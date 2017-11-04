#!/bin/sh

if [ $# -ne 2 ]; then
    echo "引数が"$#"個宣言されています."
    echo "実行するには1個の引数を入れて下さい."
    echo "引数1: PHI-PHIJのrange"
    echo "引数2: 日付(e.g. 0409)"
    exit 1
fi

mkdir $1

echo $2 MONO 128 2D $1 | ./F_phiens
echo $2 MONO 256 2D $1 | ./F_phiens
echo $2 MONO 512 2D $1 | ./F_phiens
echo $2 MONO 1024 2D $1 | ./F_phiens
echo $2 MONO 128 3D $1 | ./F_phiens
echo $2 MONO 256 3D $1 | ./F_phiens
echo $2 MONO 512 3D $1 | ./F_phiens
echo $2 MONO 1024 3D $1 | ./F_phiens
echo $2 BI 128 2D $1 | ./F_phiens
echo $2 BI 256 2D $1 | ./F_phiens
echo $2 BI 512 2D $1 | ./F_phiens
echo $2 BI 1024 2D $1 | ./F_phiens
echo $2 BI 128 3D $1 | ./F_phiens
echo $2 BI 256 3D $1 | ./F_phiens
echo $2 BI 512 3D $1 | ./F_phiens
echo $2 BI 1024 3D $1 | ./F_phiens
