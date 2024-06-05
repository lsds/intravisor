#!/bin/sh -xe

NGINX=/usr/local/nginx/sbin/nginx
FETCHBENCH=/usr/local/nginx/sbin/fetchbench
NTIMES=10

echo "${0}: uname:"
uname -a

echo "${0}: invariants/witness:"
sysctl -a | grep -E '(invariants|witness)' || true

echo "${0}: nginx binary details:"
if ! command -v file > /dev/null; then
	echo "file binary not installed"
else
	file "${NGINX}"
fi

if command -v jot> /dev/null; then
	LOOP=`jot ${NTIMES}`
else
	echo "jot not found, assuming benchmark must be run 10 times"
	LOOP="1 2 3 4 5 6 7 8 9 10"
fi

echo "${0}: running benchmark ${NTIMES} times..."
for i in ${LOOP}; do
	echo "${0}: starting nginx iteration ${i} ..."
	export STATCOUNTERS_FORMAT=csv
	export STATCOUNTERS_OUTPUT="/tmp/nginx.statcounters.csv"
	${NGINX}

	${FETCHBENCH} http://127.0.0.1/ 5 200

	echo "${0}: stopping nginx..."
	${NGINX} -s stop
done

echo "${0}: DONE RUNNING BENCHMARKS"
