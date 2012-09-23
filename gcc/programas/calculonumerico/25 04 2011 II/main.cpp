

#include <stdlib.h>
#include <stdio.h>

#include "src\String.cpp"
#include "src\ExtractDigits.h"
#include "src\ExtractPairFromFourDigits.h"

int main()
{
  unsigned long int     LIMIT = 9999,
                        n, n2,/*Pares de Digitos[1º e 2º]*/
                        sum, exp;/*Resultado da Exponenciacao*/
  volatile long int     i;
  
  for(i = 1000;i < LIMIT;i++)
  {
    /*printf("\t[ %d ]\n%d - %d, %d\n", 
      i,
      extractDigits(2, 0, i),
      extractDigits(1, 2, i),
      contDigits(i));
    n    = extractDigits(2, 0, i);
    n2   = extractDigits(2, (contDigits(i) - 2), i);
    */
    n = extractFirstPair(i);
    n2 = extractLastPair(i);
    sum  = n + n2;
    exp  = sum * sum;
    if(exp == i)
      printf(
                   "\n\n\t\t[ %d ]\n\n"
                   "-> %d + %d = %d\n"
                   "%d^2       = %d",
                   i, n, n2, sum, sum, exp);
  }
  
  system("pause");
}
