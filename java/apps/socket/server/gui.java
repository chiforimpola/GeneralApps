
import java.io.*;
import java.lang.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.List;
import java.util.ArrayList;



/*
  Inserir dados em uma lista:
          list.insertElementAt(string, index)
          listModel.addElement("teste");
*/

public class gui extends JFrame implements KeyListener, ActionListener, MouseListener, ListSelectionListener, Runnable
{
  private int              SCREEN_W, 
                           SCREEN_H,
                           MENU_X_INI, MENU_Y_INI,
                           MENU_W, MENU_H,
                           LOG_X, LOG_Y,
                           LOG_W, LOG_H,
                           LIST_CLIENTS_X, LIST_CLIENTS_Y,
                           LIST_CLIENTS_W, LIST_CLIENTS_H;
  private String           SERVER_WELCOME_MESSAGE =
                             "********************************\n" +
                             "*              Welcome         *\n" +
                             "********************************\n";
  private Container        window;
  private JFrame           frame;
  private JList            listClients;
  private DefaultListModel listModel;
  private JTextArea        log;
  private JScrollPane      scrollLog;
  private JMenuBar         menu;
  private JMenu            menuAction;
  private JMenuItem        itemClose,
                           itemConnect,
                           itemHelp;
  private JLabel           lblClients;
  
  /* Server Configurations */
  int                      port;
  ServerSocket             server;
  Thread                   thread,
                           threadB;
  List<treatclient>        clientList =  new ArrayList();
  List<String>             nameList   =  new ArrayList();
  
  /***************************************
  *                                      *
  *    Server Configurations Methods     *
  *                                      *  
  ***************************************/
  ServerSocket createServer(int port)
  {
    try
    {
      ServerSocket sck = new ServerSocket(port);
      log.setText("\n[ Server openned on port " + Integer.toString(port) + " ]\n");
      lblClients.setVisible(true);
      listClients.setVisible(true);
      thread = new Thread(this);
      thread.start();
      return (sck);
    }catch(IOException e)
    {
      log.setText("\nError while trying to create the server socket.");
      return (null);
    }
  }
  
  void addLists()
  {
    LIST_CLIENTS_X = SCREEN_W - 300;
    LIST_CLIENTS_Y = MENU_Y_INI + 100;
    LIST_CLIENTS_W = 250;
    LIST_CLIENTS_H = 50;
    
    listModel = new DefaultListModel();
    
    listClients = new JList(listModel);
    listClients.setBounds(LIST_CLIENTS_X, LIST_CLIENTS_Y, LIST_CLIENTS_W, LIST_CLIENTS_H);
    listClients.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
    listClients.setSelectedIndex(0);
    listClients.addListSelectionListener(this);
    listClients.setVisibleRowCount(5);
    
    JScrollPane listClientsScrollPane = new JScrollPane(listClients);
    listClientsScrollPane.setBounds(LIST_CLIENTS_X, LIST_CLIENTS_Y, LIST_CLIENTS_W, LIST_CLIENTS_H);

    window.add(listClientsScrollPane);
    /* Crio a Label */
    lblClients = new JLabel("Connected Clients");
    lblClients.setBounds(LIST_CLIENTS_X, LIST_CLIENTS_Y - 50, LIST_CLIENTS_W, LIST_CLIENTS_H);
    
    lblClients.setVisible(false);
    listClients.setVisible(false);
    
    window.add(lblClients);
  }
  
  void addTextArea()
  {
    LOG_X = 0;
    LOG_Y = (MENU_H*2);
    LOG_W = (SCREEN_W/2);
    LOG_H = SCREEN_H - ( (SCREEN_H*4)/10);
    
    log   = new JTextArea();
    log.setEditable(false);
    
    scrollLog = new JScrollPane(log);
    scrollLog.setBounds(LOG_X, LOG_Y, LOG_W, LOG_H);
    window.add(scrollLog);
  }
  
  void addMenu()
  {
    itemConnect  = new JMenuItem("Connect");
    itemConnect  . setMnemonic(KeyEvent.VK_C);
    itemConnect  . setToolTipText("Connect server");
    itemConnect  . addActionListener(new ActionListener()
      {
        public void actionPerformed(ActionEvent ae)
        {
          String   str;/* will get the port */
          str = JOptionPane.showInputDialog("Port: ");
          server = createServer(Integer.parseInt(str));
        }
      });
    
    itemHelp  = new JMenuItem("Help");
    itemHelp  . setMnemonic(KeyEvent.VK_H);
    itemHelp  . setToolTipText("About...");
    itemHelp  . addActionListener(new ActionListener()
      {
        public void actionPerformed(ActionEvent ae)
        {
          JOptionPane.showMessageDialog(
          window,"This is the Help menu");
        }
      });
    
    itemClose  = new JMenuItem("Close");
    itemClose  . setMnemonic(KeyEvent.VK_C);
    itemClose  . setToolTipText("Terminate Server");
    itemClose  . addActionListener(new ActionListener()
      {
        public void actionPerformed(ActionEvent ae)
        {
          System.exit(0);
        }
      });
    
    menuAction  = new JMenu("Action");
    menuAction  . setMnemonic(KeyEvent.VK_A);
    menuAction  . add(itemConnect);
    menuAction  . add(itemHelp);
    menuAction  . add(itemClose);
    
    menu = new JMenuBar();
    
    MENU_X_INI = 0;
    MENU_X_INI = 0;
    MENU_W     = SCREEN_W;
    MENU_H     = 30;
    
    menu.add(menuAction);
    menu.setBounds(0, 0, SCREEN_W, 30);
    
    frame.setJMenuBar(menu);
  }
  
  /* Additional Methods */
  void addClientToLists(String name)
  {
    nameList.add(name);
    listModel.addElement(name);
  }
  
  /*
    Search fo all clients connected to the server
    and see if they have any message on their buffer.
    If so, analyse what will happen with this message
  */
  void getClientMessages()
  {
    int   i;
    while( true )
    {
      try
      {
        Thread.sleep(30);
      }catch(Exception e) { }
      for(i = 0;i < clientList.size();i++)
      {
        if(!clientList.get(i).isConnected())
        {
          log.append("\n[ " + clientList.get(i).getClientName() + " ] is OFFLINE");
          for(int i2 = 0;i2 < clientList.size();i2++)
          {
            if(!clientList.get(i2).isConnected())
              clientList.get(i2).sendMessage(
                "[ " + clientList.get(i).getClientName() + " ]" +
                " is OFFLINE");
            else
            {
              clientList.remove(i2);
              listClients.remove(i2);
            }
          }
        }
        
        else if(clientList.get(i).haveMessage())
        {
          for(int i2 = 0;i2 < clientList.size();i2++)
            clientList.get(i2).sendMessage(
              "[ "      + clientList.get(i).getClientName() + " ]" +
              " Says: " + clientList.get(i).getMessageToSend());
          log.append("\n[ " + 
                clientList.get(i).getClientName() + " ] Says: " +
                clientList.get(i).getMessageToSend());
          clientList.get(i).resetMessageToSend();
          break;
        }
      }
          
    }
  }
  
  gui (String title, int w, int h)
  {
    String[]    _conf = new String[10];
    String      val;
    
    WindowManager.Motif();
    
    frame  = new JFrame(title);
    window = frame.getContentPane();
    
    Icon.setIcon(frame, "/resource/server.jpg");
    
    SCREEN_W = w;
    SCREEN_H = h;
    
    addMenu();
    addTextArea();
    addLists();

    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setLayout(new BorderLayout());
    frame.addKeyListener(this);
    frame.setLocation(0 ,0);
    frame.setSize(w, h);
    frame.setResizable(false);
    frame.setVisible(true);
  }
  
  public static void main(String[] arg)
  {
    gui g = new gui("Server", 640, 480);
    g.getClientMessages();
  }
  
  /* Escuta de acoes */
  public void actionPerformed(ActionEvent ae){ }
  
  
  /* Key Listeners */
  public void keyTyped(KeyEvent e){}
  
  public void keyPressed(KeyEvent e)
  {
    if(e.getKeyCode() == KeyEvent.VK_ESCAPE) System.exit(0);
  }
  
  public void keyReleased(KeyEvent e){}
  
  /******Eventos de Mouse********/
  public void mouseClicked  (MouseEvent me){}
  public void mousePressed  (MouseEvent me){}
  public void mouseReleased (MouseEvent me){} 
  public void mouseEntered  (MouseEvent me){}
  public void mouseExited   (MouseEvent me){}
  
  /* List Event */
  public void valueChanged(ListSelectionEvent e)
  {
    if (e.getValueIsAdjusting() == false)
    {
    }
  }

  /***************************************
  *                                      *
  *           Thread Method              *
  *                                      *  
  ***************************************/
  public void run()
  {
    Socket        sck = new Socket();
    treatclient   tClient;
    
    while( true )
    {
      try
      {
        sck = server.accept();
        
        tClient = new treatclient(sck, log);
        clientList.add(tClient);
        
        threadB = new Thread(tClient);
        threadB.start();
        
        while(tClient.getClientName() == null){ }/*Wait until receives client name*/
        
        addClientToLists(tClient.getClientName());
        
        tClient.sendMessage(SERVER_WELCOME_MESSAGE);
        
        for(int i = 0;i < clientList.size()-1;i++)
        {
          if(clientList.get(i).isConnected())
            clientList.get(i).sendMessage(
              "[ " + clientList.get(i).getClientName() + " ] is ONLINE");
        }
        
      } catch(IOException io)
        {
          log.append("\nErro ao criar/receber conexao do cliente");
        }
    }
  }
  
};

