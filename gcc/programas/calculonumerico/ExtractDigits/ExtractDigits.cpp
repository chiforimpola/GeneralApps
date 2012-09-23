
#define EXTRACT_DIGITS_CPP

#include <stdio.h>
#include <math.h>
#include <malloc.h>

unsigned long int contDigits(unsigned long int value)
{
  float         f;
  unsigned int  n,
                i,
                dif,
                aux,
                digits = 0;/*numero de digitos que [value] possui(-1)*/
  
  f = value;
  while((int)f != 0)
  {
    f /= 10;
    digits++;
  }
  return (digits);
}


/*
  numDigits:  Numero de digitos que se quer pegar
  index:      Em que digito quer comecar a pegar
  value:      Numero de onde se quer extrair os digitos
*/

    /*
    12345
    
    12 345
    
    12000
    
    345
    
    0.345
    */
  

unsigned int extractDigits(short int numDigits, short int index, unsigned int value)
{
  /*
    12345 >> 23
    
  */
  unsigned long int     n,
                        digits,
                        aux;
  volatile int          i;
  char                 *strN;
  
  digits  = contDigits(value);
  strN    = (char *)malloc(digits + 1);
  aux     = 10;
  
  for(i = digits-1;i >= 0;i--)
  {
    strN[i] = (int)(value / aux);
    printf("Digitos: %d\ndiv 10: %d\nStr: %c\n"
           "Val: %d", digits, aux, strN[i], (int)(value / aux));
    system("pause");
    aux    *= 10;
  }
}

int main()
{
  int n = extractDigits(2, 0, 54321);
  
  printf("\n<%d>\n", n);
  system("pause");
}

