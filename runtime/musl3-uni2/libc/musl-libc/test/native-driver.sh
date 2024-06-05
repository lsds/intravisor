#!/bin/bash

CMD_ARGS=()
while true; do
	if (( ${#} == 0 )); then
		echo "Error: invalid driver invocation" >&2
		exit 2
	fi
	case ${1} in
		--)
			shift
			break
			;;
		*)
			CMD_ARGS+=(${1})
			shift
			;;
	esac
done
TEST=${1}
shift
TEST_ARGS=${@}

${CMD_ARGS[*]} ${TEST} ${TEST_ARGS}
