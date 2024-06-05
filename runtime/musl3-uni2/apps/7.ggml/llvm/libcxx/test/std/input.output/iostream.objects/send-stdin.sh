program=${@:1:$#-1}
input="${@: -1}"
echo -n ${input} | ${program}
