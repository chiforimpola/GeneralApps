
from zlib import compress, decompress
from sys import argv, path, exit
from os import popen
import term

termHandler = term.Color()

if len (argv) < 2:
    termHandler.cout('error', 'Parametros insuficientes!')
    termHandler.cout('warning', 'compress\tnome do arquivo\ndecompress\tnome do arquivo')
    termHandler.cout('warning', 'compress\t*string*\ndecompress\t*string*') 
    exit()

command=argv[1]

for i in range (2, len (argv)):
    if argv[i][0] == '*':
        aux = ''
        for i2 in range (1, len(argv[i])):
            if argv[i][i2] == '*': break;
            aux += argv[i][i2]
        if command == 'compress':
            termHandler.cout ('warning', compress(aux))
        elif command == 'decompress':
            termHandler.cout ('warning', decompress (aux))
        else:
            termHandler.cout ('error', 'comando desconhecido: ' + command)
    else:
        if command == 'compress':
            open(argv[i]+'.compressed', 'w').write (compress(open(argv[i]).read()))
            output = argv[i] + '.comp'
        elif command == 'decompress':
            open(argv[i], 'w').write(decompress(open(argv[i]).read()))
            output = argv[i]+'.decompressed'
        else:
            termHandler.cout ('error', 'commando desconhecido: ' + command)
        termHandler.cout ('warning', popen('du -h ' + output).read())

