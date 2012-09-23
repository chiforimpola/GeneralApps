from sys import argv, stdout, exit
from urllib import urlencode
import parameters
import os
import pygtk
pygtk.require ('2.0')
import gtk

#Parser de um html procurando por todas os valores href
#dentro de uma tag <a>
#Para cada um, realizar um encode do link
#Apos terminado o parser, sera salvo um arquivo com o mesmo nome
#do arquivo de parametro com a extensao .enc

if len (argv) == 1:
  stdout.write ("<input file>\n")
else:
  outputpath = ''
  argv_values_index = -1
  argv_command = '-'
  verbose = False
  change_clipboard = False
  tempfile = "_temp"
  version      = "\
             linkencoder -     By Leonardo Oliveira\n\
             Language    -     Python\n\
             Version     -     2.3\n\
"

  help_string  = "\
Parser para realizar um encode em todos os links localizados\n\
dentro de tags href\n\
-h, -help                 \tmostra esse menu de ajuda\n\
-version                  \tmostra a versao da aplicacao\n\
-v, -generate-verbose     \tdebug do que esta sendo feito\n\
-no-output                \tnao salva o arquivo de saida, mas coloca seu conteudo no clipboard\n\
"

  if parameters.param_exists (argv, 'generate-verbose') or parameters.param_exists (argv, 'v'):
      verbose = True
  if parameters.param_exists (argv, 'h') or parameters.param_exists (argv, 'help'):
      stdout.write (help_string+"\n")
      exit ()
  if parameters.param_exists (argv, 'version'):
      stdout.write (version+"\n")
      exit ()
  if parameters.param_exists (argv, 'no-output'):
      change_clipboard = True
  elif parameters.param_exists (argv, 'output'):
      argv_values = parameters.explode (argv)
      outputpath = argv_values['parameter'][0]

  argv_values = parameters.explode (argv)
  for i in range (0, len (argv_values['parameter'])):
    if len(argv_values['parameter']) == 0: break
    file_path = argv_values['parameter'][i]

    if outputpath == '' and not change_clipboard: outputpath = file_path+'.enc'

    contents = open(file_path, 'r').read()
    contentsindex = 0
    buff = '' #buffer utilizado para armazenar as informacoes originais do html e suas mudancas
    encoded_links = 0

    if verbose:  stdout.write ('Parser file: '+argv[i]+"\n")

    while contentsindex < len (contents):
        if contents[contentsindex] == '<' and contents[contentsindex+1] == 'a':
            buff += '<a'
            contentsindex += 2
            data = ''
            tagencodedvalue = ''

            while contents[contentsindex] != '>':
                buff += contents[contentsindex]
                if contents[contentsindex+1:contentsindex+5] == 'href': #caso os 4 proximos caracteres sejam HREF
                    buff += 'href='
                    quotes = 0
                    equals = 0
                    tagvalue = ''
                    contentsindex += 5
                    i = contentsindex

                    while quotes < 2:
                        if contents[i] == '"' or contents[i] == "'": quotes += 1
                        elif contents[i] == '=' and equals == 0: equals = 1
                        elif equals == 1 and quotes == 1:
                            tagvalue += contents[i]
                        i += 1

                    #realizar a verificacao se o link esta em http ou https (se nenhum, ignoro)
                    if tagvalue[:4] == 'http':
                        if tagvalue[:5] != 'https':
                            slashindex = 7 # http : / /
                            protocol = 'http://'
                        else:
                            slashindex = 8 #https : / /
                            protocol = 'https://'
                    else:
                        slashindex = 0
                        protocol = ''

                    data = { 'url':tagvalue[slashindex:] }
                    tagencodedvalue = '"'+protocol+urlencode(data)[4:]+'"' #para remover o parametro: url=
                    buff += tagencodedvalue
                    contentsindex += len(tagvalue)+1
                    encoded_links += 1
                    break
                contentsindex += 1

        else:
            buff += contents[contentsindex]
        contentsindex += 1

    if encoded_links > 0:
        if not change_clipboard:
            if verbose:
                stdout.write ('Salvando arquivo: '+outputpath+"\n")
                stdout.write ('Total de links alterados: '+str(encoded_links)+"\n")
            outputhandle = open(outputpath, 'w')
            outputhandle.write(buff)
            outputhandle.close()
        #
        # Altero o clipboard de acordo com o conteudo do arquivo de saida
        #
        else:
            if verbose:
                stdout.write ("Alterando o conteudo do clipboard...\t\n"),
            tempfilehandle = open (tempfile, 'w')
            tempfilehandle.write (buff)
            tempfilehandle.close()
            clipboard = gtk.clipboard_get ()
            clipboard.set_text (open(tempfile).read())
            clipboard.store()
            os.system ('rm -f '+tempfile)
            if verbose: stdout.write ("\tOK\n")
    else:
        stdout.write ("Nenhum link encodado!\n")

  

