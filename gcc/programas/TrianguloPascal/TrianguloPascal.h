
#ifndef TRIANGULO_PASCAL_H
#define TRIANGULO_PASCAL_H


/*******************************************
  Contera cada um dos numeros do triangulo,
    bem como sua linha/coluna
********************************************/
struct _TrianguloPascal
{
  long int           n,
                     i, j;
  _TrianguloPascal  *prox, *ante;
  
  long int getN(long int i, long int j);
  void     setN(long int i, long int j, long int n);
  void New(long int i, long int j);
};


struct TrianguloPascal
{
  long int             MAX;
  
  char *getRow(long int n);
  void  create(long int n);
  void  Show();
};

#endif
