/*
 * Pequeno cheater de alocacao de memoria que
 * encontrei para C++ utilizando vector
 * 
 *    Basicamente, eu posso utilizar qualquer
 *    classe que eu criar com um atributo vector.
 *    Esse vector irá armazenar em diferentes enderecos
 *    a mesma instancia da propria classe, possuindo ou
 *    nao os mesmos valores, para cada instancia. Dessa forma, nao preciso me
 *    preocupar com malloc, ou new. Tudo que preciso, é de
 *    uma instancia da classe.
 * 
 * Isso é util para mascarar o uso de ponteiros.
 */

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

class A
{
private:
	std::vector<class A *>             pool;
	std::vector<class A *>::iterator   it_pool;
public:
	short int   x;
	A()
	{
		x = 0;
	}

	void addToPool(class A instance)
	{
		class A   *instance2 = new A();

		(*instance2) = instance;

		pool.push_back (instance2);
	}

	A *getNext()
	{
		static std::vector <class A*>::iterator i = pool.begin();

		return (((*i++)));
	}
};


int main ()
{
	A a, *b;

	a.x = 1;
	a.addToPool(a);

	a.x = 2;
	a.addToPool(a);

	while (b = a.getNext())
		std::cout << b->x << std::endl;

}
