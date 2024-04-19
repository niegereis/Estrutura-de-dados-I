#!/bin/bash

CURRENT_FILE=$(dirname "$(readlink -f "$0")")

make


if [[ -d $CURRENT_FILE/failed-tests ]]; then
  rm -rf $CURRENT_FILE/failed-tests
fi
mkdir -p $CURRENT_FILE/failed-tests

printf "\n"
printf "\t\tTESTES TP2ED1"
printf "\n"

for file in $CURRENT_FILE/tests/*.in; do
  RES=$($CURRENT_FILE/exe < $file)
  FILE_NAME=$(echo "$file" | sed 's/.*\/tests\///' | sed 's/\.in//')

  if [[ ! -f ${file%.in}.out ]]; then
    printf "\tNÃO EXISTE ${file%.in}.out"
    continue
  fi

  OUT=$(cat ${file%.in}.out)

  if [[ "$RES" == "$OUT" ]]; then
    printf "TESTE \e[32m$FILE_NAME\e[0m passou\n"
  else
    echo "Experado:" > $CURRENT_FILE/failed-tests/${FILE_NAME}.out
    echo "$OUT" >> $CURRENT_FILE/failed-tests/${FILE_NAME}.out
    echo "" >> $CURRENT_FILE/failed-tests/${FILE_NAME}.out
    echo "Recebido:" >> $CURRENT_FILE/failed-tests/${FILE_NAME}.out
    echo "$RES" >> $CURRENT_FILE/failed-tests/${FILE_NAME}.out
    echo "" >> $CURRENT_FILE/failed-tests/${FILE_NAME}.out

    echo "$RES" > $CURRENT_FILE/failed-tests/${FILE_NAME}.res
    echo "$OUT" > $CURRENT_FILE/failed-tests/${FILE_NAME}.expout
  
    printf "Teste \e[31m$FILE_NAME\e[0m falhou\n"
  
    diff -u $CURRENT_FILE/failed-tests/${FILE_NAME}.res $CURRENT_FILE/failed-tests/${FILE_NAME}.expout
    rm $CURRENT_FILE/failed-tests/${FILE_NAME}.res
    rm $CURRENT_FILE/failed-tests/${FILE_NAME}.expout

   fi
done

echo ""

if [[ ! "$(ls -A $CURRENT_FILE/failed-tests)" ]]; then
  rm -rf $CURRENT_FILE/failed-tests
fi
