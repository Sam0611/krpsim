#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
COLOR='\033[1;33;5m'
NC='\033[0m'

path="conf_files/wrong/"
str=$(ls ${path})

files=(${str})

errors=0

for item in ${files[@]}; do
    ./builddir/krpsim ${path}"$item" 10 2>tester_output
    printf "$item "
    if [ -s tester_output ]; then
        printf "${GREEN}[OK]${NC}\n"
    else
        printf "${RED}[KO]${NC}\n"
        ((errors++))
    fi
done

printf "\n${COLOR}There are ${errors} errors not handled${NC}\n"

rm tester_output