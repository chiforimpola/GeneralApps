


import java.awt.event.*;
import java.awt.*;
import javax.swing.*;
import java.io.*;
import java.net.Socket;

/*
  Interface grafica do cliente para comunicacao com o servidor.
  Esta classe possui tambem, uma thread(para este cliente) que
  aguardare dados vindos do servidor e os colocara em uma area de
  texto
*/

public class clientwindow extends JFrame implements KeyListener, Runnable
{
  int		       SCREEN_W   = 640,
		       SCREEN_H   = 480,
		       MENU_H	  = 20,
		       BUTTON_W   = 100,
		       BUTTON_H   = 20,
		       TXTF_W	  = SCREEN_W - (SCREEN_W * 1)/10,
		       TXTF_H	  = 30,
		       TXTA_W	  = SCREEN_W - (SCREEN_W * 1)/10,
		       TXTA_H	  = SCREEN_H - (SCREEN_H * 2)/10,
		       porta	  = 8080,
		       MAX_CONF   = 3;
  String	       text	  = null,
		       IP	  = "evento";
  String[]	       _conf	  = null;
  Container	       wnd	  = getContentPane();
  JTextField	       txtf	  = new JTextField();
  JTextArea	       historico  = new JTextArea();
  JScrollPane	       scroll	  = new JScrollPane(historico);
  JMenuBar	       menuBar	  = new JMenuBar();
  JMenu 	       menu1	  = new JMenu("Acoes"),
		       menu2	  = new JMenu("Acoes");
  JMenuItem	       conectar   = new JMenuItem("Conectar"),
		       desconectar= new JMenuItem("Desconectar"),
		       fechar	  = new JMenuItem("Fechar"),
		       configuracao = new JMenuItem("Configuracoes");
  Configuracao	       conf	  = null;
  Thread	       thread	  = null;
  Socket	       clientSck  = null;
  DataInputStream      in	  = null;
  DataOutputStream     out	  = null;
  
  clientwindow(){}
  
  clientwindow(String titulo)
  {
    super(titulo);
    CreateConfigurationWindow();
    addTxt();
    addMenus();
    Create();
  }

  void CreateConfigurationWindow()
  {
    String[] str = new String[MAX_CONF];
    _conf  = new String[MAX_CONF+1];
    _conf[0] = "Porta";
    _conf[1] = "IP";
    conf = new Configuracao(_conf);
    conf.Visible(true);
	while(!conf.isFinished())
	{
	  try
	  {
	    Thread.sleep(100);
	  }catch(Exception e){ e.printStackTrace(); }
	}
    str = conf.getValues();
    try
    {
      porta = Integer.parseInt(str[0]);
    }catch(Exception e2)
    {
      JOptionPane.showMessageDialog(wnd, "Erro, caixa '" + _conf[0] + "' deve possuir apenas numeros.");
      System.exit(-1);
    }
    IP = str[1];
  }
  
  void Connect()
  {
    try
    {
      clientSck  = new Socket(IP, porta);
      in	 = new DataInputStream(clientSck.getInputStream());
      out	 = new DataOutputStream(clientSck.getOutputStream());
      desconectar.setEnabled(true);
      conectar.setEnabled(false);
      thread	 = new Thread(this);
      thread.start();
    }catch(Exception e)
    {
      JOptionPane.showMessageDialog(
	this,
	"Erro ao conectar" +
	"\n[" + IP + "]\n" +
	"\n[" + porta + "]\n");
    }
  }

  void addMenus()
  {
    conectar.setToolTipText("Conecta ao servidor");
    conectar.setMnemonic(KeyEvent.VK_C);
    conectar.addActionListener(new ActionListener()
    {
      public void actionPerformed(ActionEvent e)
      {
	Connect();
      }
    });
    desconectar.setToolTipText("Desconecta do servidor");
    desconectar.setMnemonic(KeyEvent.VK_D);
    desconectar.setEnabled(false);
    desconectar.addActionListener(new ActionListener()
    {
      public void actionPerformed(ActionEvent e)
      {
	try
	{
	  Thread.currentThread().stop();
	  clientSck.close();
	  desconectar.setEnabled(false);
	  conectar.setEnabled(true);
	}catch(Exception e2)
	{
	  e2.printStackTrace();
	}
      }
    });
    configuracao.setToolTipText("Conecta ao servidor");
    configuracao.setMnemonic(KeyEvent.VK_O);
    configuracao.setEnabled(false);
    /*
      Por alguma razao, a janela de configuracao aparece com erro neste trecho, sendo que
      quando eu utilizo o mesmo trecho de codigo no metodo 'CreateConfigurationWindow()',
      a janela aparece normalmente
    */
    configuracao.addActionListener(new ActionListener()
    {
      public void actionPerformed(ActionEvent e)
      {
	String[] str = new String[MAX_CONF];
	conf = new Configuracao(_conf);
	conf.Visible(true);

	while(!conf.isFinished())
	{
	  try
	  {
	    Thread.sleep(100);
	  }catch(Exception e2){ e2.printStackTrace(); }
	}
	str = conf.getValues();
	porta = Integer.parseInt(str[0]);
	IP = str[1];
      }
    });
    fechar.setToolTipText("Encerra programa");
    fechar.setMnemonic(KeyEvent.VK_F);
    fechar.addActionListener(new ActionListener()
    {
      public void actionPerformed(ActionEvent e)
      {
	System.exit(0);
      }
    });
    menu1.setMnemonic(KeyEvent.VK_A);
    menu1.add(configuracao);
    menu1.add(conectar);
    menu1.add(desconectar);
    menu1.add(fechar);
    menuBar.setBounds(0, 0, SCREEN_W, 25);
    menuBar.add(menu1);
    wnd.add(menuBar, BorderLayout.NORTH);
  }

  void addTxt()
  {
    txtf.setBounds(0, MENU_H, TXTF_W, TXTF_H);
    txtf.addKeyListener(this);
    historico.setEditable(false);
    scroll.setBounds(0, MENU_H + TXTF_H, TXTA_W, TXTA_H);
    wnd.add(txtf);
    wnd.add(scroll);
  }
  
  String getText()
  {
    return (text);
  }

  boolean isFinished()
  {
    if(text == null) return (false);
    else return (true);
  }

  public void keyTyped(KeyEvent e){}
  public void keyPressed(KeyEvent e)
  {
    if(e.getKeyCode() == KeyEvent.VK_ENTER && !txtf.getText().equals(""))
    {
      try
      {
	out.writeUTF(txtf.getText());
	txtf.setText("");
      }catch(Exception e2)
      {
	historico.append("\nErro ao enviar dados.");
      }
    }
  }
  public void keyReleased(KeyEvent e){}
  
  void Create()
  {
    //setResizable(false);
    setSize(SCREEN_W, SCREEN_H);
    setLayout(null);
    setLocationRelativeTo(null);
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    setVisible(true);
  }
  public static void main(String[] arg)
  {
    new clientwindow("Client");
  }
  
  public void run()
  {
    while(true)
    {
      try
      {
	text = in.readUTF();
	historico.append("\n" + text);
      }catch(Exception e)
      {
	historico.append("\nUm erro ocorreu, talvez o servidor esteja offline\n");
	conectar.setEnabled(true);
	desconectar.setEnabled(false);
	break;
      }
    }
  }
}
