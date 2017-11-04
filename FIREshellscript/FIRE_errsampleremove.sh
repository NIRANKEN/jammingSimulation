#!/bin/sh

if [ $# -ne 2 ]; then
    echo "指定された引数の数は$#個です. 1>&2"
    echo "実行するには2個の引数が必要です." 1>&2
    echo "第一引数... 日付(e.g. 0224)." 1>&2
    echo "第二引数... サンプルナンバー(e.g. 1,401,...)." 1>&2
    exit 1
fi

if [ $2 -ge 0 -a $2 -lt 10 ]; then
    rm -f EigCum0000$2_*.txt
elif [ $2 -ge 10 -a $2 -lt 100 ]; then
    rm -f EigCum000$2_*.txt
elif [ $2 -ge 100 -a $2 -lt 1000 ]; then
    rm -f EigCum00$2_*.txt
elif [ $2 -ge 1000 -a $2 -lt 10000 ]; then
    rm -f EigCum0$2_*.txt
elif [ $2 -ge 10000 -a $2 -lt 100000 ]; then
    rm -f EigCum$2_*.txt
else
    echo "You make an ERROR!!"
    exit 1
fi

rm -f "VV"$1"_CODDIST"$2"_*.txt"
rm -f "BIPhiEngVV"$1"_RAND"$2"_1.txt"
