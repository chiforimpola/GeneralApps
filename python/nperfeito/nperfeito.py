

import os
import sys
from term import Color

term = Color()
debug = False

if len (sys.argv) > 1:
    if sys.argv[1] == 'debug':
		debug = True


def getDivisores(n):
    divisores = []
    for i in range(n):
        if  i > 0 and (n % i) == 0:
            divisores.append(i)

    return (divisores)

def isPerfect (n):
    divisores = getDivisores (n)
    sigma = 0
    
    if debug:
		term.cout ('white', 'Divisors: ')
		for i in divisores:
			term.cout ('warning', str (i))
    
    if len (divisores) > 0:
        for i in divisores:
            sigma += i

    if sigma == n:
        return (True)

    return (False)


n = int (raw_input ("Entre com o numero>> "))
while n != -1:

    if (isPerfect (n)):
        term.cout ('warning', str (n) + ' [perfect]')
    else:
        term.cout ('error', str (n) + ' [imperfect]')

    n = int (raw_input ("Entre com o numero>> "))
