#!/bin/sh

if [ $# -eq 1 ]; then
    PN=$1
    #PN場合分け.

    cat smcfN$PN.txt | sed -e "s/$/ $PN/g" > hey.txt
    cat hey.txt > smcfN$PN.txt
    rm -f hey.txt
else
        echo "引数1: 粒子数(e.g. 128)"
        echo "ERROR!"
        exit 1
fi
