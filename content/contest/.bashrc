rcc() {
    g++ -ftrapv -Wconversion -std=c++11 -Wall -Wextra -pedantic -fno-common -fno-builtin -o ${@: -1}.out $@ && ./${@: -1}.out
}