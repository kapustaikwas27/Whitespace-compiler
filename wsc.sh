#!/bin/bash
# ./wsc.sh path [name] [-ar]

name=${2:-a.out}
g++ pre.cpp -o pre

if [ $# -eq 2 ]
then
    ./pre < "$1" > b.txt
else
    ./pre "$3" < "$1" > b.txt
fi

cat a.txt b.txt c.txt > d.c
gcc d.c -o "${name}"
