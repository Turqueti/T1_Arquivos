#!/bin/bash

pastaDoTrab=/home/turqueti/Documents/Facul/2020.1/arquivos/trabalhos/T1
pathToProg=$pastaDoTrab/programaTrab
pastaCasosDeTeste=$pastaDoTrab/.Materiais/t2/Casos_test

# echo $pathToProg
cd $pastaDoTrab
if [ ! -f programaTrab ];then
    echo run make
else

    cd $pastaCasosDeTeste
    if [ -f programaTrab ];then
        rm programaTrab
        # echo removeu programaTrab
    fi

    if mv  $pathToProg  $pastaCasosDeTeste ; then
        $pastaDoTrab/.Tools/autoTester.sh $pastaCasosDeTeste/programaTrab $pastaCasosDeTeste -c
    fi

fi


