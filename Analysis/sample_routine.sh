#!/bin/sh

if [ $# -ne 5 ]; then
    echo "引数は5個宣言してください."
    echo "引数1: 日付(例by 0510)"
    echo "引数2: 空間次元(例by 3D)"
    echo "引数3: 粒子数(例by 256)"
    echo "引数4: 開始sample num(例by 0)"
    echo "引数5: 終了sample num(例by 400)"
    exit 1
fi

echo $1" BI "$3" "$2" "$4" "$5 > sin_sample_bi_

mkdir "SAMPLE"$1"_N"$3
cd "SAMPLE"$1"_N"$3
mkdir "1by0"
mkdir "3by1"
mkdir "1by1"
mkdir "1by3"
mkdir "0by1"
cd "../"

cp *.sh "./SAMPLE"$1"_N"$3"/1by0"
cp *.sh "./SAMPLE"$1"_N"$3"/3by1"
cp *.sh "./SAMPLE"$1"_N"$3"/1by1"
cp *.sh "./SAMPLE"$1"_N"$3"/1by3"
cp *.sh "./SAMPLE"$1"_N"$3"/0by1"
cp F_* "./SAMPLE"$1"_N"$3"/1by0"
cp F_* "./SAMPLE"$1"_N"$3"/3by1"
cp F_* "./SAMPLE"$1"_N"$3"/1by1"
cp F_* "./SAMPLE"$1"_N"$3"/1by3"
cp F_* "./SAMPLE"$1"_N"$3"/0by1"
if [ ! -d "./"$2"N"$3 ]; then
  mkdir "./"$2"N"$3
fi
cp F_sample "./"$2"N"$3
if [ ! -d "./BI"$2"N"$3"_3by1" ]; then
  mkdir "./BI"$2"N"$3"_3by1"
fi
cp F_sample "./BI"$2"N"$3"_3by1"
if [ ! -d "./BI"$2"N"$3 ]; then
  mkdir "./BI"$2"N"$3
fi
cp F_sample "./BI"$2"N"$3
if [ ! -d "./BI"$2"N"$3"_1by3" ]; then
  mkdir "./BI"$2"N"$3"_1by3"
fi
cp F_sample "./BI"$2"N"$3"_1by3"
if [ ! -d "./BI"$2"N"$3"_0by1" ]; then
  mkdir "./BI"$2"N"$3"_0by1"
fi
cp F_sample "./BI"$2"N"$3"_0by1"

cp sin_sample_bi_ "./"$2"N"$3
cp sin_sample_bi_ "./BI"$2"N"$3"_3by1"
cp sin_sample_bi_ "./BI"$2"N"$3
cp sin_sample_bi_ "./BI"$2"N"$3"_1by3"
cp sin_sample_bi_ "./BI"$2"N"$3"_0by1"

cd "./"$2"N"$3
./F_sample < sin_sample_bi_
mv *"_"$1"_"$2"BIN"$3".txt" "../SAMPLE"$1"_N"$3"/1by0/"
cd "../BI"$2"N"$3"_3by1"
./F_sample < sin_sample_bi_
mv *"_"$1"_"$2"BIN"$3".txt" "../SAMPLE"$1"_N"$3"/3by1/"
cd "../BI"$2"N"$3
./F_sample < sin_sample_bi_
mv *"_"$1"_"$2"BIN"$3".txt" "../SAMPLE"$1"_N"$3"/1by1/"
cd "../BI"$2"N"$3"_1by3"
./F_sample < sin_sample_bi_
mv *"_"$1"_"$2"BIN"$3".txt" "../SAMPLE"$1"_N"$3"/1by3/"
cd "../BI"$2"N"$3"_0by1"
./F_sample < sin_sample_bi_
mv *"_"$1"_"$2"BIN"$3".txt" "../SAMPLE"$1"_N"$3"/0by1/"
cd "../"
cp stat_routine.sh "./SAMPLE"$1"_N"$3
cd "SAMPLE"$1"_N"$3
