#!/bin/sh

if [ $# -ne 5 ]; then
    echo "引数は5個宣言してください."
    echo "引数1 日付(例by 0510)"
    echo "引数2 空間次元(例by 3D)"
    echo "引数3 粒子数(例by 256)"
    echo "引数4 開始sample num(例by 0)"
    echo "引数5 終了sample num(例by 400)"
    exit 1
fi

./sample_routine.sh $1 $2 $3 $4 $5

# echo "引数1: 固有振動数の出力モード(例: 0->normal, 1->MScaled)"
# echo "引数2: zero-frequencyの出力モード(例: 0->出力しない, 1->出力する)"
# echo "引数3: 日付(例: 0510)"
# echo "引数4: 空間次元(例: 3D)"
# echo "引数5: 粒子数(例: 256)"
# echo "引数6: 成分1の混合比 (例:1)" 
# echo "引数7: 成分2の混合比 (例:1)" 
# echo "引数8: 成分1と成分2のサイズ比 (例:1.4)"

declare -a array=(1 0 3 1 1 1 1 3 0 1)
dir_num=5
dir1="./1by0/"
dir2="./3by1/"
dir3="./1by1/"
dir4="./1by3/"
dir5="./0by1/"
for i in `seq 1 $dir_num`
do
    eval DIR=\"\$`echo dir$i`\" #間接参照で目的のdirectoryを代入
    echo $DIR"に入ります..."
    cd $DIR
    echo ${array[0]}":"${array[1]}"の混合比についてEigのサンプル統計をとります..."
    ./all_routine_ver2.sh 0 0 $1 $2 $3 ${array[0]} ${array[1]} 1.4
    ./all_routine_ver2.sh 1 0 $1 $2 $3 ${array[0]} ${array[1]} 1.4
    # ./all_routine_ver2.sh $1 $2 $3
    array=("${array[@]:1}") # 先頭要素抜く 
    array=("${array[@]:1}") # 先頭要素抜く
    cd ../
done
