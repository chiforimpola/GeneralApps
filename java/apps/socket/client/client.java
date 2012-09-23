
import java.io.*;
import java.net.Socket;
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.awt.*;

public class client implements Runnable
{
  private String                 servername = "localHost",
                                 name       = System.getProperty("user.name");
  private int                    porta      = 1010;
  private Scanner                sc         = null;
  private DataInputStream        in         = null;
  private DataOutputStream       out        = null;
  private Socket                 clientsck  = null;
  private Thread                 thread     = null;
  
  /*****************************************
    Envio/Recebimento de Dados do SERVER
  ******************************************/
  
  void sendMessage(String str)
  {
    try
    {
      out.writeUTF (str);
    }catch(IOException e)
     {
       System.out.print(
         "\nErro ao enviar dados ao server!\n" +
         "[ SERVER ] " + servername + "\n"     +
         "[ PORT   ] " + porta + "\n");
     }
  }
  
  
  /**************************************
          Metodos de Configuracao
  **************************************/
  
  Socket Connect(String IP, int porta)
  {
    try
    {
      Socket sck  = new Socket (servername, porta);
      servername  = IP;
      this.porta  = porta;
      return (sck);
    }catch(IOException e)
     {
       return (null);
     }
  }
  
  DataInputStream getInputStream(Socket sck)
  {
    DataInputStream in;
    try
    {
      in = new DataInputStream(sck.getInputStream());
      return (in);
    }catch(IOException e)
     {
       System.out.print(
         "\nErro ao receber stream de entrada!\n" +
         "[ " + sck.toString() + " ]");
       return (null);
     }
  }
  
  DataOutputStream getOutputStream(Socket sck)
  {
    DataOutputStream out;
    try
    {
      out = new DataOutputStream(sck.getOutputStream());
      return (out);
    }catch(IOException e)
     {
       System.out.print(
         "\nErro ao receber stream de saida!\n" +
         "[ " + sck.toString() + " ]");
       return (null);
     }
  }
  
  client(String IP, int porta)
  {
    String        msg;
    
    clientsck = Connect(IP, porta);
    if(clientsck == null)
    {
      System.out.print(
        "\n\tError on trying to connect to server" +
        "\n\tServer may be offline\n");
      System.exit(-1);
    }
    
    in        = getInputStream(clientsck);
    out       = getOutputStream(clientsck);
    sc        = new Scanner (System.in);
    
    sendMessage(name);
    
    thread = new Thread(this);
    thread.start();
    
    while( true )
    {
      msg = sc.nextLine();
      
      if(!msg.equals("")) sendMessage(msg);
    }
    
  }
  
  public static void main(String[] arg)
  {
    String    servername;
    int       port;
    Scanner   read = new Scanner(System.in);
    
    System.out.print("\nServer Name: ");
    servername = read.nextLine();
    System.out.print("\nServer Port: ");
    port = read.nextInt();
    
    client c = new client (servername, port);
  }
  
  /*
    Lera os dados enviados pelo servidor e os colocara na tela
  */
  public void run()
  {
    String     msg;
    
    while( true )
    {
      try
      {
        msg = in.readUTF();
        System.out.print(msg + "\n");
      }catch(IOException e)
       {
         System.out.print("\n\tServer is offline.\n");
         break;
       }
    }
  }
  
}
