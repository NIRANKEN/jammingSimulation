#!/bin/sh

if [ $# -ne 1 ]; then
    echo "引数は1つでなければ"
    exit 1
fi

mkdir -p new
cat $1 | sed -e "s/"set\ format\ x\ \"%\ h\""/"set\ format\ x\ \"10^\{%L\}\""/g" | sed -e "s/"set\ format\ y\ \"%\ h\""/"set\ format\ y\ \"10^\{%L\}\""/g" > new/$1
