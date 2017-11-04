#!/bin/sh

if [ $# -ne 1 ]; then
    echo "指定された引数は$#個です." 1>&2
    echo "実行するには$#個の引数が必要です." 1>&2
    echo "第一引数 -> 日付(e.g. 0227)" 1>&2
    exit 1
fi

if [ ! -e ~/sagyo2017$1 ]; then
    echo "ディレクトリ(~/sagyo2017$1)が存在しません." 1>&2
    echo "作業ディレクトリを(~/sagyo2017$1)としてshellを実行してください."
    exit 1
fi

mkdir ~/TEST$1
#mkdir ~/TEST$1/2DN128
#mkdir ~/TEST$1/2DN256
#mkdir ~/TEST$1/2DN512
#mkdir ~/TEST$1/2DN1024
mkdir ~/TEST$1/3DN64
mkdir ~/TEST$1/3DN128
mkdir ~/TEST$1/3DN256
mkdir ~/TEST$1/3DN512
mkdir ~/TEST$1/3DN1024
mkdir ~/TEST$1/3DN2048
mkdir ~/TEST$1/3DN4096
mkdir ~/TEST$1/BI3DN64
mkdir ~/TEST$1/BI3DN128
mkdir ~/TEST$1/BI3DN256
mkdir ~/TEST$1/BI3DN512
mkdir ~/TEST$1/BI3DN1024
mkdir ~/TEST$1/BI3DN2048
mkdir ~/TEST$1/BI3DN4096
#mkdir ~/TEST$1/BI2DN128
mkdir ~/TEST$1/BI2DN256
#mkdir ~/TEST$1/BI2DN512
#mkdir ~/TEST$1/BI2DN1024
#mkdir ~/TEST$1/BI3DN256_1:3
#mkdir ~/TEST$1/BI3DN256_3:1
#mkdir ~/TEST$1/BI3DN256_0:1
cp ~/sagyo2017$1/FIREshellscript/FIREcp.sh ~/TEST$1/
cp ~/sagyo2017$1/FIREshellscript/scheduleFIRE.sh ~/TEST$1/
cp ~/sagyo2017$1/FIREshellscript/FIRE_errsampleremove.sh ~/TEST$1/
cp ~/sagyo2017$1/FIREprogram/*.cpp ~/TEST$1
cp ~/sagyo2017$1/FIREprogram/*.h ~/TEST$1

cd ~/TEST$1/
./scheduleFIRE.sh 3 1.4 64 1 1 0 10 1
./scheduleFIRE.sh 3 1.4 128 1 1 0 5 1
./scheduleFIRE.sh 3 1.4 256 1 1 0 3 1
./scheduleFIRE.sh 3 1.4 512 1 1 0 2 1
./scheduleFIRE.sh 3 1.4 1024 1 1 0 1 1
./scheduleFIRE.sh 3 1.4 2048 1 1 0 1 1
./scheduleFIRE.sh 3 1.4 4096 1 1 0 1 1
echo "HOST NAME IS $HOSTNAME"
if [ $HOSTNAME -eq "bear" ]; then
  sed -e "%s/pow(2/pow(2.0/g" TestProgram_FVVmodified.cpp > FVVmod.cpp
  sed -e "%s/pow(2/pow(2.0/g" velver.h > vv.h
  cat vv.h > velver.h
  icpc -fast FVVmod.cpp -o VVFIRE
else
  icpc -fast TestProgram_FVVmodified.cpp -o VVFIRE
fi  
