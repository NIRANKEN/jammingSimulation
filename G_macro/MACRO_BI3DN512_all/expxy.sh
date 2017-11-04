#!/bin/sh

if [ $# -eq 1 ]; then
    mkdir -p new
    cat $1 | sed -e "s/"set\ format\ x\ \"%\ h\""/"set\ format\ x\ \"10^\{%L\}\""/g" | sed -e "s/"set\ format\ y\ \"%\ h\""/"set\ format\ y\ \"10^\{%L\}\""/g" > new/$1
elif [ $# -eq 3 ]; then
name=`ls $1 | sed -e "s/$2/$3/g"`
mkdir -p new
cat $1 | sed -e "s/"set\ format\ x\ \"%\ h\""/"set\ format\ x\ \"10^\{%L\}\""/g" | sed -e "s/"set\ format\ y\ \"%\ h\""/"set\ format\ y\ \"10^\{%L\}\""/g" | sed -e "s/$2/$3/g" > new/$name
else
    echo "宣言は一個かさんこ"
    exit 1
fi
