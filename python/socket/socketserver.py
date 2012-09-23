
from os import popen
from socket import *
from sys import argv
from threading import *
from term import Color
from str import toArray

terminal = Color()
clients = []

def broadcast (message):
  global clients
  for i in clients:
    i[0].send (message)


def listernerController (clientsocket):
  buff = True
  BUFFER_SIZE = 1024
  client_info = clientsocket[0].recv (BUFFER_SIZE)
  while buff != None:
    buff = clientsocket[0].recv (BUFFER_SIZE)
    value = toArray (buff, ':')
    if value[0] == 'message':
        print (client_info + " says: " + value[1])
        broadcast ('Client '+client_info+' says: '+value[1])
    elif value[0] == 'command':
        if value[1] != 'exit':
            print ('Executing '+ value[1]+" for client: "+client_info)
            broadcast (popen (value[1]).read())
        else: break

  clientsocket[0].close()

def cliThread():
    print ('Entrando em CLI...')
    command = ''
    while command != 'exit':
        command = raw_input('>>> ')
        if command == 'clients':
            for i in clients: print (i)
        else: print (command+" nao reconhecido...")

def server(server, port, debug = False):
  BUFFER_SIZE = 1024
  maxconnections = 10
  print ('Criando socket do servidor...')
  sck = socket (AF_INET, SOCK_STREAM)
  sck.bind ( (server, port) )
  sck.listen (maxconnections)
  Thread (target=cliThread, args=()).start()
  print ('Estado: aguardando conexoes...')
  while True:
    auxSck = sck.accept ()
    clients.append (auxSck)
    a=Thread (target = listernerController, args=(auxSck,),)
    a.start()
  print ('Servidor encerrado.')

terminal.cout ('warning', "<server ip><port to listen>")

if len (argv) >= 2: server ( argv[1], int(argv[2]), True )

