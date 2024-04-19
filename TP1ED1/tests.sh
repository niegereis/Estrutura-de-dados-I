#\bin\sh

MEDIA=0
QTD=$1
DIMENSIONS=$2
echo "$DIMENSIONS $DIMENSIONS p" > case.in
echo "Serão realizados $QTD testes\n"
for i in $(seq 1 $QTD); do
  echo "Teste $i"
  # converter numero para shellscript
  
  RES=$(gcc *.c -o exe && ./exe random < case.in)
  echo "Valor em tempo $RES"
  MEDIA=$(($MEDIA+$RES))
  echo "$MEDIA"
done
MEDIA=$(echo "scale=2;$MEDIA/$QTD"|bc)
echo "MEDIA (DE $DIMENSIONS x $DIMENSIONS) => ${MEDIA}"
