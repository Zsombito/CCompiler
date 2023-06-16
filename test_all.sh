#!/bin/bash

wrong=0

correct=0

NOCOLOR='\033[0m'
GREEN='\033[0;32m'
RED='\033[0;31m'

for driver in compiler_tests/*/*_driver.c ; do

    base=${driver: : -9}

    pair="${base}.c"

    echo %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    bin/c_compiler -S ${pair} -o ${base}.s

    mips-linux-gnu-gcc -mfp32 -o ${base}.o -c ${base}.s

    mips-linux-gnu-gcc -mfp32 -static -o ${base} ${base}.o ${driver}

    qemu-mips ${base}

    if [ "$?" -eq "0" ]

    then

    echo -e ${pair} ": ${GREEN}PASS${NOCOLOR}"

    correct=$(( correct + 1 ))

    else

    echo -e ${pair} ": ${RED}FAILED${NOCOLOR}"

    wrong=$(( wrong + 1 ))

    fi

    echo %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    printf "\n"



done



 echo "SIUUUUUUUUUUUUUUUUUU: "${correct}

 echo "Incorrect: "${wrong}