#!/bin/bash

C_FILENAME=$1
ADT_NAME=$(echo $C_FILENAME |cut -f1 -d.)
H_FILENAME=$ADT_NAME".h"

echo "$C_FILENAME"

createTypeDefs(){

    awk '/^struct/{gsub(/\{/,"");print "typedef " $0 " "toupper(substr($2,2))";"}' $C_FILENAME
}

createFunctionHeaders(){
    awk '/^[^[:space:],s].*[\)\{]/{gsub(/\{/,"");gsub(/[[:space:]]$/,"");print $0";"}' $C_FILENAME
}

createDefine(){

    echo "#ifndef ${ADT_NAME^^}_H"
    echo "#define ${ADT_NAME^^}_H"
    echo
    createTypeDefs
    echo
    createFunctionHeaders
    echo
    echo "#endif"
}


createFile(){
    createDefine > $H_FILENAME
}

createEdToUpdateFile(){
    echo "$DIFF"    
    echo "w"
    echo "q"
}



if [ ! -f $C_FILENAME ] || [[ ! $C_FILENAME =~ .c$ ]]
then
    echo "usage: creatHeader file.c"
else
    
    if [ ! -f $H_FILENAME ]
    then
        createFile
    else
        DIFF=$(createDefine | diff $H_FILENAME - -I '^#' -B -e)
        #echo "$DIFF"
        if [ "$DIFF" ]
        then
        createEdToUpdateFile | ed $H_FILENAME -s
        fi
    fi


fi