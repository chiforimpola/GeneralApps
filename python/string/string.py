
def toarray (value, pattern):
    result = []
    aux = ''
    for i in value:
        if (i == pattern):
            result.append (aux)
            aux = ''
        else:
            aux += i

    result.append (aux)
    return (result)


