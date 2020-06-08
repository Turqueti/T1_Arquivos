#!/bin/bash

pastaDoTrab=/home/turqueti/Documents/2020.1/facul/arquivos/T1_Arquivos
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
        cp $pastaDoTrab/.Binarios/* $pastaCasosDeTeste
        $pastaDoTrab/.Tools/autoTester.sh $pastaCasosDeTeste/programaTrab $pastaCasosDeTeste -c
    fi

fi


