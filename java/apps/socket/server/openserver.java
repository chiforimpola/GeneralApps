
import java.awt.event.*;
import java.awt.*;
import javax.swing.*;
import java.io.*;
import java.net.Socket;


public class openserver extends JFrame implements KeyListener
{
    static int   SCREEN_W   = 640,
   		         SCREEN_H   = 480,
		         MENU_H	    = 20,
		         BTN_W    = 100,
		         BTN_H    = 20,
		         BTN_X    = 0,
		         BTN_Y    = 50,
		         TXTF_W	  = SCREEN_W - (SCREEN_W * 9 /10),
		         TXTF_H	  = 20,
		         TXTA_W	  = SCREEN_W - (SCREEN_W * 1)/10,
		         TXTA_H	  = SCREEN_H - (SCREEN_H * 3)/10,
		         porta	  = 8080;
    static Container	 wnd;
    static JLabel       lbl;
    static JTextField   txtf;
    static TextArea	    historico;
    static JButton      online,
                        offline;
    static Socket       client;
    static Server       server;
    static boolean      ONLINE;
    static openserver   os;
    
  openserver()
  {
    super("off-line");
    wnd  = getContentPane();
    lbl  = new JLabel("Porta");
    lbl.setBounds(0, 0, 50, 30);
    txtf = new JTextField();
    txtf.setBounds(60, 0, TXTF_W, TXTF_H);
    online = new JButton("online");
    online.setBounds(BTN_X, BTN_Y, BTN_W, BTN_H);
    online.setMnemonic(KeyEvent.VK_O);
    online.addActionListener(new ActionListener()
    {
      public void actionPerformed(ActionEvent e)
      {
	    try
	    {
	      if(txtf.getText().equals(""))
            JOptionPane.showMessageDialog(wnd, "Porta deve ser definida.");
         else
             Online();
        }catch(Exception e2)
	    {
	      e2.printStackTrace();
	    }
      }
    });
    offline = new JButton("offline");
    offline.setBounds(BTN_X + BTN_W, BTN_Y, BTN_W, BTN_H);
    offline.setEnabled(false);
    offline.setMnemonic(KeyEvent.VK_L);
    offline.addActionListener(new ActionListener()
    {
      public void actionPerformed(ActionEvent e)
      {
	      if(ONLINE)
          {
            server.close();
            online.setEnabled(true);
            offline.setEnabled(false);
            setTitle("offline");
            ONLINE = false;
          }
      }
    });
    historico = new TextArea();
    historico.setBounds(0, 100, TXTA_W, TXTA_H);
    historico.setEditable(false);
    wnd.add(lbl);
    wnd.add(txtf);
    wnd.add(historico);
    wnd.add(online);
    wnd.add(offline);
    Create();
  }
  
  void Create()
  {
    setResizable(false);
    setSize(SCREEN_W, SCREEN_H);
    setLayout(null);
    setLocationRelativeTo(null);
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    setVisible(true);
    wnd.addKeyListener(this);
  }
  
  public void keyTyped(KeyEvent e){}
  public void keyPressed(KeyEvent e)
  {
    if(e.getKeyCode() == KeyEvent.VK_ESCAPE) System.exit(0);
  }
  public void keyReleased(KeyEvent e){}
  
  void Online()
  {
    online.setEnabled(false);
    offline.setEnabled(true);
    client	= new Socket();
    server	= new Server(historico, Integer.parseInt(txtf.getText()));
    server.online();
    server.watingClientConnection();
    
    setTitle("online");
    ONLINE = true;
  }
  
  public static void main(String[] str)
  {
    os = new openserver();
    while(true)
      while(ONLINE) server.acceptClient();
  }
}
