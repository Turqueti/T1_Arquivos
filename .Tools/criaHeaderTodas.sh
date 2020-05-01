#!/bin/bash

for f in *.c
do
if [ ! $f == "main.c" ]
    then
        ./.tools/criaheaderfile.sh $f

fi
done