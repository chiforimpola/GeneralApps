



import java.io.*;
import java.net.Socket;
import java.net.InetAddress;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import javax.swing.*;


/*
*/


public class treatclient extends JFrame implements Runnable
{
  private String              name        =  null,
                              msgToSend   =  null;
  private Socket              clientsck   =  null;
  private DataInputStream     in          =  null;
  private DataOutputStream    out         =  null;
  private boolean             CONNECTED   =  true;
  private JTextArea           placeToPutMessages = null;
  
  String       getClientName(){ return (name); }
  InetAddress  getInetAddress(){ return (clientsck.getInetAddress()); }
  
  String       getMessageToSend(){ return (msgToSend); }
  void         resetMessageToSend(){ msgToSend = null; }
  
  boolean      isConnected(){ return (CONNECTED); }
  boolean      haveMessage(){ if(msgToSend == null) return (false); else return (true); }
  
  boolean sendMessage(String str)
  {
    try
    {
      out.writeUTF(str);
      return (true);
    }catch(IOException e)
     {
       CONNECTED = false;
       Thread.currentThread().stop();
       return (false);
     }
  }
  
  /**************************************
          Metodos de Configuracao
  **************************************/
  DataInputStream getInputStream(Socket sck)
  {
    try
    {
      DataInputStream in = new DataInputStream(sck.getInputStream());
      return (in);
    }catch(IOException e)
     {
       e.printStackTrace();
       return (null);
     }
  }
  
  DataOutputStream getOutputStream(Socket sck)
  {
    try
    {
      DataOutputStream out = new DataOutputStream(sck.getOutputStream());
      return (out);
    }catch(IOException e)
     {
       e.printStackTrace();
       return (null);
     }
  }
  
  treatclient(Socket sck)
  {
    clientsck  = sck;
    this.name  = name;
    in         = getInputStream(clientsck);
    out        = getOutputStream(clientsck);
  }
  
  treatclient(Socket sck, JTextArea txta)
  {
    clientsck  = sck;
    this.name  = name;
    in         = getInputStream(clientsck);
    out        = getOutputStream(clientsck);
    placeToPutMessages = txta;
  }
  
  /*************************************************
       Metodo que sera utilizado pelas Threads
  *************************************************/
  public void run()
  {
    String     str, aux;
    
    /***********************************************************
        Primeira mensagem do cliente serao suas configurcoes
    ***********************************************************/
    try
    {
      name = in.readUTF();
      //if(placeToPutMessages != null)
        //placeToPutMessages.append("\nTREATCLIENT: " + name + "\n");
    }catch(IOException e)
     {
       e.printStackTrace();
       Thread.currentThread().stop();
     }
    
    while( true )
    {
      try
      {
        msgToSend = in.readUTF();
      }catch(Exception e)
       {
         CONNECTED = false;
         Thread.currentThread().stop();
         break;
       }
    }
  }
  
}

