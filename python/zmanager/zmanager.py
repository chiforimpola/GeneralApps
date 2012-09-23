
from zlib import compress, decompress
from sys import argv, stdout

do_compress = False
do_decompress = False

for i in range (1, len(argv)):
  if argv[i][0] == '-':
      if argv[i][1] == 'd':
        do_decompress = True
      elif argv[i][1] == 'c':
        do_compress = True
      break

if do_compress == False and do_decompress == False:
  stdout.write("\nc\t\tCompress\nd\t\tDecompress\n")
else:
  for i in range (1, len(argv)):
    if argv[i][0] != '-':
      if do_compress:
        compressed=compress (open(argv[i]).read())
        open(argv[i],'w').write(compressed)
      elif do_decompress:
          decompressed=decompress(open(argv[i]).read())
          open(argv[i],'w').write(decompressed)

