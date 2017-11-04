#!/bin/sh

if [ $# -ne 6 ]; then
    echo "引数は7個宣言してください."
    echo "引数1: 日付(例: 0510)"
    echo "引数2: 空間次元(例: 3D)"
    echo "引数3: 粒子数(例: 256)"
    echo "引数4: input file name(例: SM_cfreq2.txt)"
    echo "引数5: データ点の個数(例: 8)"
    echo "引数6: Shift定数(例: 0.0000001)"
    exit 1
fi

echo $1 BI $3 $2 $4 > sin_ecf_bi_
./F_ECF $5 $6 < sin_ecf_bi_
