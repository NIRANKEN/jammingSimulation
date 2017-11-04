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

echo $1" BI "$3" "$2" "$4" "$5 > sin_sample_bi_

mkdir "SAMPLE"$1
cd "SAMPLE"$1
mkdir "1:0"
mkdir "3:1"
mkdir "1:1"
mkdir "1:3"
mkdir "0:1"
cd "../"

cp *.sh "./SAMPLE"$1"/1:0"
cp *.sh "./SAMPLE"$1"/3:1"
cp *.sh "./SAMPLE"$1"/1:1"
cp *.sh "./SAMPLE"$1"/1:3"
cp *.sh "./SAMPLE"$1"/0:1"
cp F_* "./SAMPLE"$1"/1:0"
cp F_* "./SAMPLE"$1"/3:1"
cp F_* "./SAMPLE"$1"/1:1"
cp F_* "./SAMPLE"$1"/1:3"
cp F_* "./SAMPLE"$1"/0:1"

cp F_sample "./"$2"N"$3
cp F_sample "./BI"$2"N"$3"_3:1"
cp F_sample "./BI"$2"N"$3
cp F_sample "./BI"$2"N"$3"_1:3"
cp F_sample "./BI"$2"N"$3"_0:1"

cp sin_sample_bi_ "./"$2"N"$3
cp sin_sample_bi_ "./BI"$2"N"$3"_3:1"
cp sin_sample_bi_ "./BI"$2"N"$3
cp sin_sample_bi_ "./BI"$2"N"$3"_1:3"
cp sin_sample_bi_ "./BI"$2"N"$3"_0:1"

cd "./"$2"N"$3
./F_sample < sin_sample_bi_
mv *"_"$1"_"$2"BIN"$3".txt" "../SAMPLE"$1"/1:0/"
cd "../BI"$2"N"$3"_3:1"
./F_sample < sin_sample_bi_
mv *"_"$1"_"$2"BIN"$3".txt" "../SAMPLE"$1"/3:1/"
cd "../BI"$2"N"$3
./F_sample < sin_sample_bi_
mv *"_"$1"_"$2"BIN"$3".txt" "../SAMPLE"$1"/1:1/"
cd "../BI"$2"N"$3"_1:3"
./F_sample < sin_sample_bi_
mv *"_"$1"_"$2"BIN"$3".txt" "../SAMPLE"$1"/1:3/"
cd "../BI"$2"N"$3"_0:1"
./F_sample < sin_sample_bi_
mv *"_"$1"_"$2"BIN"$3".txt" "../SAMPLE"$1"/0:1/"
cd "../SAMPLE"$1
