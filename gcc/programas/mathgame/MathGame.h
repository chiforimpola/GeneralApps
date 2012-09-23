
#ifndef MATH_GAME_H
#define MATH_GAME_H

#define MATH_GAME_DIMENSION      5
#define MATH_GAME_RESET_NUMBER   -999

struct MathGame
{
  long int    array[MATH_GAME_DIMENSION][MATH_GAME_DIMENSION],
              firstSum;
  int         empty[MATH_GAME_DIMENSION][2],
              iempty;
  
  void init(long int n, short int dificult);
  bool hasWon();
  bool wasEmpty(long int i, long int j);
  void print();
  long int  getRowSum(short int row);
  long int  getColSum(short int col);
};

#endif
