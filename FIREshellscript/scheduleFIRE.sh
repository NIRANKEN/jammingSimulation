#!/bin/sh

if [ $# -ne 8 ]; then
    echo "指定された引数は$#個です." 1>&2
    echo "実行するには$#個の引数が必要です." 1>&2
    echo "第一引数 -> dimension" 1>&2
    echo "第二引数 -> BI or MONO(e.g. 1.0, 1.4, ..." 1>&2
    echo "第三引数 -> the number of particles" 1>&2
    echo "第四引数 -> 第1種の粒子比I (I:II)" 1>&2
    echo "第五引数 -> 第2種の粒子比II (I:II)" 1>&2
    echo "第六引数 -> 開始seed値" 1>&2
    echo "第七引数 -> サンプル間隔()" 1>&2
    echo "第八引数 -> 使用するのーみその数" 1>&2
    exit 1
fi

if [ `echo "$2 == 1.0" | bc` -eq 1 ]; then
    zzz=MONO
else
    zzz=BI    
fi

if [ $3 -eq 64 ]; then
:
elif [ $3 -eq 128 ]; then
:
elif [ $3 -eq 256 ]; then
:
elif [ $3 -eq 512 ]; then
:
elif [ $3 -eq 1024 ]; then
:
elif [ $3 -eq 2048 ]; then
:
elif [ $3 -eq 4096 ]; then
:
else
    echo "粒子数"$3"の値が不正です." 1>&2
    exit 1
fi

dim=$1
phi_beg=0
if [ $dim -eq 2 ]; then
    phi_beg=1.0
elif [ $dim -eq 3 ]; then
    phi_beg=0.8
else
    echo "2D, 3D以外はサポートしていません." 1>&2
    exit 1
fi

echo "#!/bin/sh" > "FIRE_"$zzz$1"DN"$3"_"$4":"$5".sh"
echo -e "\n" >> "FIRE_"$zzz$1"DN"$3"_"$4":"$5".sh"
xxx=$6
yyy=$(($6+$7))

for i in `seq 1 $8`
    do
        echo  "./VVFIRE "$xxx" "$yyy" $phi_beg 0.6 -0.05 "$3" "$1" "$2" "$4" "$5" &" >> "FIRE_"$zzz$1"DN"$3"_"$4":"$5".sh"
        xxx=$yyy
        yyy=$((yyy+$7))
done

vvv="FIRE_"$zzz$1"DN"$3"_"$4":"$5".sh" 
chmod 755 $vvv

Fdir=""
if [ $4 -eq 1 ] && [ $5 -eq 1 ]; then ## BI1:1
    Fdir="$zzz$1"DN"$3"
elif [ $5 -eq 0 ]; then  ## MONO 
    Fdir="$1"DN"$3"
else ## BI $4:$5
    Fdir="$zzz$1"DN"$3"_"$4":"$5"
fi

if [ -d $Fdir ]; then
    mv $vvv "$Fdir"
else
  echo "$Fdir""は存在していません." 1>&2
fi
