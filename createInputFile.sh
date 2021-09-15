#!/bin/bash

args=("$@")

FILE=${args[0]}
if [ -f "$FILE" ]; then
    echo "$FILE exists."
else 
    echo "$FILE does not exist."
fi

FILE=${args[1]}
if [ -f "$FILE" ]; then
    echo "$FILE exists."
else 
    echo "$FILE does not exist."
fi

if [ $# -le 3 ]
  then
    echo "No all arguments supplied"
  else 
    echo "All arguments supplied"  
fi

FILE=inputFile.txt
if [ -f "$FILE" ]; then
    echo "$FILE exists. Delete old File and create new"
    rm -rf inputFile.txt
    touch inputFile.txt
else 
    echo "$FILE does not exist."
    touch inputFile.txt
fi

duplicate=${args[3]}
counter=1
RANGE=9999
T=1
RANGEAGE=120
BINARY=2

CFILE="countriesFile.txt"
VFILE="virusesFile.txt"
while [ $counter -le ${args[2]} ]
do

if [ $duplicate -eq 1 ]
then

    result="NO"
    num=$RANDOM
    let "num %=$BINARY"


    if [ "$num" -eq $T ]
    then
      result="YES"
    else
      reuslt="NO"
    fi
      age=$RANDOM
      ids=$RANDOM

      charsName=$((4+RANDOM%9))
      charsSur=$((4+RANDOM%9))
      day=$(date \-d "$((2000+RANDOM%22))-$((RANDOM%12+1))-$((RANDOM%28+1))" '+%d/%m/%Y')
      
      let "ids %= $RANGE"
      let "age %= $RANGEAGE"

      country=$(shuf \-n 1 ${CFILE})
      virus=$(shuf \-n 1 ${VFILE})
      name=$(cat \/dev/urandom | tr \-dc A-Z | head \-c ${charsName})
      surname=$(cat \/dev/urandom | tr \-dc A-Z | head \-c ${charsSur})
      if [ "$num" -eq $T ]
      then
        echo "$ids $name $surname ${country} $age ${virus} $result $day" >> inputFile.txt
      else
        echo "$ids $name $surname ${country} $age ${virus} $result" >> inputFile.txt
      fi  
      ((counter++))
else
result="NO"
    num=$RANDOM
    let "num %=$BINARY"


    if [ "$num" -eq $T ]
    then
      result="YES"
    else
      reuslt="NO"
    fi
      age=$RANDOM
      ids=$counter

      charsName=$((4+RANDOM%9))
      charsSur=$((4+RANDOM%9))
      day=$(date \-d "$((2000+RANDOM%22))-$((RANDOM%12+1))-$((RANDOM%28+1))" '+%d/%m/%Y')
      
      let "ids %= $RANGE"
      let "age %= $RANGEAGE"

      country=$(shuf \-n 1 ${CFILE})
      virus=$(shuf \-n 1 ${VFILE})
      name=$(cat \/dev/urandom | tr \-dc A-Z | head \-c ${charsName})
      surname=$(cat \/dev/urandom | tr \-dc A-Z | head \-c ${charsSur})
      if [ "$num" -eq $T ]
      then
        echo "$ids $name $surname ${country} $age ${virus} $result $day" >> inputFile.txt
      else
        echo "$ids $name $surname ${country} $age ${virus} $result" >> inputFile.txt
      fi  
      ((counter++))
fi      

done

