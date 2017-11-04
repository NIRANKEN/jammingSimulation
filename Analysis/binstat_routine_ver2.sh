#!/bin/sh

if [ $# -ne 7 ]; then
    echo "引数は7個宣言してください."
    echo "引数1: 日付(例: 0510)"
    echo "引数2: 空間次元(例: 3D)"
    echo "引数3: 粒子数(例: 256)"
    echo "引数4: DPHIの開始値(例: 1.0 => 10^(-(1+haba)) ~ 10^(-1))"
    echo "引数5: DPHIのbin幅(例: 0.5)"
    xxx=`echo "$4 * $5" | bc -l`
    echo "引数6: DPHIのbin幅の数(例: 11 => 引4 * 引5 = $xxx )"
    echo "引数7: omegaのbin幅(例: 0.05)"
    exit 1
fi

echo "$1 BI $3 $2" > sin_binstat_bi_
haba=$5
beg_phi=$4
dir_num=$6
SM_range=2 #default
SM_tei=2 #default

#end_phi1=`echo "$haba * ($dir_num - 1) + $beg_phi" | bc -l`
#end_phi2=`echo "$haba * $dir_num + $beg_phi" | bc -l`
#echo $end_phi1"~"$end_phi2"のPHI区間まで"$haba"の幅でサンプリング抽出します..."
phi_p=$beg_phi
phi_l=`echo "$phi_p + $haba" | bc -l`
dir_phi=$phi_l"_"$phi_p
cp F_binstat $dir_phi
cp F_smooth $dir_phi
cp sin_binstat_bi_ $dir_phi
cd $dir_phi
./F_binstat $7 < sin_binstat_bi_
./F_smooth $SM_range $SM_tei < sin_binstat_bi_
cd ../
#./F_phiens $phi_p $haba < sin_phiens_bi_ 
for i in `seq 2 $dir_num`
do
    phi_p=$phi_l
    phi_l=`echo "$phi_p + $haba" | bc -l`
    dir_phi=$phi_l"_"$phi_p
    cp F_binstat $dir_phi
    cp F_smooth $dir_phi
    cp sin_binstat_bi_ $dir_phi
    cd $dir_phi
    ./F_binstat $7 < sin_binstat_bi_
    ./F_smooth $SM_range $SM_tei < sin_binstat_bi_
    cd ../
done
