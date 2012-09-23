

from urllib2 import urlopen
from sys import argv, stdout, exit
from os import popen
from str import toArray


if len (argv) < 2:
    print ('\nAdicione as urls para efetuar o download\n')
else:
    for i in range (1, len(argv)):
        try:
            urlcontents=urlopen(argv[i]).read()
            downloaded_file = str(i) + ".down"
            open(downloaded_file, 'w').write(urlcontents)
            print ("\nSalvando arquivo: " + downloaded_file + "\t[" + toArray(popen('du -h ' + downloaded_file).read(), '\n')[0] + "]")
            print ('default', '\n\tFinalizando aplicacao')
        except:
            print ('\nErro ao realizar request!')
