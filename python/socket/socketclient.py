

from socket import *
from sys import argv
from threading import *
from term import Color
from str import toArray

terminal = Color()

def listernerController (serversocket):
  buff = True
  BUFFER_SIZE = 1024
  while buff != 'shutdown':
    buff = serversocket.recv (BUFFER_SIZE)
    print (buff)

def client (server, port, debug = False):
  if debug:  print ('Criando socket de cliente...')
  sck = socket (AF_INET, SOCK_STREAM)
  if debug:
      print ("\t\tOK")
      print ('Connectando cliente ao servidor ('+server+', '+str(port)+')' )
  sck.connect ( (server, port) )
  sck.send (sck.getsockname()[0])
  Thread (target=listernerController, args=(sck,)).start ()
  buff = True
  mode = 'message'
  while buff != 'exit':
      buff = raw_input (mode+":")
      aux = toArray (buff, ':')
      if aux[0] == '/switch':
          mode = aux[1]
      elif mode == 'message':
          sck.send (mode+':'+buff)
      elif mode == 'command':
          sck.send (mode+':'+buff)

  if debug: print ('Encerrando cliente...')

if len (argv) < 2:
    terminal.cout ('warning', '<ip do servidor><porta de comunicacao>')

else: client (argv[1],  int(argv[2]), True )
