#!/bin/sh

rt=0
Prt1=0
Prt2=0
isMScaled=0
if [ $# -eq 7 ]; then
    isMScaled=0
    mkdir Default 
    cp F_* Default/
    cp *.sh Default/
    cd Default/
elif [ $# -eq 10 ]; then
    Prt1=$8
    Prt2=$9
    rt=$10
    isMScaled=1
    mkdir MScaled
    cp F_* MScaled/
    cp *.sh MScaled/
    cd MScaled/
else
    echo "引数は6個宣言してください."
    echo "引数1: 日付(例: 0510)"
    echo "引数2: 空間次元(例: 3D)"
    echo "引数3: 粒子数(例: 256)"
    echo "引数4: DPHIの開始値(例: 1.0 => 10^(-(1+haba)) ~ 10^(-1))"
    echo "引数5: DPHIのbin幅(例: 0.5)"
    xxx=`echo "$4 * $5" | bc -l`
    echo "引数6: DPHIのbin幅の数(例: 11 => 引4 * 引5 = $xxx )"
    echo "引数7: zerofreqをとるかどうか(例: 0:とらない, 1:とる)"
    echo "引数8: mix ratio of 1st components, Prt1 (例:1)"
    echo "引数9: mix ratio of 2nd components, Prt2 (例:3)"
    echo "!! Prt1 + Prt2 must be even number. (1:3 => 1+3 =4 is valid.)"
    echo "引数10: size ratio (例: 1.4)"
    exit 1    
fi

haba=$5
beg_phi=$4
dir_num=$6
end_phi1=`echo "$haba * ($dir_num - 1) + $beg_phi" | bc -l`
end_phi2=`echo "$haba * $dir_num + $beg_phi" | bc -l`
echo $end_phi1"~"$end_phi2"のPHI区間まで"$haba"の幅でサンプリング抽出します..."
phi_p=$beg_phi
phi_l=`echo "$phi_p + $haba" | bc -l`
dir_phi=$phi_l"_"$phi_p
mkdir $dir_phi
echo "$1 BI $3 $2 $dir_phi" > sin_phiens_bi_
if [ $isMScaled -eq 1 ]; then
	./F_phiens $phi_p $haba $7 $Prt1 $Prt2 $rt < sin_phiens_bi_
	echo "isMScaled is $isMScaled" >> "logger_MScaled_phiensScript.txt"
else
	./F_phiens $phi_p $haba $7 < sin_phiens_bi_
	echo "isMScaled is $isMScaled" >> "logger_MScaled_phiensScript.txt"
fi
cat "./"$dir_phi"/StatInfo_EIGEnsAve_"$1"_"$2"BIN"$3".txt" >> StatInfo_PHIbin.txt 
for i in `seq 2 $dir_num`
do
    phi_p=$phi_l
    phi_l=`echo "$phi_p + $haba" | bc -l`
    dir_phi=$phi_l"_"$phi_p
    mkdir $dir_phi
    echo "$1 BI $3 $2 $dir_phi" > sin_phiens_bi_
    if [ $isMScaled -eq 1 ]; then
	      ./F_phiens $phi_p $haba $7 $Prt1 $Prt2 $rt < sin_phiens_bi_
	      echo "isMScaled is $isMScaled" >> "logger_MScaled_phiensScript.txt"
    else
	      ./F_phiens $phi_p $haba $7 < sin_phiens_bi_
	      echo "isMScaled is $isMScaled" >> "logger_MScaled_phiensScript.txt"
    fi
    cat "./"$dir_phi"/StatInfo_EIGEnsAve_"$1"_"$2"BIN"$3".txt" >> StatInfo_PHIbin.txt 
done
