#!/bin/sh

if [ $# -ne 4 ]; then
        echo "引数は4個宣言してください."
        echo "引数1: Output file name(例: hogehoge.txt)"
        echo "引数2: 日付(例: 0510)"
        echo "引数3: 空間次元(例: 3D)"
        echo "引数4: 粒子数(例: 256)"
        exit 1
fi

echo "$2 BI $4 $3" > sin_ifreq_bi_


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

echo $2 BI $4 $3 $dir1 $dir2 | ./F_ifreq 0
echo $2 BI $4 $3 $dir1 $dir3 | ./F_ifreq 0
echo $2 BI $4 $3 $dir1 $dir4 | ./F_ifreq 0
echo $2 BI $4 $3 $dir1 $dir5 | ./F_ifreq 0
echo $2 BI $4 $3 $dir1 $dir6 | ./F_ifreq 0
echo $2 BI $4 $3 $dir1 $dir7 | ./F_ifreq 0
echo $2 BI $4 $3 $dir1 $dir8 | ./F_ifreq 0
echo $2 BI $4 $3 $dir1 $dir9 | ./F_ifreq 0
echo $2 BI $4 $3 $dir1 $dir10 | ./F_ifreq 0

str1="InvariantFreq_"$dir1"_"$dir2"_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt"
str2="InvariantFreq_"$dir1"_"$dir3"_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt"
str3="InvariantFreq_"$dir1"_"$dir4"_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt"
str4="InvariantFreq_"$dir1"_"$dir5"_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt"
str5="InvariantFreq_"$dir1"_"$dir6"_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt"
str6="InvariantFreq_"$dir1"_"$dir7"_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt"
str7="InvariantFreq_"$dir1"_"$dir8"_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt"
str8="InvariantFreq_"$dir1"_"$dir9"_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt"
str9="InvariantFreq_"$dir1"_"$dir10"_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt"

omega1=`cat "$str1" | cut -d' ' -f1`
omega2=`cat "$str2" | cut -d' ' -f1`
omega3=`cat "$str3" | cut -d' ' -f1`
omega4=`cat "$str4" | cut -d' ' -f1`
omega5=`cat "$str5" | cut -d' ' -f1`
omega6=`cat "$str6" | cut -d' ' -f1`
omega7=`cat "$str7" | cut -d' ' -f1`
omega8=`cat "$str8" | cut -d' ' -f1`
omega9=`cat "$str9" | cut -d' ' -f1`

DOS1=`cat "$str1" | cut -d' ' -f2`
DOS2=`cat "$str2" | cut -d' ' -f2`
DOS3=`cat "$str3" | cut -d' ' -f2`
DOS4=`cat "$str4" | cut -d' ' -f2`
DOS5=`cat "$str5" | cut -d' ' -f2`
DOS6=`cat "$str6" | cut -d' ' -f2`
DOS7=`cat "$str7" | cut -d' ' -f2`
DOS8=`cat "$str8" | cut -d' ' -f2`
DOS9=`cat "$str9" | cut -d' ' -f2`

omega_mean=`echo "( $omega1 + $omega2 + $omega3 + $omega4 + $omega5 + $omega6 + $omega7 + $omega8 + $omega9 )/9.0" | bc -l` 
DOS_mean=`echo "( $DOS1 + $DOS2 + $DOS3 + $DOS4 + $DOS5 + $DOS6 + $DOS7 + $DOS8 + $DOS9 )/9.0" | bc -l`
echo "0"$omega_mean $DOS_mean > "InvariantFreq_mean_"$2"_"$3"BIN"$4".txt"


cp F_cfreq2 1.5_1
cp F_cfreq2 2_1.5
cp F_cfreq2 2.5_2
cp F_cfreq2 3_2.5
cp F_cfreq2 3.5_3
cp F_cfreq2 4_3.5
cp F_cfreq2 4.5_4
cp F_cfreq2 5_4.5
cp F_cfreq2 5.5_5
cp F_cfreq2 6_5.5

cp sin_ifreq_bi_ 1.5_1
cp sin_ifreq_bi_ 2_1.5
cp sin_ifreq_bi_ 2.5_2
cp sin_ifreq_bi_ 3_2.5
cp sin_ifreq_bi_ 3.5_3
cp sin_ifreq_bi_ 4_3.5
cp sin_ifreq_bi_ 4.5_4
cp sin_ifreq_bi_ 5_4.5
cp sin_ifreq_bi_ 5.5_5
cp sin_ifreq_bi_ 6_5.5

cp "InvariantFreq_mean_"$2"_"$3"BIN"$4".txt" 1.5_1
cp "InvariantFreq_mean_"$2"_"$3"BIN"$4".txt" 2_1.5
cp "InvariantFreq_mean_"$2"_"$3"BIN"$4".txt" 2.5_2
cp "InvariantFreq_mean_"$2"_"$3"BIN"$4".txt" 3_2.5
cp "InvariantFreq_mean_"$2"_"$3"BIN"$4".txt" 3.5_3
cp "InvariantFreq_mean_"$2"_"$3"BIN"$4".txt" 4_3.5
cp "InvariantFreq_mean_"$2"_"$3"BIN"$4".txt" 4.5_4
cp "InvariantFreq_mean_"$2"_"$3"BIN"$4".txt" 5_4.5
cp "InvariantFreq_mean_"$2"_"$3"BIN"$4".txt" 5.5_5
cp "InvariantFreq_mean_"$2"_"$3"BIN"$4".txt" 6_5.5

cd 1.5_1
./F_cfreq2 0 < sin_ifreq_bi_
cd ../2_1.5
./F_cfreq2 0 < sin_ifreq_bi_
cd ../2.5_2
./F_cfreq2 0 < sin_ifreq_bi_
cd ../3_2.5
./F_cfreq2 0 < sin_ifreq_bi_
cd ../3.5_3
./F_cfreq2 0 < sin_ifreq_bi_
cd ../4_3.5
./F_cfreq2 0 < sin_ifreq_bi_
cd ../4.5_4
./F_cfreq2 0 < sin_ifreq_bi_
cd ../5_4.5
./F_cfreq2 0 < sin_ifreq_bi_
cd ../5.5_5
./F_cfreq2 0 < sin_ifreq_bi_
cd ../6_5.5
./F_cfreq2 0 < sin_ifreq_bi_
cd ../


echo "" > $1
cd 1.5_1/
cat "CharacteristicFrequency2_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt" >> ../$1
cd ../2_1.5/
cat "CharacteristicFrequency2_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt" >> ../$1
cd ../2.5_2/
cat "CharacteristicFrequency2_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt" >> ../$1
cd ../3_2.5/
cat "CharacteristicFrequency2_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt" >> ../$1
cd ../3.5_3/
cat "CharacteristicFrequency2_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt" >> ../$1
cd ../4_3.5/
cat "CharacteristicFrequency2_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt" >> ../$1
cd ../4.5_4/
cat "CharacteristicFrequency2_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt" >> ../$1
cd ../5_4.5/
cat "CharacteristicFrequency2_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt" >> ../$1
cd ../5.5_5/
cat "CharacteristicFrequency2_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt" >> ../$1
cd ../6_5.5/
cat "CharacteristicFrequency2_EIGEnsAve_BR0.05_"$2"_"$3"BIN"$4".txt" >> ../$1
cd ../
