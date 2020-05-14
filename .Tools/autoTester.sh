#!/bin/bash

function default() {
    i=$start
    while [[ $i -le $numcasos ]]
    do
        $prog < $pathToTests/$i.in > /tmp/testfile

        if ! cmp -s /tmp/testfile $pathToTests/$i.out
            then
                echo $i.in
        fi

        ((i = i + 1))
    done
}

function color() {
    i=$start
    while [[ $i -le $numcasos ]]
    do
        $prog < $pathToTests/$i.in > /tmp/testfile

        if cmp -s /tmp/testfile $pathToTests/$i.out
            then
                echo -e  "\e[32m$i.in"
        else
            echo -e "\e[31m$i.in"
        fi

        ((i = i + 1))
    done
}

function uso() {
    if [ $flagUso -eq 0 ];then
    echo "uso: autoTester programa pasta_casos_de_teste [-options]"
    flagUso=1
    fi
}

flagUso=0

if [ $# -eq 0 ];then
    uso
    exit
fi
if [ ! -x $1 ];then

    uso    
    echo programa nao eh um executavel
    exit

else
    prog=$PWD/$1
fi
shift
if [ ! -d $1 ];then
    
    uso
    echo pasta_casos_de_teste nao eh uma pasta
    exit

else
    pathToTests=$PWD/$1 #caminho para pasta dos casos de teste sendo $PWD a pasta em que o programa foi executado
    numcasos=$(ls $pathToTests -l| grep "\.in"|wc -l) #numero de casos de teste
    start=1

fi
shift

if [ ! -n "$1" ];then
    default
else

    while [ -n "$1" ]; do # while loop starts

        case "$1" in

        -c) color ;; # executa a func color

        *) echo "Opcao $1 nao reconhecida" ;; #caso a func n~ao seja implementada

        esac

        shift

    done

fi
