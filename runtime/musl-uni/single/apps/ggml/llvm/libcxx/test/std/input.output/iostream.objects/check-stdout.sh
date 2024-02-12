program=${@:1:$#-1}
expected_stdout="${@: -1}"
${program} 2>stderr.log >stdout.log
[ "${expected_stdout}" == "$(cat stdout.log)" ]
