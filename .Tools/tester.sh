#!/bin/bash

pastaDoTrab=/home/turqueti/Documents/Facul/2020.1/arquivos/trabalhos/T1
pathToProg=$pastaDoTrab/programaTrab
pastaCasosDeTeste=$pastaDoTrab/.Materiais/Casos_test

# echo $pathToProg
cd $pastaDoTrab
if [ ! -f programaTrab ];then
    echo run make
else

    cd $pastaDoTrab/.Materiais/Casos_test
    if [ -f programaTrab ];then
        rm programaTrab
        # echo removeu programaTrab
    fi

    if mv  $pathToProg  $pastaCasosDeTeste ; then
        $pastaDoTrab/.Tools/autoTester.sh $pastaCasosDeTeste/programaTrab $pastaCasosDeTeste -c
    fi

fi


