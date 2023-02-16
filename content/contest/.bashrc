rcc() {
    g++ -ftrapv -Wconversion -std=c++11 -Wall -Wextra -pedantic -fno-common -fno-builtin -o ${@: -1}.out $@ && ./${@: -1}.out
}
# switcher le clavier entre QWERTY et AZERTY avec alt shift K
setxkbmap us,fr -option "lv3:ralt_alt,grp:alt_shift_k_toggle"