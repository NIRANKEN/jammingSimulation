#!/bin/sh

if [ $# -ne 3 ]; then
        echo "引数は3個宣言してください."
        echo "引数1: 日付(例: 0510)"
        echo "引数2: 空間次元(例: 3D)"
        echo "引数3: 粒子数(例: 256)"
        exit 1
fi

dir1="1.5_1"
dir2="2_1.5"
dir3="2.5_2"
dir4="3_2.5"
dir5="3.5_3"
dir6="4_3.5"
dir7="4.5_4"
dir8="5_4.5"
dir9="5.5_5"
dir10="6_5.5"
dir11="6.5_6"

# modified in 2017/0606

echo "CharacteristicFrequency2_SM_EIGEnsAve_BR0.05_"$1"_"$2"BIN"$3".txt $1 BI $3 $2" > sin_addBIN_bi_

cp F_addBIN 1.5_1
cp F_addBIN 2_1.5
cp F_addBIN 2.5_2
cp F_addBIN 3_2.5
cp F_addBIN 3.5_3
cp F_addBIN 4_3.5
cp F_addBIN 4.5_4
cp F_addBIN 5_4.5
cp F_addBIN 5.5_5
cp F_addBIN 6_5.5
cp F_addBIN 6.5_6

cp sin_addBIN_bi_ 1.5_1
cp sin_addBIN_bi_ 2_1.5
cp sin_addBIN_bi_ 2.5_2
cp sin_addBIN_bi_ 3_2.5
cp sin_addBIN_bi_ 3.5_3
cp sin_addBIN_bi_ 4_3.5
cp sin_addBIN_bi_ 4.5_4
cp sin_addBIN_bi_ 5_4.5
cp sin_addBIN_bi_ 5.5_5
cp sin_addBIN_bi_ 6_5.5
cp sin_addBIN_bi_ 6.5_6

cd 1.5_1
./F_addBIN 1 < sin_addBIN_bi_
cd ../2_1.5
./F_addBIN 1 < sin_addBIN_bi_
cd ../2.5_2
./F_addBIN 1 < sin_addBIN_bi_
cd ../3_2.5
./F_addBIN 1 < sin_addBIN_bi_
cd ../3.5_3
./F_addBIN 1 < sin_addBIN_bi_
cd ../4_3.5
./F_addBIN 1 < sin_addBIN_bi_
cd ../4.5_4
./F_addBIN 1 < sin_addBIN_bi_
cd ../5_4.5
./F_addBIN 1 < sin_addBIN_bi_
cd ../5.5_5
./F_addBIN 1 < sin_addBIN_bi_
cd ../6_5.5
./F_addBIN 1 < sin_addBIN_bi_
cd ../6.5_6
./F_addBIN 1 < sin_addBIN_bi_
cd ../

