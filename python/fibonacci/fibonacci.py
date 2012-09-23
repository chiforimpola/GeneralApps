
def getTerms (termos):
  n, n2, result = 0, 1, []

  for i in range (0, termos):
    result.append (n)
    n, n2 = n2, (n2 + n)

  return (result)

def fibB (termos):
  n, n2, cont = 0, 1, 0

  while cont < termos:
    print n,
    n, n2, cont = n2, n2 + n, cont + 1


def recursive(reverse, terms, n = 0, n2 = 1, cont = 0):
    if not reverse: print n
    if cont < terms: recursive (reverse, terms, n2, n2+n, cont+1)
    if reverse: print n

