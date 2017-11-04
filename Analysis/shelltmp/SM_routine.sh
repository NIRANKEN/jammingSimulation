#!/bin/sh

if [ $# -ne 5 ]; then
    echo "引数は5個宣言してください."
    echo "引数1: cfreq Output file name(例: hogehoge.txt)"
    echo "引数2: cfreq2 Output file name(例: hogehoge2.txt)"
    echo "引数3: 日付(例: 0510)"
    echo "引数4: 空間次元(例: 3D)"
    echo "引数5: 粒子数(例: 256)"
    exit 1
fi

./SMcfreq_routine.sh $1 $3 $4 $5
./SMifreq_routine.sh $2 $3 $4 $5
./SMaddstat2_routine.sh $3 $4 $5
