#!/bin/sh

if [ $# -ne 5 ]; then
    echo "引数は5個宣言してください."
    echo "引数1: 日付(例: 0510)"
    echo "引数2: 空間次元(例: 3D)"
    echo "引数3: 粒子数(例: 256)"
    echo "引数4: 開始sample num(例: 0)"
    echo "引数5: 終了sample num(例: 400)"
    exit 1
fi

./sample_routine.sh $1 $2 $3 $4 $5

dir_num=5
dir1="./1:0/"
dir2="./3:1/"
dir3="./1:1/"
dir4="./1:3/"
dir5="./0:1/"
for i in `seq 1 $dir_num`
do
    eval DIR=\"\$`echo dir$i`\" #間接参照で目的のdirectoryを代入
    echo $DIR"に入ります..."
    cd $DIR
    ./all_routine_ver2.sh $1 $2 $3
    cd ../
done
