

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#include "String.h"
#include "Sudoku.h"


void Sudoku :: init(short int dificudade)
{
  long int  i, j, n = 1;
  
  srand( time(NULL) );
  
  resetGrid();
  
  /* Comeco a Montar o Tabuleiro */
  for(i = 0;i < SUDOKU_MAX_I;i++)
  {
    for(j = 0;j < SUDOKU_MAX_J;j++)
    {
      n = rand() % 15+1;
      
      if(!verificaRow(i, n) || !verificaCol(j, n))
        j--;
      else
        grid[i][j] = n;
    }
  }
}

void Sudoku :: resetGrid()
{
  /* Zero o Tabuleiro */
  for(int i = 0;i < SUDOKU_MAX_I;i++)
    for(int j = 0;j < SUDOKU_MAX_J;j++)
      grid[i][j] = 0;
}


void Sudoku :: print()
{
  long int  i, j;
  
  for(i = 0;i < SUDOKU_MAX_I;i++)
  {
    for(j = 0;j < SUDOKU_MAX_J;j++) printf(" %d ", grid[i][j]);
    printf("\n");
  }
}

int Sudoku :: getQuadrante(int row, int col)
{
  if(row >= 0 && row <= 2)
  {
    if(col >= 0 && col <= 2) return (0);
    if(col >= 3 && col <= 5) return (1);
    if(col >= 6 && col <= 8) return (2);
  }
  
  else if(row >= 3 && row <= 5)
  {
    if(col >= 0 && col <= 2) return (3);
    if(col >= 3 && col <= 5) return (4);
    if(col >= 6 && col <= 8) return (5);
  }
  
  else if(row >= 6 && row <= 8)
  {
    if(col >= 0 && col <= 2) return (6);
    if(col >= 3 && col <= 5) return (7);
    if(col >= 6 && col <= 8) return (8);
  }
}

bool Sudoku :: verificaQuadrante(int quad, int n)
{
  int    i, j;
  
  if(quad >= 0 && quad < 9)
  {
    if(quad == 0)
    {
      for(i = 0;i < 3;i++)
        for(j = 0;j < 3;j++)
          if(grid[i][j] == n) return (false);
    }
    
    else if(quad == 1)
    {
      for(i = 0;i < 3;i++)
        for(j = 3;j < 6;j++)
          if(grid[i][j] == n) return (false);
    }
    
    else if(quad == 2)
    {
      for(i = 0;i < 3;i++)
        for(j = 6;j <= 8;j++)
          if(grid[i][j] == n) return (false);
    }
    
    else if(quad == 3)
    {
      for(i = 3;i < 6;i++)
        for(j = 0;j < 3;j++)
          if(grid[i][j] == n) return (false);
    }
    
    else if(quad == 4)
    {
      for(i = 3;i < 6;i++)
        for(j = 3;j < 6;j++)
          if(grid[i][j] == n) return (false);
    }
    
    else if(quad == 5)
    {
      for(i = 3;i < 6;i++)
        for(j = 6;j <= 8;j++)
          if(grid[i][j] == n) return (false);
    }
    
    else if(quad == 6)
    {
      for(i = 6;i <= 8;i++)
        for(j = 0;j < 3;j++)
          if(grid[i][j] == n) return (false);
    }
    
    else if(quad == 7)
    {
      for(i = 6;i <= 8;i++)
        for(j = 3;j < 6;j++)
          if(grid[i][j] == n) return (false);
    }
    
    else if(quad == 8)
    {
      for(i = 6;i <= 8;i++)
        for(j = 6;j <= 8;j++)
          if(grid[i][j] == n) return (false);
    }
  }
  else
    return (false);
  
  return (true);
}


bool Sudoku :: verificaRow(int row, int n)
{
  short int   j;
  
  for(j = 0;j < SUDOKU_MAX_J;j++)
    if(grid[row][j] == n)
      return (false);
  
  return (true);
}


bool Sudoku :: verificaCol(int col, int n)
{
  short int   i;
  
  for(i = 0;i < SUDOKU_MAX_I;i++)
    if(grid[i][col] == n)
      return (false);
  
  return (true);
}


int main()
{
  Sudoku s;
  
  s.init(1);
  s.print();
}
