cd $(dirname $0)

[ -d bin/ ] || mkdir bin

gcc -Wall src/noswap/noswap.c -o bin/noswap
