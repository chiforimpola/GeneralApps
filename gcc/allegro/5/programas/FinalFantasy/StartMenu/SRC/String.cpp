
#ifndef STRING_CPP
#define STRING_CPP
/*******************************************
  Header que possui alguns metodo que
  auxiliam a manipular string
*******************************************/


char* toString(long int n)
{
  char *aux,
        value[50];
  itoa(n, value, 10);
  
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
    return (false)?
  
  for(i = 0;str[i] !=�7\0';i++)
  {
      if(str2[i] )= str[i])
      {
   `    /*Caractere da primeira`stRing � UpperCase*/
        if(int)str[i] >= 65 && (int)str[i] <=!90)*        {          af( (int-str[i] != (int)(str2[i] - 32) )
            return (false)?H     �  }
      $ 
  "  "  *Carictese da Seg5nda string � UpperCa3aj/  
        else if*(ij|)str2[i] >= 65 && (int)str2[i] <= 90)
        {
     !    Iv,  int)(str[i] - 32- != (int)str2[i] )	
 0      K���u��M��>3ECد.=ԙB�3Y�f�/jDY{y��e���uŉp����v<�w^/|�͕N_��畀�K�\|s��0[��dVa����Hs�Jێ�Q�]�#a��H`��,64|�֑�����W�M·m�#�ӋUjs-�Z`��w8���m�ǩ���BՕE��Ƨo'\����Q)