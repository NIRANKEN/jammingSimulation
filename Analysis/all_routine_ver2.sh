#!/bin/sh

if [ $# -eq 4 ]; then
    out1="cfreq.txt"
    out2="cfreq2.txt"
    #DOStype=1
    phi_beg=1.0
    phi_haba=0.5
    phi_num=11
    omega_haba=0.05
    if [ $1 -eq 0 ]; then
       ./phiens_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num
    else
      echo "第一引数は 0 にしてください.."
      exit 1
    fi
    ## ./phiens_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num
    ./binstat_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num $omega_haba
    ./cfreq_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num 0 $out1
    ./cfreq_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num 1 $out1
    ./ifreq_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num 0 $out2
    ./ifreq_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num 1 $out2
    ./addstat_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num 0
    ./addstat_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num 1
    echo "$2 BI $4 $3" | ./F_phijcum

elif [ $# -eq 7 ]; then
    out1="cfreq.txt"
    out2="cfreq2.txt"
    #DOStype=1
    phi_beg=1.0
    phi_haba=0.5
    phi_num=11
    omega_haba=0.05
    path="./"
    if [ $1 -eq 0 ]; then
       ./phiens_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num
    elif [ $1 -eq 1 ]; then
       ./phiens_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num $5 $6 $7
       cd ./MScaled
    else
      echo "第一引数は 0 or 1 です."
      exit 1
    fi

    ## ./phiens_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num
    ./binstat_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num $omega_haba
    ./cfreq_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num 0 $out1
    ./cfreq_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num 1 $out1
    ./ifreq_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num 0 $out2
    ./ifreq_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num 1 $out2
    ./addstat_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num 0
    ./addstat_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num 1
    echo "$2 BI $4 $3" | ./F_phijcum 
elif [ $# -eq 9 ]; then
    phi_beg=1.0
    phi_haba=0.5
    phi_num=11
    omega_haba=0.05
    if [ $1 -eq 0 ]; then
       ./phiens_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num
    elif [ $1 -eq 1 ]; then
       ./phiens_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num $5 $6 $7
       cd ./MScaled
    else
      echo "第一引数は 0 or 1 です."
      exit 1
    fi
    ./binstat_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num $omega_haba
    ./cfreq_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num 0 $8 
    ./cfreq_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num 1 $8 
    ./ifreq_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num 0 $9
    ./ifreq_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num 1 $9
    ./addstat_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num 0 
    ./addstat_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num 1
    echo "$2 BI $4 $3" | ./F_phijcum 

elif [ $# -eq 10 ]; then
    phi_beg=1.0
    phi_haba=0.5
    phi_num=11
    omega_haba=0.05
    if [ $1 -eq 0 ]; then
       ./phiens_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num
    elif [ $1 -eq 1 ]; then
       ./phiens_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num $5 $6 $7
       cd ./MScaled
    else
      echo "第一引数は 0 or 1 です."
      exit 1
    fi
    ./binstat_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num $omega_haba
    ./cfreq_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num ${10} $8 
    ./ifreq_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num ${10} $9
    ./addstat_routine_ver2.sh $2 $3 $4 $phi_beg $phi_haba $phi_num ${10}
    echo "$2 BI $4 $3" | ./F_phijcum 
 
elif [ $# -eq 14 ]; then
    ./phiens_routine_ver2.sh $2 $3 $4 ${11} ${12} ${13}
    ./binstat_routine_ver2.sh $2 $3 $4 ${11} ${12} ${13} ${14}
    ./cfreq_routine_ver2.sh $2 $3 $4 ${11} ${12} ${13} ${10} $8 
    ./ifreq_routine_ver2.sh $2 $3 $4 ${11} ${12} ${13} ${10} $9
    ./addstat_routine_ver2.sh $2 $3 $4 ${11} ${12} ${13} ${11}
    echo "$2 BI $4 $3" | ./F_phijcum 

else
    echo "引数は4or7or9or10or14個宣言してください."
    echo "引数1: 固有振動数の出力モード(例: 0->normal, 1->MScaled)"
    echo "引数2: 日付(例: 0510)"
    echo "引数3: 空間次元(例: 3D)"
    echo "引数4: 粒子数(例: 256)"
    echo "引数5: 成分1の混合比 (例:1)" 
    echo "引数6: 成分2の混合比 (例:1)" 
    echo "引数7: 成分1と成分2のサイズ比 (例:1.4)"
    echo "引数8: cfreq Output file name(例: hogehoge.txt)"
    echo "引数9: cfreq2 Output file name(例: hogehoge2.txt)"
    echo "引数10: Smoothed DOS or not (0=>normal DOS, 1=>smoothed DOS)"
    echo "引数11: DPHIの開始値(例: 1.0 => 10^(-(1+haba)) ~ 10^(-1))"
    echo "引数12: DPHIのbin幅(例: 0.5)"
    #xxx=`echo "$9 * ${10}" | bc -l`
    echo "引数13: DPHIのbin幅の数(例: 11 => 引7 * 引8のDPHI値まで)"
    echo "引数14: omegaのbin幅(例: 0.05)"
    exit 1
fi