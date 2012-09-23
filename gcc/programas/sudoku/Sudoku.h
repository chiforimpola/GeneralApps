
#ifndef SUDOKU_H
#define SUDOKU_H

#define SUDOKU_MAX_I       9
#define SUDOKU_MAX_J       9

struct Sudoku
{
  short int      grid[SUDOKU_MAX_I][SUDOKU_MAX_J];
  
  void resetGrid();
  int  getQuadrante(int row, int col);
  bool verificaQuadrante(int quad, int n);
  bool verificaRow(int row, int n);
  bool verificaCol(int col, int n);
  void init(short int dificudade);
  void print();
};

#endif
