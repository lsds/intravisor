program=${@:1:$#-1}
expected_stderr="${@: -1}"
${program} 2>stderr.log >stdout.log
[ "${expected_stderr}" == "$(cat stderr.log)" ]
