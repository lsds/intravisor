import sys
import json
import time
import os
import subprocess
import re
import signal

from os.path import basename
from multiprocessing import Pool
from string import Template
from datetime import datetime

report = Template('''<?xml version="1.0" encoding="UTF-8"?>
<testsuites>
<testsuite name="${suite}" errors="${errors}" failures="${failures}" skipped="${skipped}" tests="${tests}" hostname="tbd" time="${total}" timestamp="${timestamp}">
${testcases}
</testsuite>
</testsuites>
''')
passcase = Template('''<testcase classname="${classname}" name="${name}" time="${time}" status="run">
<system-out><![CDATA[
${stdout}
]]></system-out>
<system-err><![CDATA[
${stderr}
]]></system-err>
</testcase>''')
failcase = Template('''<testcase classname="${classname}" name="${name}" time="${time}" status="run">
<failure message="Test ${name} failed" type="failure">
<![CDATA[
DESCRIPTION:
${description}
STDOUT:
${stdout}
STDERR:
${stderr}
]]>
</failure>
<system-out><![CDATA[
${stdout}
]]></system-out>
<system-err><![CDATA[
${stderr}
]]></system-err>
</testcase>''')
skipcase = Template('''<testcase classname="${classname}" name="${name}" time="${time}" status="run">
<skipped/>
<system-out><![CDATA[
${stdout}
]]></system-out>
<system-err><![CDATA[
${stderr}
]]></system-err>
</testcase>''')

class TC:
    PASS = '\033[1;32m' if sys.stdout.isatty() else ''
    FAIL = '\033[1;31m' if sys.stdout.isatty() else ''
    WARN = '\033[1;33m' if sys.stdout.isatty() else ''
    CEND = '\033[0m' if sys.stdout.isatty() else ''

class Args(object):

    def __init__(self):
        opt = sys.argv[1:]
        self.kind: str = opt[0]  # kind of test run (used for skip reasons)
        self.nproc: int = int(opt[1])  # number of parallel processes
        self.workdir: str = opt[2]  # working directory
        self.testspec: str = opt[3]  # path to the JSON test spec
        self.driver: str = opt[4]  # path to test driver
        self.driver_id: str = os.path.basename(self.driver)  # driver id
        self.suitename: str = opt[5]  # testsuite name (classname for junit report)
        self.report: str = opt[6]  # path to junit report
        self.tags: list = opt[7:]  # test tags (used for skip reasons)

class Test(object):

    test_names = {}

    def __init__(self, t: dict, a: Args, kind: str):
        self.kind: str = kind
        self.app: str = self._replace_variables(a, t.get('app'))  # test app
        self.args: list = self._get_test_args(a, t.get('args', []))
        self.params: list = self._get_driver_params(a, t.get('params', {}))
        self.name: str = t.get('name', self._default_name())  # test name
        if self.name not in Test.test_names:
            Test.test_names[self.name] = 1
        self.timeout: int = int(t.get('timeout', 120))  # test timeout in seconds
        self.env: dict = {k: v for k, v in t.get('env', {}).items()}  # extra env vars
        self.skip: list = Test._reasons(t.get('skip', []))  # list of reasons to ignore failure
        self.ignore: list = Test._reasons(t.get('ignore', []))  # when not to run the test at all
        self.stdin: str = t.get('stdin', None)  # standard input (optional)
        self.expected: dict = {  # expected results from the test run
            'rc': Test._expected_rc(t),  # expected exit codes
            'stdout': t.get('stdout', []),  # lines to match in stdout
            'stderr': t.get('stderr', []),  # lines to match in stderr
        }
        self.cmd: list = [a.driver] + self.params + ['--'] + [self.app] + self.args
        self.cwd = a.workdir
        self.classname: str = f'{a.suitename}.{self.kind}'

    def _replace_variables(self, a: Args, text: str) -> str:
        tmp = text.replace('${build}', a.workdir)
        tmp = tmp.replace('${kind}', self.kind)
        for name, val in os.environ.items():
            if name.startswith('TEST_RUNNER_'):
                nm = name[len('TEST_RUNNER_'):].lower()
                tmp = tmp.replace(f'${{{nm}}}', val)
        return tmp

    def _default_name(self):
        # generate unique default name
        base = basename(self.app).replace('.', '-').replace('_', '-')
        suffix = '-' + str('-'.join([str(t).strip(' -') for t in self.args])) if self.args else ''
        name = f'{base}{suffix}'
        if name in Test.test_names:
            n = Test.test_names[name] + 1
            Test.test_names[name] = n
            return f'{name}-{n}'
        else:
            return name

    def _get_test_args(self, a: Args, test_args: list) -> list:
        # arguments for the test app
        return [self._replace_variables(a, v) for v in test_args]

    def _get_driver_params(self, a: Args, params) -> list:
        # driver parameters for this test
        return [self._replace_variables(a, v) for v in params.get(a.driver_id, [])]

    @staticmethod
    def _reasons(some) -> list:
        if not isinstance(some, list):
            some = [str(some)]
        return some

    @staticmethod
    def _expected_rc(t: dict) -> list:
        xrc = t.get('xrc', [0])
        if not isinstance(xrc, list):
            xrc = [xrc]
        return [int(v) for v in xrc]

def __subprocess(cmd: list, stdin, env: dict, cwd: str):
    return subprocess.Popen(cmd, universal_newlines=True, cwd=cwd,
        start_new_session=True, stdin=subprocess.PIPE if stdin else None,
        stdout=subprocess.PIPE, stderr=subprocess.PIPE,
        env={**env, **dict(os.environ)})

def __run_process(t: Test) -> tuple:
    proc = __subprocess(t.cmd, t.stdin, t.env, cwd=t.cwd)
    try:
        stdout, stderr = proc.communicate(input=t.stdin, timeout=t.timeout)
        code = proc.returncode
    except subprocess.TimeoutExpired as err:
        stdout = err.stdout
        stderr = err.stderr
        if not stdout:
            stdout = f'Timed out after {t.timeout} seconds'
        if not stderr:
            stderr = f'Timed out after {t.timeout} seconds'
        code = 124  # timed out
        pg = os.getpgid(proc.pid)
        os.killpg(pg, signal.SIGKILL)
    if type(stdout) is not str:
        stdout = stdout.decode('utf-8')
    if type(stderr) is not str:
        stderr = stderr.decode('utf-8')
    return code, stdout.strip('\n'), stderr.strip('\n')

def __scan_output(received: list, expected: list) -> tuple:
    n = 0
    for kk, cmd in enumerate(expected):
        if n >= len(received):
            yield '', '', -2  # reached end of output
        line = received[n]
        n += 1
        yield line, cmd, n  # we index lines starting with 1
    if n < len(received):
        yield '', '', -3  # reached end expected output but more lines are available

def __compare_output(received: list, expected: list) -> tuple:
    if not expected:
        return True, ''  # no need to check anything
    for v in __scan_output(received, expected):
        line, paragon, n = v
        if n == -1:
            # no more checks needed
            break
        elif n == -2:
            # unexpected end of output
            return False, f'(reached end of output)'
        elif n == -3:
            # end of expected output
            return False, f'(output is too long)'
        elif n == -4:
            # bad command in test spec
            return False, f'(bad command in test spec)'
        if paragon in line:
            # check that `expected` is just a substring
            pass
        else:
            # try to match regex
            matcher = re.compile(paragon)
            if matcher.match(line):
                pass
            else:
                return False, f'in line {n} `{line}` vs `{paragon}`'
    return True, ''  # all good

def __check(rc: int, stdout: list, stderr: list, t: Test) -> tuple:
    message = []
    successful = rc in t.expected.get('rc')
    if not successful:
        message += [f'unexpected exit code: {rc}']
    successful, where = __compare_output(stdout, t.expected.get('stdout'))
    if not successful:
        message += [f'stdout mismatch {where}']
    successful, where = __compare_output(stderr, t.expected.get('stderr'))
    if not successful:
        message += [f'stderr mismatch {where}']
    return len(message) == 0, ', '.join(message)

def __run(t: Test, a: Args) -> tuple:
    if t.ignore and (a.kind in t.ignore or (set(t.ignore) & set(a.tags))):
        # do not run this test
        dt = 0.0
        dt_str = '%.3f' % dt
        if a.kind in t.ignore:
            skipping = a.kind
        else:
            cr = set(t.ignore) & set(a.tags)
            skipping = '+'.join(sorted([str(t) for t in cr]))
        res = skipcase.substitute(
            name=t.name, classname=t.classname, time=dt_str,
            stdout=f'test not run: {skipping}', stderr='')
        return t.name, res, dt, 1, 0, skipping
    st = time.time()
    rc, out, err = __run_process(t)
    dt = (time.time() - st)
    dt_str = '%.3f' % dt
    successful, msg = __check(rc, out.split('\n'), err.split('\n'), t)
    nskipped = 0
    nfailed = 0
    skipping = ''
    if successful:
        print(f'{TC.PASS}PASS{TC.CEND} {t.name} ({dt_str} sec)')
        res = passcase.substitute(
            name=t.name, classname=t.classname, time=dt_str,
            stdout='' if out is None else out,
            stderr='' if err is None else err)
    else:
        # test failed, but we may ignore the failure in certain cases
        if t.skip:
            if 'jenkins' in t.skip and 'JOB_URL' in os.environ:
                skipping = 'jenkins'
            elif 'flaky' in t.skip or 'always' in t.skip:
                skipping = 'flaky'
            elif a.kind in t.skip:  # skip by test kind
                skipping = a.kind
            else:
                for tag in a.tags:  # skip by test tags
                    if tag in t.skip:
                        skipping = tag
                        break
        if skipping:
            nskipped = 1
            print(f'{TC.WARN}SKIP{TC.CEND} {t.name}: {msg} [{skipping}] ({dt_str} sec)')
            res = skipcase.substitute(
                name=t.name, classname=t.classname, time=dt_str,
                stdout='' if out is None else out,
                stderr='' if err is None else err)
        else:
            nfailed = 1
            print(f'{TC.FAIL}FAIL{TC.CEND} {t.name}: {msg} ({dt_str} sec)')
            res = failcase.substitute(
                name=t.name, classname=t.classname, time=dt_str,
                description=f'Command line: {" ".join(t.cmd)}\nReason: {msg}\nReturn code: {rc}',
                stdout='' if out is None else out,
                stderr='' if err is None else err)
    return t.name, res, dt, nskipped, nfailed, skipping

if __name__ == '__main__':
    args = Args()
    with open(args.testspec, 'rt') as f:
        testspec: list = json.load(f)
    tests = [Test(v, args, kind=args.kind) for v in testspec]

    # run tests
    if args.nproc == 1:
        q: list = [__run(t, args) for t in tests]
    else:
        def __run__(v: Test):
            return __run(v, args)
        with Pool(args.nproc) as p:
            q: list = p.map(__run__, tests)

    # process results
    testcases = []  # list of results for junit report
    ntests, failures, skipped = 0, 0, 0  # counters for tests
    failed_tests = []  # list of failed tests
    skipped_tests = []  # list of skipped tests
    total = 0.0  # total execution time
    skip_reasons = {}  # why tests have been skipped
    for x in q:
        if x is None:
            continue
        tname, tres, ttime, tskipped, tfailed, tsreason = x
        if tres is None:
            continue
        testcases.append(tres)
        total += ttime
        ntests += 1
        skipped += tskipped
        failures += tfailed
        if tfailed > 0:
            failed_tests.append(tname)
        if tskipped > 0:
            skipped_tests.append((tname, tsreason))
            if tsreason not in skip_reasons:
                skip_reasons[tsreason] = 0
            skip_reasons[tsreason] += tskipped
    when = datetime.now()
    with open(args.report, 'wt') as f:
        f.write(report.substitute(
            testcases='\n'.join(testcases),
            suite=args.suitename,
            errors='0',
            failures=f'{failures}', skipped=f'{skipped}', tests=f'{ntests}',
            timestamp=when.astimezone().strftime('%Y-%m-%dT%H:%M:%S%z'),
            total='%.3f' % total
        ))
    print(f'Results: total tests {ntests}, failed {failures}, skipped {skipped}')
    if failures > 0:
        print('Failed tests:')
    for tn in sorted(failed_tests):
        print(f'- failed: {tn}')
    if skipped > 0:
        print('Skipped tests:')
    for tn, tsreason in sorted(skipped_tests, key=lambda t: t[0]):
        print(f'- skipped: {tn} ({tsreason})')
    sys.exit(1 if failures > 0 else 0)
