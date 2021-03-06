#!/bin/sh

echo "ソートして累積分布をoutput.txtに出力します.\n"
sort -nk1 $1 | tr '\n' ',' | sed -e "s/,/,\n/g" > TMPFILE_sorted.txt
export xxx=`wc -l $1 | cut -d' ' -f1`
#echo $xxx
export yyy=`echo 1.0/$xxx | bc -l `
#echo $yyy
echo $xxx"行あるTEXTについて処理します...\n"
echo -n > output.txt

for i in `seq 1 $xxx`
do
    zzz=`echo $yyy*$i | bc -l | sed -e 's/\./0./g'`
    ##echo $zzz
    cat TMPFILE_sorted.txt | sed -n -e `echo $i'p'` | sed -e "s/,/ $zzz/g" >> output.txt
done
