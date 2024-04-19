#!/bin/bash

CURRENT_FILE=$(dirname "$(readlink -f "$0")")

gcc -g -o $CURRENT_FILE/prototype/exe $CURRENT_FILE/prototype/*.c -Wall

for file in $CURRENT_FILE/tests/*.in; do
  RES=$($CURRENT_FILE/prototype/exe < $file)
  OUT=$(cat ${file%.in}.out)
  
  FILE_NAME=$(echo "$file" | sed 's/.*\/caso//' | sed 's/\.in//' )

  if [[ "$RES" == "$OUT" ]]; then
    echo "Teste $FILE_NAME passou"
  else
    mkdir -p $CURRENT_FILE/failed-tests
    echo "$OUT" > $CURRENT_FILE/failed-tests/${FILE_NAME}.out
    echo "$RES" > $CURRENT_FILE/failed-tests/${FILE_NAME}.res

    printf "\n\tTeste $FILE_NAME falhou\n"
    echo "$(diff $CURRENT_FILE/failed-tests/${FILE_NAME}.out $CURRENT_FILE/failed-tests/${FILE_NAME}.res)"
    rm -rf $CURRENT_FILE/failed-tests
  fi
done