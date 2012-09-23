from os import listdir, path, getcwd
from platform import system, release

DIRECTORY_SEPARATOR = '/'
ACTUAL_DIR = '.'
ABOVE_DIR = '..'

if system() == 'Linux':
    ACTUAL_DIR = '.'
    ABOVE_DIR = '..'

def upperdir (abspath):
    '''
        funcao que retorna o caminho absoluto de um diretorio acima daquele
        passado como parametro
    '''
    abspath = normalizepath (abspath)
    if abspath == '':
        return (DIRECTORY_SEPARATOR)

    i = len (abspath)-1
    if abspath[i] == DIRECTORY_SEPARATOR:
        abspath = abspath[:i]
        i -= 1

    while i > 0 and abspath[i] != DIRECTORY_SEPARATOR: i -= 1
    if i > 0:
        return (abspath[:i+1])
    return (DIRECTORY_SEPARATOR)

def read(path = "."):
    '''
       retorna os elementos internos ao diretorio (apenas seus nomes, ou seja,
       seus respectivos caminhos absolutos nao sao retornados)
    '''
    result = []
    try:
        result = listdir (path)
        return (result)
    except:
        return (None)

def isdir(abspath):
    '''
       return:
           True: caso caminho passado como parametro represente um diretorio
           False: caso o caminho passado como parametro nao represente um diretorio ou nao exista
    '''
    return (path.isdir(abspath))

def normalizepath(abspath):
    '''
       retorna o caminho absoluto baseado no caminho passado como parametro
       e capaz de resolver os caminhos em ambientes unix, tais como: '.', '..', '/'
    '''
    buf = ''
    dirtree = []
    if isdir (abspath) and abspath[len(abspath)-1] !=DIRECTORY_SEPARATOR: abspath += DIRECTORY_SEPARATOR
    for i in range (0, len(abspath)):
        if abspath[i] != DIRECTORY_SEPARATOR: buf += abspath[i]
        if i+1 == len (abspath) or abspath[i] == DIRECTORY_SEPARATOR:
            if buf == '':
                dirtree.append (DIRECTORY_SEPARATOR)
            else:
                dirtree.append (buf)
            buf = ''

    aux = []
    abspath = ''
    for i in range (0, len(dirtree)):
        if dirtree[i] == ACTUAL_DIR and i == 0:
            abspath = getcwd() + DIRECTORY_SEPARATOR
        elif dirtree[i] == ABOVE_DIR and i == 0:
            abspath = upperdir (getcwd())
        else:
            if dirtree[i] == ABOVE_DIR:
                abspath = upperdir(abspath)
            elif dirtree[i] != ACTUAL_DIR:
                if dirtree[i] != DIRECTORY_SEPARATOR:
                    abspath += dirtree[i]
                    if isdir (abspath): abspath += DIRECTORY_SEPARATOR
                else:
                    abspath += dirtree[i]

    aux = ''
    got = 0
    for i in range (0, len(abspath)):
        if abspath[i] == DIRECTORY_SEPARATOR:
            if i == 0:
                aux += abspath[i]
            elif got == 1:
                got = 0
                aux += abspath[i]
        else:
            aux += abspath[i]
            got = 1
    abspath = aux
    return (abspath)

def parsedir(abspath, maxdepth = 1):
    '''
       retorna uma lista contendo todos os elementos do diretorio passado
       como parametro e de seus subdiretorios. O numero maximo de subdiretorios
       a ser lido e definido no parametro 'maxdepth'
    '''
    abspath = normalizepath (abspath)
    result = read(abspath)

    if result == None:
        return (None)

    if maxdepth > 0:
        aux = []
        #atualizo o caminho dos elementos para o caminho absoluto
        for i in range (0, len (result)):
            aux.append (normalizepath (abspath+DIRECTORY_SEPARATOR+result[i]))
        result = aux
        for i in range (0, len (result)): 
            if isdir (result[i]):
                child = parsedir (result[i], maxdepth-1)
                cpresult = []
                if child != None:
                    for i2 in range (0, len (result)):
                        cpresult.append (result[i2])
                        if i2 == i:
                           for i3 in child: cpresult.append (i3)
                    result = cpresult
                #else:
                #    print 'Erro ao ler: ' + result[i]
        return (result)
    return (None)

