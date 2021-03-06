#!/bin/sh

if [ $# -ne 8 ]; then
    echo "引数は8個宣言してください."
    echo "引数1: 日付(例: 0510)"
    echo "引数2: 空間次元(例: 3D)"
    echo "引数3: 粒子数(例: 256)"
    echo "引数4: DPHIの開始値(例: 1.0 => 10^(-(1+haba)) ~ 10^(-1))"
    echo "引数5: DPHIのbin幅(例: 0.5)"
    xxx=`echo "$4 * $5" | bc -l`
    echo "引数6: DPHIのbin幅の数(例: 11 => 引4 * 引5 = $xxx )"
    echo "引数7: Smoothed DOS or not (0=>normal DOS, 1=>smoothed DOS)"
    echo "引数8: Output file name (例: cfreq.txt)"
    exit 1
fi
if [ $7 -eq 0 ]; then
addstr=""
elif [ $7 -eq 1 ]; then
addstr="SM_"
else
    echo "引数7($7)が不正な値です.(0 or 1)"
    exit 1
fi
echo "$1 BI $3 $2" > sin_cfreq_bi_
echo -n "" > $addstr$8

haba=$5
beg_phi=$4
dir_num=$6

phi_p=$beg_phi
phi_l=`echo "$phi_p + $haba" | bc -l`
dir_phi=$phi_l"_"$phi_p
cp F_cfreq $dir_phi
cp sin_cfreq_bi_ $dir_phi
cd $dir_phi
./F_cfreq $7 < sin_cfreq_bi_
cat "CharacteristicFrequency_"$addstr"EIGEnsAve_BR0.05_"$1"_"$2"BIN"$3".txt" >> ../$addstr$8
cd ../
for i in `seq 2 $dir_num`
do
    phi_p=$phi_l
    phi_l=`echo "$phi_p + $haba" | bc -l`
    dir_phi=$phi_l"_"$phi_p
    cp F_cfreq $dir_phi
    cp sin_cfreq_bi_ $dir_phi
    cd $dir_phi
    ./F_cfreq $7 < sin_cfreq_bi_
    cat "CharacteristicFrequency_"$addstr"EIGEnsAve_BR0.05_"$1"_"$2"BIN"$3".txt" >> ../$addstr$8
    cd ../
done



