
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "String.h"
#include "MathGame.h"

long int MathGame :: getRowSum(short int row)
{
  long int   i, sum = 0;
  
  for(i = 0;i < MATH_GAME_DIMENSION;i++)
  {
    if(array[row][i] != MATH_GAME_RESET_NUMBER)
      sum += array[row][i];
    else
      return (0);
  }
  
  return (sum);
}


long int MathGame :: getColSum(short int col)
{
  long int   i, sum = 0;
  
  for(i = 0;i < MATH_GAME_DIMENSION;i++)
  {
    if(array[i][col] != MATH_GAME_RESET_NUMBER)
      sum += array[i][col];
    else
      return (0);
  }
  
  return (sum);
}

bool MathGame :: hasWon()
{
  volatile int    i;
  
  for(i = 0;i < MATH_GAME_DIMENSION;i++)
    if(getRowSum(i) != firstSum && getColSum(i) != firstSum)
      return (false);
  
  return (true);
}

bool MathGame :: wasEmpty(long int i, long int j)
{
  for(int i2 = 0;i2 < iempty;i2++)
    if(empty[i2][0] == i && empty[i2][1] == j)
      return (true);
  
  return (false);
}


void MathGame :: init(long int max, short int dificuldade)
{
  long int   i, j,
             n, 
             aux,
             empty2;
  
  iempty = firstSum = 0;
  
  for(i = 0;i < MATH_GAME_DIMENSION;i++)
    for(j = 0;j < MATH_GAME_DIMENSION;j++)
      array[i][j] = 0;
  
  srand( time(NULL) );
  
  for(j = 0;j < MATH_GAME_DIMENSION;j++)
  {
    n = rand() % max + 1;
    array[0][j] = n;
  }
  firstSum = getRowSum(0);
  
  for(i = 1;i < MATH_GAME_DIMENSION - 1;i++)
  {
    n = rand() % max + 1;
    array[i][0] = n;
  }
  
  aux = firstSum;
  for(i = 0;i < MATH_GAME_DIMENSION - 1;i++)
    aux -= array[i][0];
  array[i][0] = aux;
  
  /* Monto as outras linhas/colunas */
  for(i = 1;i < MATH_GAME_DIMENSION;i++)
  {
    if(i < MATH_GAME_DIMENSION - 1)
    {
      for(j = 1;j < MATH_GAME_DIMENSION - 1;j++)
        array[i][j] = rand() % max + 1;
    
      aux = firstSum;
      for(int i2 = 1;i2 < MATH_GAME_DIMENSION - 1;i2++)
        aux -= array[i][i2];
      array[i][j] = aux;
    }
    else
    {
      for(j = 1;j < MATH_GAME_DIMENSION;j++)
      {
        aux = firstSum;
        for(int i2 = 0;i2 < MATH_GAME_DIMENSION - 1;i2++)
          aux -= array[i2][j];
        array[i][j] = aux;
      }
    }
  }
  
  /* Escondo [dificult] numeros da grid */
  iempty = 0;
  for(int n = 0;n < dificuldade;n++)
  {
    i = j = 0;
    while(array[i][j] == MATH_GAME_RESET_NUMBER)
    {
      i = rand() % MATH_GAME_DIMENSION;
      j = rand() % MATH_GAME_DIMENSION;
    }
    array[i][j] = MATH_GAME_RESET_NUMBER;
    empty[iempty][0] = i;
    empty[iempty][1] = j;
    iempty++;
  }
}


void MathGame :: print()
{
  for(int i = 0;i < MATH_GAME_DIMENSION;i++)
  {
    for(int j = 0;j < MATH_GAME_DIMENSION;j++)
    {
      if(array[i][j] == MATH_GAME_RESET_NUMBER)
        printf(" [?] ");
      else
        printf(" [%d] ", array[i][j]);
    }
    printf("\n");
  }
}



