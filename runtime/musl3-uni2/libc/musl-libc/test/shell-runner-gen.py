import sys
import json
import os

from runner import Test
from string import Template

script_template = Template('''

TOTAL_TESTS_NUM=0
PASSED_TESTS_NUM=0
FAILED_TESTS_NUM=0
SKIPPED_TESTS_NUM=0

PASSED_TESTS=
FAILED_TESTS=
SKIPPED_TESTS=

TEST_TAGS=$${TEST_RUNNER_TAGS:-"${tags}"}

echo "-- INFO Running with tags: $${TEST_TAGS}"

function contains () {
    local haystack="$${1}"
    local needle="$${2}"
    if [ "$${haystack#*$$needle}" != "$${haystack}" ]; then
        return 0
    else
        return 1
    fi
}

function test_run() {
    local tname=$${1}
    local cmd=$${2}
    local stdinput=$${3}
    local xrc=$${4}
    local kind=$${5}
    local skip=$${6}
    local ignore=$${7}
    TOTAL_TESTS_NUM=$$((TOTAL_TESTS_NUM+1))
    for r in $${ignore}; do
        if contains "$${TEST_TAGS} $${kind}" "$${r}"; then
            SKIPPED_TESTS_NUM=$$((SKIPPED_TESTS_NUM+1))
            SKIPPED_TESTS="$${SKIPPED_TESTS} $${tname}"
            echo "-- SKIP $${tname}: $${r} (not run)"
            return
        fi
    done
    echo "-- START -- $${tname}"
    if [ "$${stdinput}" == "" ]; then
        $${cmd}
    else
        echo -e -n "$${stdinput}" | $${cmd}
    fi
    local rc=$${?}
    echo "-- END -------------------------"
    if [ $${rc} == $${xrc} ]; then
        PASSED_TESTS_NUM=$$((PASSED_TESTS_NUM+1))
        PASSED_TESTS="$${PASSED_TESTS} $${tname}"
        echo "-- PASS $${tname} (returned $${rc})"
    else
        for r in $${skip}; do
            if contains "$${TEST_TAGS} $${kind} flaky" "$${r}"; then
                SKIPPED_TESTS_NUM=$$((SKIPPED_TESTS_NUM+1))
                SKIPPED_TESTS="$${SKIPPED_TESTS} $${tname}"
                echo "-- SKIP $${tname}: $${r}"
                return
            fi
        done
        FAILED_TESTS_NUM=$$((FAILED_TESTS_NUM+1))
        FAILED_TESTS="$${FAILED_TESTS} $${tname}"
        echo "-- FAIL $${tname}: returned $${rc} instead of $${xrc}"
    fi
}

${tests}

echo "-- INFO Results ($${TOTAL_TESTS_NUM} tests):"
echo "-- INFO  - passed:  $${PASSED_TESTS_NUM}"
echo "-- INFO  - failed:  $${FAILED_TESTS_NUM}"
echo "-- INFO  - skipped: $${SKIPPED_TESTS_NUM}"

if [ -z "$${FAILED_TESTS}" ]; then
    exit 0
else
    exit 1
fi

''')

test_template = Template(
    '${env} test_run ${name} "${cmd}" "${stdin}" ${xrc} ${kind} "${skip}" "${ignore}"'
)

class Args(object):

    def __init__(self):
        opt = sys.argv[1:]
        self.scriptpath: str = opt[0]  # path to generated script
        self.workdir: str = opt[1]  # working directory
        self.testspec: str = opt[2]  # path to the JSON test spec
        self.suitename: str = opt[3]  # testsuite name (classname for junit report)
        self.tags: list = opt[4:]  # test tags (used for skip reasons)
        self.driver: str = 'none'
        self.driver_id: str = 'none'

if __name__ == '__main__':
    args = Args()
    with open(args.testspec, 'rt') as f:
        testspec: list = json.load(f)
    static_tests = [Test(v, args, kind='static') for v in testspec]
    dynamic_tests = [Test(v, args, kind='dynamic') for v in testspec]

    cwd_path = os.path.join(os.path.dirname(__file__), 'src')

    for t in static_tests + dynamic_tests:
        t.cmd = t.cmd[t.cmd.index('--') + 1:]
        t.cmd[0] = './' + os.path.relpath(t.cmd[0], cwd_path)

    tests = []
    for t in static_tests + dynamic_tests:
        tenv = ' '.join([f'{n}={v}' for n, v in t.env.items()])
        tcmd = ' '.join(t.cmd)
        if t.stdin is not None:
            user_input = t.stdin.replace('\n', '\\n')
        else:
            user_input = ''
        fqn = f'{t.kind}.{t.name}'
        tests.append(test_template.substitute(
            name=fqn, env=tenv, cmd=tcmd, stdin=user_input,
            xrc=t.expected.get('rc')[0],
            kind=t.kind, timeout=t.timeout,
            skip=' '.join(t.skip), ignore=' '.join(t.ignore),
        ).strip())

    with open(args.scriptpath, 'wt') as f:
        f.write(script_template.substitute(
            tests='\n'.join(tests),
            tags=' '.join(args.tags)
        ))
