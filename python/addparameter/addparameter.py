from sys import argv, stdout, path, exit
import traceback
import codecs
EXTERNAL_MODULES = '/media/PENDRIVE/principal/desenvolvimento/python/resource/modules/'
path.append (EXTERNAL_MODULES)
import parameters

def showHelp():
    helpMesage = "\
    -tag           \t\t    tag a ser buscada\n\
    -pattern       \t\t    string que define a posicao de insercao [a cada ocorrencia]\n\
    -p             \t\t    parametro a se adicionado\n\
    -f             \t\t    file absolute path\n\
    -clip          \t\t    define que o conteudo modificado seja copiado ao clipboard, nao gerando um arquivo de saida.\
                 "
    print (helpMesage)

def print_text (msg, verbose = 0):
    if verbose: print (msg)

try:
    args = parameters.explode (argv, 1, ('tag', 'pattern', 'p', 'f'))
    tagtosearch = args['tag']
    stringpattern = args['pattern']
    parametertoadd = args['p']
    inputfile = args['f']
    verbose = parameters.cmd_exists (argv, 'verbose')

    print args
    exit()

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
      print_text('Links modificados: '+str(modified_links), verbose)
      print_text ('Salvando arquivo modificado: ' + outputfile, verbose)
      open(outputfile, 'w').write(output)
    else:
      print_text ('Padrao nao encontrado: ' + stringpattern, 1)

except:
    showHelp()
