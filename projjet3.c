#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "math.h"

// copie colle prise de differenete corection pour nous donner des sources de fct pas pour les copier coller tel qu'elle mais une sorte de repertoire de fonction utile est possible

build() {
    gcc -Wall -Wextra -O2 "$1" -o "${1%.c}"
}

run() {
    gcc -Wall -Wextra -O2 "$1" -o "${1%.c}" && ./"${1%.c}"
}

clean() {
    rm -f *.o *.out a.out $(ls | grep -v '\.' | grep -v '^$')
}

build_all() {
    gcc -Wall -Wextra -O2 *.c -o program
}

runargs() {
    exe="${1%.c}"
    gcc -Wall -Wextra "$1" -o "$exe" && shift && "./$exe" "$@"
}

build_debug() {
    gcc -Wall -Wextra -g *.c -o program_debug
}
