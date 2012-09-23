

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
                           SCREEN_H;
  private Container        window;
  private JFrame           frame;
  private JTextField       msgToSend;
  private JTextArea        log;
  private JScrollPane      scrollLog;
  private JMenuBar         menu;
  private JMenu            menuAction,
                           menuLayout;
  private JMenuItem        itemClose,
                           itemConnect,
                           itemServerName,
                           itemServerPort,
                           /* UIManagers */
                           itemLocalSystem,
                           itemNimbus,
                           itemMotif,
                           itemCustomLookAndFeel,
                           itemCrossPlataform;
                           
  private JLabel           lblClients;
  /*SERVER INFO.*/
  String                   servername,
                           serverport;
  
  /* Client Configurations */
  private int                    port;
  private String                 name            = System.getProperty("user.name");
  private boolean                CONNECTED       = false;
  
  private DataInputStream        in              = null;
  private DataOutputStream       out             = null;
  private Socket                 client;
  private Thread                 thread;
  private List<String>           clientNameList  =  new ArrayList();
  
  void addTextArea(JFrame frame)
  {
    msgToSend = new JTextField(20);
    msgToSend.setVisible(false);
    msgToSend.addKeyListener(this);
    
    log   = new JTextArea(10, 25);
    log.setEditable(false);
    
    scrollLog = new JScrollPane(log);
    scrollLog.setVisible(false);
    
    frame.add(msgToSend);
    frame.add(scrollLog);
  }
  
  void addMenu(JFrame frame)
  {
    itemConnect  = new JMenuItem("Connect");
    itemConnect  . setMnemonic(KeyEvent.VK_C);
    itemConnect  . setToolTipText("Connect server");
    itemConnect  . setEnabled(false);
    itemConnect  . addActionListener(new ActionListener()
      {
        public void actionPerformed(ActionEvent ae)
        {
          client = Connect();
          if(client != null)
          {
            CONNECTED = true;
            in  = getInputStream(client);
            out = getOutputStream(client);
            sendMessage(name);
            msgToSend.setVisible(true);
            scrollLog.setVisible(true);
            itemConnect.setEnabled(false);
          }
          else
            log.append("Server " + servername + " is Offline");
        }
      });
    
    itemServerName  = new JMenuItem("Server Name");
    itemServerName  . setMnemonic(KeyEvent.VK_N);
    itemServerName  . setToolTipText("Input Server Name or IP");
    itemServerName  . addActionListener(new ActionListener()
      {
        public void actionPerformed(ActionEvent ae)
        {
          servername = JOptionPane.showInputDialog("Name: ");
          if(!servername.equals("") && !serverport.equals(""))
            itemConnect.setEnabled(true);
        }
      });
    
    itemServerPort  = new JMenuItem("Server Port");
    itemServerPort  . setMnemonic(KeyEvent.VK_P);
    itemServerPort  . setToolTipText("Input Server Port");
    itemServerPort  . addActionListener(new ActionListener()
      {
        public void actionPerformed(ActionEvent ae)
        {
          serverport = JOptionPane.showInputDialog("Port: ");
          if(!servername.equals("") && !serverport.equals(""))
            itemConnect.setEnabled(true);
        }
      });
    
    itemClose  = new JMenuItem("Close");
    itemClose  . setMnemonic(KeyEvent.VK_C);
    itemClose  . setToolTipText("Terminate Aplication");
    itemClose  . addActionListener(new ActionListener()
      {
        public void actionPerformed(ActionEvent ae)
        {
          System.exit(0);
        }
      });
    
    itemLocalSystem  = new JMenuItem("Local System");
    itemLocalSystem  . setMnemonic(KeyEvent.VK_L);
    itemLocalSystem  . setToolTipText("Layout of Local System");
    itemLocalSystem  . addActionListener(new ActionListener()
      {
        public void actionPerformed(ActionEvent ae)
        {
          WindowManager.LocalPlataform();
          UpdateWindowLayout();
        }
      });
      
    itemNimbus  = new JMenuItem("Nimbus");
    itemNimbus  . setMnemonic(KeyEvent.VK_N);
    itemNimbus  . setToolTipText("Nimbus Layout ");
    itemNimbus  . addActionListener(new ActionListener()
      {
        public void actionPerformed(ActionEvent ae)
        {
          WindowManager.Nimbus();
          UpdateWindowLayout();
        }
      });
      
    itemMotif  = new JMenuItem("Motif");
    itemMotif  . setMnemonic(KeyEvent.VK_N);
    itemMotif  . setToolTipText("Motif Layout ");
    itemMotif  . addActionListener(new ActionListener()
      {
        public void actionPerformed(ActionEvent ae)
        {
          WindowManager.Motif();
          UpdateWindowLayout();
        }
      });
      
    itemCustomLookAndFeel  = new JMenuItem("CustomLook");
    itemCustomLookAndFeel  . setEnabled(false);
    itemCustomLookAndFeel  . setMnemonic(KeyEvent.VK_U);
    itemCustomLookAndFeel  . setToolTipText("Custom Layout ");
    itemCustomLookAndFeel  . addActionListener(new ActionListener()
      {
        public void actionPerformed(ActionEvent ae)
        {
          //UIManager.setLookAndFeel(new com.nilo.plaf.ninrod.NimRODLookAndFeel());
          UpdateWindowLayout();
        }
      });
      
    itemCrossPlataform  = new JMenuItem("Cross Plataform");
    itemCrossPlataform  . setMnemonic(KeyEvent.VK_C);
    itemCrossPlataform  . setToolTipText("Cross Plataform Layout");
    itemCrossPlataform  . addActionListener(new ActionListener()
      {
        public void actionPerformed(ActionEvent ae)
        {
          WindowManager.LocalPlataform();
          UpdateWindowLayout();
        }
      });
    
    menuAction  = new JMenu("Action");
    menuAction  . setMnemonic(KeyEvent.VK_A);
    menuAction  . add(itemServerName);
    menuAction  . add(itemServerPort);
    menuAction  . add(itemConnect);
    menuAction  . add(itemClose);
    
    menuLayout  = new JMenu("Layout");
    menuLayout  . setMnemonic(KeyEvent.VK_L);
    menuLayout  . add(itemLocalSystem);
    menuLayout  . add(itemNimbus);
    menuLayout  . add(itemMotif);
    menuLayout  . add(itemCustomLookAndFeel);
    menuLayout  . add(itemCrossPlataform);
    
    menu = new JMenuBar();
    
    menu.add(menuAction);
    menu.add(menuLayout);
    
    frame.setJMenuBar(menu);
  }
  
  /* Additional Methods */
  
  void sendMessage(String str)
  {
    try
    {
      out.writeUTF (str);
    }catch(IOException e)
     {
       JOptionPane.showMessageDialog(window, "Erro ao enviar Dados.");
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
  
  Socket Connect()
  {
    try
    {
      Socket sck  = new Socket (servername, Integer.parseInt(serverport));
      thread = new Thread(this);
      thread.start();
      return (sck);
    }catch(IOException e)
     {
       return (null);
     }
  }
  
  void Update()
  {
    frame.pack();
  }
  
  void UpdateWindowLayout()
  {
    WindowManager.Update(frame);
  }
  
  
  
  gui (String title, int w, int h)
  {
    frame =  new JFrame("title");
    
    WindowManager.Motif();
    
    window  = frame.getContentPane();
    window.setLayout(new GridLayout(2,2)); 
    
    SCREEN_W = w;
    SCREEN_H = h;
    
    addMenu(frame);
    addTextArea(frame);
    
    /*List<String> laf = new ArrayList();
    laf = WindowManager.getInstaledLookAndFeel();
    for(int i = 0;i < laf.size();i++)
      log.append(laf + "\n");*/

    Icon.setIcon(frame, "/resource/linux.jpg");
    
    frame.setLocationRelativeTo(null);
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setLayout(new FlowLayout());
    frame.addKeyListener(this);
    frame.setLocation(0 ,0);
    frame.setTitle(title);
    frame.setVisible(true);
    frame.setResizable(false);
    frame.pack();
  }
  
  public static void main(String[] arg)
  {
    gui g = new gui("Client", 640, 480);
    while(true)
    {
       try
       {
         Thread.sleep(100);
       }catch(Exception e) { }
       g.Update();
    }
  }
  
  /* Escuta de acoes */
  public void actionPerformed(ActionEvent ae){ }
  
  
  /* Key Listeners */
  public void keyTyped(KeyEvent e){}
  
  public void keyPressed(KeyEvent e)
  {
    if(e.getKeyCode() == KeyEvent.VK_ESCAPE) System.exit(0);
    
    else if(e.getSource() == msgToSend && e.getKeyCode() == KeyEvent.VK_ENTER)
    {
      if(!msgToSend.getText().equals(""))
      {
        sendMessage(msgToSend.getText());
        msgToSend.setText("");
      }
    }
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

  
  /*****************************************************************
    Lera os dados enviados pelo servidor e os colocara na tela
  ******************************************************************/
  public void run()
  {
    String     msg;
    
    while( true )
    {
      try
      {
        msg = in.readUTF();
        log.append(msg + "\n");
      }catch(IOException e)
       {
         log.append("\n\tServer is offline.\n");
         Thread.currentThread().stop();
         break;
       }
    }
  }
  
  
};

