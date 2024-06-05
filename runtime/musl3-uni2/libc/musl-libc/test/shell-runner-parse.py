import sys

from runner import report, passcase, failcase, skipcase
from datetime import datetime

START = '-- START --'
END = '-- END -------------------------'
PASS = '-- PASS'
FAIL = '-- FAIL'
SKIP = '-- SKIP'
INFO = '-- INFO'

if __name__ == '__main__':

    results = sys.argv[1]  # path to log file from the shell test runner script
    foutput = sys.argv[2]  # path to junit report to generate
    suitename = sys.argv[3]  # test suite name

    with open(results, 'rt') as f:
        lines = f.readlines()
    tests = {}
    tname = ''
    for line in lines:
        line = line.strip()
        if line.startswith(START):
            tname = line[len(START) + 1:]
            tests[tname] = {
                'name': tname,
                'result': None,
                'output': [],
                'found-end': False,
                'reason': None
            }
            continue
        if tname in tests:
            u = tests.get(tname)
            if line.startswith(END):
                u['found-end'] = True
            elif line.startswith(PASS):
                u['result'] = 'pass'
                tname = ''
            elif line.startswith(FAIL):
                u['result'] = 'fail'
                tmp = line[len(FAIL) + 1:]
                _, reason = [t.strip() for t in tmp.split(':')][:2]
                u['reason'] = reason
                tname = ''
            elif line.startswith(SKIP):
                u['result'] = 'skip'
                tmp = line[len(SKIP) + 1:]
                _, reason = [t.strip() for t in tmp.split(':')][:2]
                u['reason'] = reason
                tname = ''
            else:
                u['output'].append(line)
        elif line.startswith(SKIP):
            tmp = line[len(SKIP) + 1:]
            tname, reason = [t.strip() for t in tmp.split(':')][:2]
            tests[tname] = {
                'name': tname,
                'result': 'skip',
                'output': [],
                'found-end': True,
                'reason': reason
            }
            tname = ''
        elif line.startswith(INFO):
            pass
        else:
            print(f'unexpected line: {line}')

    testcases = []
    failures, skipped, passed = 0, 0, 0
    failed_tests = []
    skipped_tests = []
    for tname, u in tests.items():
        result = u.get('result')
        reason = u.get('reason')
        found_end = u.get('found-end')
        output: list = u.get('output')
        kind = tname.split('.')[0]
        name = '.'.join(tname.split('.')[1:])
        if result == 'pass':
            testcases.append(
                passcase.substitute(
                    name=name, classname=f'{suitename}.{kind}', time='0.0',
                    stdout='\n'.join(output), stderr='')
            )
            passed += 1
        elif result == 'fail':
            testcases.append(
                failcase.substitute(
                    name=name, classname=f'{suitename}.{kind}', time='0.0',
                    description=f'{tname} failed: {reason}',
                    stdout='\n'.join(output), stderr='')
            )
            failures += 1
            failed_tests.append((tname, reason))
        elif result == 'skip':
            testcases.append(
                skipcase.substitute(
                    name=name, classname=f'{suitename}.{kind}', time='0.0',
                    stdout=' '.join(output), stderr='')
            )
            skipped += 1
            skipped_tests.append((tname, reason))

    ntests = passed + skipped + failures
    when = datetime.now()
    with open(foutput, 'wt') as f:
        f.write(report.substitute(
            testcases='\n'.join(testcases),
            suite=suitename,
            errors='0',
            failures=f'{failures}', skipped=f'{skipped}', tests=f'{ntests}',
            timestamp=when.astimezone().strftime('%Y-%m-%dT%H:%M:%S%z'),
            total='0.0'
        ))

    print(f'Results: total tests {ntests}, failed {failures}, skipped {skipped}')
    if failures > 0:
        print('Failed tests:')
    for tn, tsreason in sorted(failed_tests, key=lambda t: t[0]):
        print(f'- failed: {tn} ({tsreason})')
    if skipped > 0:
        print('Skipped tests:')
    for tn, tsreason in sorted(skipped_tests, key=lambda t: t[0]):
        print(f'- skipped: {tn} ({tsreason})')
    sys.exit(1 if failures > 0 else 0)
