cd $(dirname $0)

[ -d bin/ ] || mkdir bin

gcc -Wall -O2 -fPIC -shared src/lockall/lockall.c -Wl,-soname,liblockall.so -o bin/liblockall.so
