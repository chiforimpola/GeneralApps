from sys import argv, stdout
import codecs
import term
import parameters

terminal = term.Color()

def showHelp():
    helpMesage = "\
    -tag           \t\t    tag a ser buscada\n\
    -pattern       \t\t    string que define a posicao de insercao [a cada ocorrencia]\n\
    -p             \t\t    parametro a se adicionado\n\
    -f             \t\t    file absolute path\n\
                 "
    print helpMesage


if parameters.param_exists (argv, 'tag', 0) == 0 or parameters.param_exists (argv, 'pattern', 0) == 0 or parameters.param_exists (argv, 'p', 0) == 0 or parameters.param_exists (argv, 'f', 0) == 0:
    showHelp()
    exit()

itagtosearch = 1
iparametertoadd = 2
icharpattern = 3
istartfileinput = 4

tagtosearch = ''
stringpattern = ''
parametertoadd = ''
inputfile = ''
args = parameters.explode (argv, 1, ('tag', 'pattern', 'p', 'f'))

tagtosearch = args['tag']
stringpattern = args['pattern']
parametertoadd = args['p']
inputfile = args['f']


contents = open(inputfile).read()
i2 = 0
output = ''
modified = False
modified_links = 0
while i2 < len (contents):
    output += contents[i2]
    if contents[i2] == '<' and contents[i2+1] != '/':
        tag = ''
        i3 = i2+1
        while contents[i3] != ' ' and contents[i3] != '>':
            tag += contents[i3]
            i3 += 1
        if tag == tagtosearch:
            for i3 in range (i2+1, len (contents)):
                output += contents[i3]
                if contents[i3] == stringpattern:
                    ok = True
                    cont = 0
                    for i4 in range (i3, len(contents)):
                        if cont < len(stringpattern) and contents[i4] != stringpattern[cont]:
                            ok = False
                            break
                        elif cont == len(stringpattern):
                            break
                        cont += 1
                    if ok == True:
                        output += stringpattern[1:] + parametertoadd
                        modified = True
                        modified_links += 1
                        i2 = len (stringpattern)-1 + i3
                        break
                elif contents[i3] == '>':
                    i2 = i3
                    break
    i2 += 1
if modified:
    outputfile = inputfile + '.modfied'
    terminal.cout ('blue', 'Links modificados: '+str(modified_links))
    terminal.cout ('blue', 'Salvando arquivo modificado: ' + outputfile)
    open(outputfile, 'w').write(output)
else:
    terminal.cout ('error', 'Padrao nao encontrado: ' + stringpattern)
