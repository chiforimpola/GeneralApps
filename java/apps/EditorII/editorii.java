import java.awt.event.*;
import java.awt.*;
import javax.swing.*;
import java.io.*;
import java.io.File.*;

class FontInterface extends JFrame implements ActionListener
{
  static int	  RADIO = 5;
  static int	  SCREENX = 480,SCREENY = 240;
  static int	  LARG = 100,ALT = 30;
  static int	  BTNLARG = 100,BTNALT = 30;
  int		  mode = 0;//0 = Fonte;1 = Plano de fundo
  int		  fontColor = 0,backgroundColor = 4;
  Container	  wnd = getContentPane();
  ButtonGroup	  group = new ButtonGroup();
  JRadioButton[]  radio = new JRadioButton[RADIO];
  JButton	  close;
  JTextArea	  txta;
  //.  setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
  FontInterface(String titulo){ super(titulo); }
  void addButtons()
  {
    close = new JButton("Close");
    close . addActionListener(this);
    close . setBounds((SCREENX/2)-BTNLARG/2,SCREENY-BTNALT*2,BTNLARG,BTNALT);
    close . setMnemonic(KeyEvent.VK_C);
    close . setToolTipText("Close window and return to main aplication.");
    wnd   . add(close);
  }
  void addRadioButtons()
  {
    int x = 0,y = 0,larg = 100,alt = 30;
    for(int i = 0;i < RADIO;i++)
    {
      radio[i] = new JRadioButton();
      radio[i] . addActionListener(this);
      fontColor = 0;
      backgroundColor = 4;
      switch(i)
      {
	case 0:
	  radio[i].setText("Black");
	  radio[i].setBounds(x,y,larg,alt);
	  radio[i].setSelected(true);
	  radio[i].setMnemonic(KeyEvent.VK_B);
	  break;
	case 1:
	  radio[i].setText("Blue");
	  radio[i].setBounds(x,y,larg,alt);
	  radio[i].setMnemonic(KeyEvent.VK_L);
	  break;
	case 2:
	  radio[i].setText("Red");
	  radio[i].setBounds(x,y,larg,alt);
	  radio[i].setMnemonic(KeyEvent.VK_R);
	  break;
	case 3:
	  radio[i].setText("Green");
	  radio[i].setBounds(x,y,larg,alt);
	  radio[i].setMnemonic(KeyEvent.VK_G);
	  break;
	case 4:
	  radio[i].setText("White");
	  radio[i].setBounds(x,y,larg,alt);
	  radio[i].setMnemonic(KeyEvent.VK_W);
	  break;
      }
      x += larg;
      if(x + larg > SCREENX)
      {
	x = 0;
	y += alt;
      }
      wnd.add(radio[i]);
    }
  }
  int getFontColor(){ return fontColor; }
  int getBackgroundColor(){ return backgroundColor; }
  void Finaliza()
  {
    //setResizable(false);
    setSize(SCREENX,SCREENY);
    setLayout(null);
    setLocationRelativeTo(null);
    setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
    setVisible(false);
  }
  void setAreaToEdit(JTextArea txta,int mode){ this.txta = txta;this.mode = mode; }
  void setVisible(int modo)
  {
    switch(modo)
    {
      case 0:
	setVisible(false);
	break;
      case 1:
	setVisible(true);
	break;
    }
  }
  void init()
  {
    addButtons();
    addRadioButtons();
    Finaliza();
  }
  //***Escuta de Acoes***
  public void actionPerformed(ActionEvent e)
  {
    if(e.getSource() == close) setVisible(false);
    for(int i = 0;i < RADIO;i++)
    {
      if(e.getSource() == radio[i])
      {
	//***Desmarco a opcao que estava marcada anteriormente**
	for(int i2 = 0;i2 < RADIO;i2++)
	{
	  if(radio[i2].isSelected() == true && i2 != i)
	  {
	    radio[i2].setSelected(false);
	    break;
	  }
	  else if(radio[i2].isSelected() == false && i2 == i) radio[0].setSelected(true);
	}
	//***Opcao desmarcada***
	//***Altero a cor baseado na opcao selecionada***
	switch(i)
	{	 //black,blue,red,green,white
	  case 0:
	    if(mode == 0){ txta.setForeground(Color.black);fontColor = 0; }
	    else	  { txta.setBackground(Color.black);backgroundColor = 0; }
	    break;
	  case 1:
	    if(mode == 0) { txta.setForeground(Color.blue);fontColor = 1; }
	    else	  { txta.setBackground(Color.blue);backgroundColor = 1; }
	    break;
	  case 2:
	    if(mode == 0) { txta.setForeground(Color.red);fontColor = 2; }
	    else	  { txta.setBackground(Color.red);backgroundColor = 2; }
	    break;
	  case 3:
	    if(mode == 0) { txta.setForeground(Color.green);fontColor = 3; }
	    else	  { txta.setBackground(Color.green);backgroundColor = 3; }
	    break;
	  case 4:
	    if(mode == 0) { txta.setForeground(Color.white);fontColor = 4; }
	    else	  { txta.setBackground(Color.white);backgroundColor = 4; }
	    break;
	}
      }
    }
  }
}

class Window extends JFrame implements ActionListener,MouseListener,KeyListener
{
  Container	editor = getContentPane();
  static int	SCREENX = 640,SCREENY = 480;
  static int	LIMIT_MENU = 5;
  static int	LIMIT_COMPONENT = 5;
  JScrollPane	scroll1;
  JTextArea	txta;
  JMenuBar	menuBar;
  JMenu 	menuArquivo, menuLayout, menuHelp;
  JMenuItem	itemOpenArq, itemSaveArq, itemCloseArq, itemSair, itemAbout, itemFont, itemBackground;
  //Para mostrar o nome do arquivo e preencher a area de texto com seu conteudo
  JTabbedPane	tab = new JTabbedPane();
  File		arq = null;
  //***Crio o objeto da classe de interface da fonte***

  FontInterface _font = new FontInterface("Font Layout");

//********************Metodos****************************
  Window(String nome)
  {
    super(nome);
    _font.init();
  }
  void addTextArea()
  {
    txta = new JTextArea();
    txta.addKeyListener(this);
    scroll1 = new JScrollPane(txta);
    scroll1 . setBounds(0,40,SCREENX-20,SCREENY-100);
    editor  . add(scroll1);
  }
  void addMenu()
  {
    menuArquivo  = new JMenu("Arquivo");
    menuArquivo  . setMnemonic(KeyEvent.VK_A);
    //**************Adiciono o item Open em Arquivo**************
    itemOpenArq  = new JMenuItem("Open");
    itemOpenArq  . addActionListener(this);
    itemOpenArq  . setMnemonic(KeyEvent.VK_O);
    itemOpenArq  . setToolTipText("Open the choosed file.");
    menuArquivo  . add(itemOpenArq);
    //**************Adiciono o item Save em Arquivo**************
    itemSaveArq  = new JMenuItem("Save");
    itemSaveArq  . setMnemonic(KeyEvent.VK_S);
    itemSaveArq  . addActionListener(this);
    itemSaveArq  . setToolTipText("Save the opened File.");
    itemSaveArq  . setEnabled(false);
    menuArquivo  .  add(itemSaveArq);
    //**************Adiciono o item Close em Arquivo**************
    itemCloseArq  = new JMenuItem("Close");
    itemCloseArq  . setMnemonic(KeyEvent.VK_C);
    itemCloseArq  .addActionListener(new ActionListener()
    {
      public void actionPerformed(ActionEvent e)
      {
	txta.setText(" ");
	itemSaveArq   . setEnabled(false);
	itemCloseArq  . setEnabled(false);
      }
    });
    itemCloseArq  . setToolTipText("Close the file, cleaning the text area.");
    itemCloseArq  . setEnabled(false);
    itemOpenArq.setMnemonic(KeyEvent.VK_O);
    menuArquivo . add(itemCloseArq);
    //**************Adiciono o item Sair em Arquivo**************
    itemSair	 = new JMenuItem("Exit");
    itemSair	 . setMnemonic(KeyEvent.VK_X);
    itemSair.addActionListener(new ActionListener()
    {
      public void actionPerformed(ActionEvent e){ System.exit(0); }
    });
    itemSair. setToolTipText("Close aplication.");
    itemSair.setMnemonic(KeyEvent.VK_X);
    menuArquivo  . add(itemSair);
    //**************Adiciono o menu HELP**************
    menuHelp	 = new JMenu("HELP");
    menuHelp	 . setMnemonic(KeyEvent.VK_H);
    //**************Adiciono o menu Layout e seus submenus**************
    menuLayout	 = new JMenu("Layout");
    menuLayout	 . setMnemonic(KeyEvent.VK_L);
    itemFont	 = new JMenuItem("Font");
    itemFont	 . setToolTipText("Change Font");
    itemFont	 . setMnemonic(KeyEvent.VK_F);
    itemFont	 . addActionListener(this);
    menuLayout	 . add(itemFont);
    itemBackground     = new JMenuItem("BackGround");
    itemBackground     . setToolTipText("Change BackGround Layout");
    itemBackground     . setMnemonic(KeyEvent.VK_B);
    itemBackground     . addActionListener(this);
    menuLayout	       . add(itemBackground);
    //**************Adiciono o item About em HELP**************
    itemAbout	 = new JMenuItem("About");
    itemAbout	 . setMnemonic(KeyEvent.VK_T);
    itemAbout	 . addActionListener(new ActionListener()
    {
      public void actionPerformed(ActionEvent ae)
      {
	JOptionPane.showMessageDialog(
	    editor,
	    "Feito por Leonardo. Este aplicativo demonstra a facilidade de se programar\n"
	  + "em Java utilizando componentes da Classe Swing. Neste material utilizo escu-\n"
	  + "ta de eventos em itens de menus que foram, obviamente, adicionados em menus.\n"
	  + "Recentemente adicionei um FileChooser.\n"
	  + "Ver: 0.2");
      }
    });
    menuHelp	 . add(itemAbout);
    menuBar	 = new JMenuBar();
    menuBar	 . add(menuArquivo);
    menuBar	 . add(menuLayout);
    menuBar	 . add(menuHelp);
    menuBar	 . setBounds(0,0,SCREENX,30);
    editor.add(menuBar);
  }
  //******************Adiciono a tab******************
  void addTab()
  {
    tab.addTab("Vazio", null, txta, "Does nothing");
    editor.add(tab);
  }
  void Finaliza()
  {
    setResizable(false);
    setSize(SCREENX,SCREENY);
    setLayout(null);
    setLocationRelativeTo(null);
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    setVisible(true);
  }
  //*****Eventos de Mouse*****
  public void mouseClicked  (MouseEvent me){}
  public void mousePressed  (MouseEvent me){}
  public void mouseReleased (MouseEvent me){} 
  public void mouseEntered  (MouseEvent me){}
  public void mouseExited   (MouseEvent me){}
  //*****Eventos de Teclas*****
  public void keyTyped(KeyEvent e)
  {
    if(e.getKeyChar() == '{') { }
  }
  public void keyPressed(KeyEvent e) {}
  public void keyReleased(KeyEvent e){}

  //Escuta de acoes
  public void actionPerformed(ActionEvent ae)
  {
     //**************Para abrir um arquivo**************
    if(ae.getSource() == itemOpenArq)
    {
      JFileChooser fc = new JFileChooser("C:\\");
      int OK = fc.showOpenDialog(this);
      if(OK == JFileChooser.APPROVE_OPTION)
      {
	arq = new File(fc.getSelectedFile().getPath());//Vejo o arquivo selecionado, depois o caminho dele
	if(arq.exists() == true)
	{
	  FileInputStream fis = null;
	  BufferedInputStream bis = null;
	  DataInputStream dis = null;
	  try
	  {
	    String aux;
	    fis = new FileInputStream(arq);
	    bis = new BufferedInputStream(fis);
	    dis = new DataInputStream(bis);
	    txta.setText("");
	    while (dis.available() != 0) txta.append(dis.readLine()+"\n");
	    fis.close();
	    bis.close();
	    dis.close();
	    txta.requestFocus();
	  }catch (IOException io){ }
	  //***Habilito a opcao de salvar e fechar arquivo***
	  itemSaveArq  . setEnabled(true);
	  itemCloseArq . setEnabled(true);
	}
	else
	{
	  JOptionPane.showMessageDialog(
	    fc,
	    "Erro ao tentar abrir o arquivo!\n"
	  + "Caminho: '" + arq.getPath() + "'\n");
	}
      }
    }
     //**************Fim da Abertura de Arquivo**************
     //**************Save de Arquivo**************
    if(ae.getSource() == itemSaveArq)
    {
    //Salvo o texto original em um arquivo temporario
      File temp = new File(arq.getPath() + "$");
      if(arq.exists() == true)
      {
	try
	{
	  arq.createNewFile();
	  BufferedWriter out = new BufferedWriter(new FileWriter(temp));
	  out.write(txta.getText());
	  out.close();
	}catch(IOException e){ }
      }
    }
     //**************Fim do Save de Arquivo**************
     //**************Troca de Font***********************
    if(ae.getSource() == itemFont)
    {
      _font.setAreaToEdit(txta,0);
      _font.setVisible(1);
    }
    else if(ae.getSource() == itemBackground)
    {
      _font.setAreaToEdit(txta,1);
      _font.setVisible(1);
    }
  }
}

public class editorii
{
    public editorii(){}
    public static void main(String[] args)
    {
      Window wnd = new Window("****Editor de Texto - Java****");
      wnd.addTextArea();
      wnd.addMenu();
      //wnd.addTab();
      wnd.Finaliza();
    }
}
