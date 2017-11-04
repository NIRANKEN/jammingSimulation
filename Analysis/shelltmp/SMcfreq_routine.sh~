#!/bin/sh

if [ $# -ne 4 ]; then
    echo "引数は4個宣言してください."
    echo "引数1: Output file name(例: hogehoge.txt)"
    echo "引数2: 日付(例: 0510)"
    echo "引数3: 空間次元(例: 3D)"
    echo "引数4: 粒子数(例: 256)"
    exit 1
fi

echo "$2 BI $4 $3" > sin_cfreq_bi_

cp F_cfreq 1.5_1
cp F_cfreq 2_1.5
cp F_cfreq 2.5_2
cp F_cfreq 3_2.5
cp F_cfreq 3.5_3
cp F_cfreq 4_3.5
cp F_cfreq 4.5_4
cp F_cfreq 5_4.5
cp F_cfreq 5.5_5
cp F_cfreq 6_5.5

cp sin_cfreq_bi_ 1.5_1
cp sin_cfreq_bi_ 2_1.5
cp sin_cfreq_bi_ 2.5_2
cp sin_cfreq_bi_ 3_2.5
cp sin_cfreq_bi_ 3.5_3
cp sin_cfreq_bi_ 4_3.5
cp sin_cfreq_bi_ 4.5_4
cp sin_cfreq_bi_ 5_4.5
cp sin_cfreq_bi_ 5.5_5
cp sin_cfreq_bi_ 6_5.5

cd 1.5_1
./F_cfreq 0 < sin_cfreq_bi_
cd ../2_1.5
./F_cfreq 0 < sin_cfreq_bi_
cd ../2.5_2
./F_cfreq 0 < sin_cfreq_bi_
cd ../3_2.5
./F_cfreq 0 < sin_cfreq_bi_
cd ../3.5_3
./F_cfreq 0 < sin_cfreq_bi_
cd ../4_3.5
./F_cfreq 0 < sin_cfreq_bi_
cd ../4.5_4
./F_cfreq 0 < sin_cfreq_bi_
cd ../5_4.5
./F_cfreq 0 < sin_cfreq_bi_
cd ../5.5_5
./F_cfreq 0 < sin_cfreq_bi_
cd ../6_5.5
./F_cfreq 0 < sin_cfreq_bi_
cd ../


echo "" > $1
cd 1.5_1/
cat "CharacteristicFrequency_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt" >> ../$1
cd ../2_1.5/
cat "CharacteristicFrequency_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt" >> ../$1
cd ../2.5_2/
cat "CharacteristicFrequency_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt" >> ../$1
cd ../3_2.5/
cat "CharacteristicFrequency_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt" >> ../$1
cd ../3.5_3/
cat "CharacteristicFrequency_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt" >> ../$1
cd ../4_3.5/
cat "CharacteristicFrequency_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt" >> ../$1
cd ../4.5_4/
cat "CharacteristicFrequency_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt" >> ../$1
cd ../5_4.5/
cat "CharacteristicFrequency_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt" >> ../$1
cd ../5.5_5/
cat "CharacteristicFrequency_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt" >> ../$1
cd ../6_5.5/
cat "CharacteristicFrequency_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt" >> ../$1
cd ../
