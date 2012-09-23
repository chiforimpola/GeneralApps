
#ifndef STRING_CPP
#define STRING_CPP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*******************************************
  Header que possui alguns metodo que
  auxiliam a manipular string
*******************************************/


char* toString(long int n)
{
  char *aux,
        value[50];
  //itoa(n, value, 10);
  sprintf (value, "%d", n);
  
  aux = (char *)malloc(strlen(value) + 1);
  strcpy(aux, value);
  
  return (aux);
}

unsigned int StringLengh(char *str)
{
  unsigned int i;
  for(i = 0;str[i] != '\0';i++){}
  return (i);
}


bool StringCompare(char *str, char *str2)
{
  unsigned int i;
  
  if( (StringLengh(str) < StringLengh(str2)) || (StringLengh(str2) < StringLengh(str)) )
    return (false);
  
  for(i = 0;str[i] != '\0';i++)
      if(str2[i] != str[i])
        return (false);

  return (true);
}

/*
  Comparacao de strings nao sendo
  case-sensitive
*/
bool StringCompareNoCase(char *str, char *str2)
{
  unsigned int i;
  
  if( (StringLengh(str) < StringLengh(str2)) || (StringLengh(str2) < StringLengh(str)) )
    return (false);
  
  for(i = 0;str[i] != '\0';i++)
  {
      if(str2[i] != str[i])
      {
        /*Caractere da primeira string é UpperCase*/
        if((int)str[i] >= 65 && (int)str[i] <= 90)
        {
          if( (int)str[i] != (int)(str2[i] - 32) )
            return (false);
        }
        
        /*Caractere da segunda string é UpperCase*/  
        else if((int)str2[i] >= 65 && (int)str2[i] <= 90)
        {
          if( (int)(str[i] - 32) != (int)str2[i] )
            return (false);
        }
            
        /*Caracters simplesmente sao diferentes*/
        else
          return (false);
      }
  }
  
  return (true);
}

#endif
