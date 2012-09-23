
from urllib2 import urlopen
from sys import argv
import os
import term

terminal = term.Color()

def parse(url, tagtosearch, atrtosearch, chartoremove = ''):
    contents = urlopen(url).read()
    i = 0
    while i < len (contents):
        if contents[i] == "<":
            i += 1
            tag = ''
            while contents[i] != '>' and contents[i] != ' ':
                tag += contents[i]
                i += 1
            if tag == tagtosearch:
                atr = ''
                while contents[i] != '>':
                    if contents[i] == '=':
                        if atr == atrtosearch: break
                        else:
                            atr = ''
                            while contents[i] != '>' and contents[i] != ' ': i += 1
                    if contents[i] != ' ': atr += contents[i]
                    i += 1
                if atr == atrtosearch:
                    i += 1
                    value = ''
                    while contents[i] != '>' and contents[i] != ' ':
                        value += contents[i]
                        i += 1
                    if chartoremove != '':
                        aux = ''
                        for o in value:
                            if o != chartoremove: aux += o
                        value = aux
                    if value == url: break
                    if not os.path.isdir (tagtosearch):
                        os.system ('mkdir ' + tagtosearch)
                    if not os.path.isdir (tagtosearch+'/'+atrtosearch):
                        os.system('mkdir '+tagtosearch+'/'+atrtosearch)
                    if value[len(value)-1] == '/':
                        aux = value[:-1]
                        value = aux

                    o = len (value)-1
                    while o > 0:
                        if value[o] == '/':
                            o += 1
                            break
                        o -= 1
                    filename = ''
                    while o < len (value):
                        filename += value[o]
                        o += 1

                    terminal.cout ('warning', tagtosearch+'/'+atrtosearch+'/'+filename)
                    open(tagtosearch+'/'+atrtosearch+'/'+filename, 'w').write (urlopen(value).read())
                    terminal.cout ('blue', '['+tagtosearch+', '+atrtosearch+']'+value)

                    # Verificar como realizar o processo de maneira recursiva
                    #
                    # parse (value, tagtosearch, atrtosearch, chartoremove)
                    #
        i += 1

if len (argv) == 5:
    parse (argv[1], argv[2], argv[3], argv[4])
else:
    terminal.cout('warning', 'Parametros insuficientes')
    for  i in range (1, len(argv)): terminal.cout ('warning', i)




