


import java.io.*;
import java.awt.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.InetAddress;
import java.util.List;
import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;



public class server implements Runnable
{
  private int                 porta               =  8080,
                              contclients         =  0;
  private String              SERVER_WELCOME_MESSAGE = 
                                "******************************\n" +
                                "*                            *\n" +
                                "*          BEM-VINDO         *\n" +
                                "*                            *\n" +
                                "******************************\n";
  private ServerSocket        serversck           =  null;
  private Socket              clientsck           =  null;
  private TreatClient         tClient             =  null;
  List<Socket>                clientlist          =  new ArrayList();
  List<TreatClient>           tClientlist         =  new ArrayList();
  Thread                      thread              =  null,
  /* Executara o metodo run() do proprio server e nele aceitara a conexao dos clients */
                              serverthread        =  null;
  
  /**************************************
          Metodos de Configuracao
  **************************************/
  
  
  int  getPort(){ return (porta); }
  void setPort(int porta){ this.porta = porta; }
  
  void showCommands()
  {
    System.out.print(
    "\n1\t\t-\t\tListar todos conectados");
  }
  
  /*****************************************************************************
    Envia uma mensagem BroadCast onde apenas aquele client de parametro
      nao ira receber a mensagem
  ******************************************************************************/
  void BROADCAST(TreatClient t, String msg)
  {
    for(int i2 = 0;i2 < tClientlist.size();i2++)
      if( !tClientlist.get(i2).getInetAddress().equals(t.getInetAddress()) )
        tClientlist.get(i2).sendMessage(msg);
  }
  
  
  Socket  acceptClient()
  {
    try
    {
      Socket sck = new Socket();
      sck        = serversck.accept();
      return (sck);
    }catch(IOException io)
    {
      System.out.print("\nErro ao criar/receber conexao do cliente");
      return (null);
    }
  }
  
  ServerSocket getNewServerSocket(int porta)
  {
    try
    {
      ServerSocket sck = new ServerSocket(porta);
      return (sck);
    }catch(IOException e)
    {
      System.out.print("Erro ao criar servidor na porta " + porta);
      return (null);
    }
  }
  
  server(int porta)
  {
    int        aux = -1;
    
    this.porta = porta;
    serversck = getNewServerSocket(porta);
    
    System.out.print(
      "\n[ Server ]" +
      "\n>> Porta: " + this.porta + "\n");
    
    serverthread = new Thread (this);
    serverthread.start();
    
    while( true )
    {
      /******************************************************
          -> Se estiver desconectado, removo este cliente
          -> Se estiver 'setado' para enviar mensagem a todos
               os clientes, entao envio a mensagem e reseto
               a variavel
      ******************************************************/
      for(int i = 0;i < tClientlist.size();i++)
      {
        if(!tClientlist.get(i).isConnected())
        {
          System.out.print("\n\t[ " + tClientlist.get(i).getName() + " ] offline\n");
          tClientlist.remove(i);
          contclients--;
        }
        
      }
      
    }
  }
  
  public static void main(String[] arg)
  {
    new server(100);
  }
  
  /****************************************
    Metodo utilizado pela Thread. 
    Aceitara as conexoes dos clients
  ****************************************/
  
  public void run()
  {
    int       i;
    boolean   permissao = true;
    
    while( true )
    {
      permissao = true;
      
      clientsck = acceptClient();
      
      /*
        Verifico em minha lista se alguem com o mesmo INETADDRESS existe, 
        se sim, entao nao permito que se conecte
      */
      for(i = 0;i < tClientlist.size();i++)
      {
        if( clientsck.getInetAddress().equals(tClientlist.get(i).getInetAddress()) )
        {
          permissao = false;
          tClient = tClientlist.get(i);
          tClient.sendMessage("\n[ Already online ]");
          System.out.print(
            "\n[ " + tClientlist.get(i).getName() + " ] is already online!\n");
          break;
        }
      }
      
      if(permissao)
      {
        contclients++;
        tClient   = new TreatClient (clientsck);
        thread    = new Thread (tClient);
      
        tClientlist . add (tClient);
        
        tClient.sendMessage(SERVER_WELCOME_MESSAGE);
        
        thread.start();
        
        while(tClient.getName() == null){ }
        
        System.out.print("\n[ " + tClient.getName() + " ] is online\n");
        
        BROADCAST(tClient, "\n[ " + tClient.getName() + " ] is online\n");
      }
      
    }
  }
  
}

