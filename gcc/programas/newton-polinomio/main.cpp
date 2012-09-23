

#include <stdlib.h>
#include <stdio.h>
#include <iostream>


using namespace :: std;

#include "src/Pontos.h"
#include "src/Newton.h"
#include "src/TrianguloPascal.h"
#include "src/String.cpp"

int main()
{
  long int          n, i, aux;
  TrianguloPascal   tPascal;
  Pontos            p;
  
  cout<<"\nLinhas do triangulo: ";
  cin>>n;
  tPascal.create(n);
  tPascal.Show();
  
  cout<<"Digite o numero de pontos: ";
  cin>>n;
  
  cout<<"\n\t\tEntre com as Coordenadas";
  for(i = 0;i < n;i++)
  {
    p.New();
    cout<<"\nX("<<i<<"): ";
    cin>>aux;
    p.setX(aux);
    
    cout<<"\nY("<<i<<"): ";
    cin>>aux;
    p.setY(aux);
  }
  
  p.ShowAll();
  system("pause");
}
