#!/bin/sh

if [ $# -ne 3 ]; then
    echo "引数は3個宣言してください."
    echo "引数1 日付(例by 0510)"
    echo "引数2 空間次元(例by 3D)"
    echo "引数3 粒子数(例by 256)"
    exit 1
fi

cd "1by0/"
rm -f "*_"$1"_"$2"BIN"$3".txt"
cd "../3by1/"
rm -f "*_"$1"_"$2"BIN"$3".txt"
cd "../1by1/"
rm -f "*_"$1"_"$2"BIN"$3".txt"
cd "../1by3/"
rm -f "*_"$1"_"$2"BIN"$3".txt"
cd "../0by1/"
rm -f "*_"$1"_"$2"BIN"$3".txt"
cd "../"
