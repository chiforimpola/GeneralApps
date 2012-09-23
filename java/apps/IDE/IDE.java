import java.awt.event.*;
import java.awt.*;
import javax.swing.*;
import javax.swing.ImageIcon;
import java.io.File;
import java.io.*;

public class IDE extends JFrame implements ActionListener,FocusListener
{
  Container	    jnl;
  JLabel	    lbl1,lbl2,lblrows;//nome e extensao do arquivo,n de linhas
  JTextArea	    txta1;//Area do editor de texto
  JTextField	txtf1,txtf2,txtf3,txtf4;//nome,extensao,cor1,cor2
  JScrollPane   scroll1;
  JButton	    btn1,btnsave,btn2,btnopen,btncolor;
  JFileChooser	save;//nao terminado
  ButtonGroup   group;
  JRadioButton  radio1,radio2,radio3,radio4,radio5;//Foreground
  JRadioButton  radio6,radio7,radio8,radio9,radio10;//Background
  ImageIcon icn1 = new ImageIcon("Icones/Hyuga_Neji.ico");//nao terminado
  IDE(String Titulo)
  {
    super(Titulo);
    jnl    =  getContentPane();
    lbl1   =  new JLabel("Digite o nome e o caminho.");
    lbl2   =  new JLabel("Extensao");
    lblrows=  new JLabel();
    txta1  =  new JTextArea();
    txtf1  =  new JTextField("Nome e Caminho");
    txtf2  =  new JTextField("Extensao");
    save   =  new JFileChooser("C");
    btn1   =  new JButton("FECHAR");
    btn2   =  new JButton("SALVAR II");
    btnopen=  new JButton("Abrir");
    btnsave=  new JButton("SALVAR");
    btncolor= new JButton("Layout");
    scroll1 = new JScrollPane(txta1);
    group  =  new ButtonGroup();
    radio1 =  new JRadioButton("Black");
    radio2 =  new JRadioButton("White");
    radio3 =  new JRadioButton("Green");
    radio4 =  new JRadioButton("Yellow");
    radio5 =  new JRadioButton("Red");
    radio6 =  new JRadioButton("Black");
    radio7 =  new JRadioButton("White");
    radio8 =  new JRadioButton("Green");
    radio9 =  new JRadioButton("Yellow");
    radio10=  new JRadioButton("Red");
    lbl1   .  setBounds(210, 475, 200, 30);
    lbl2   .  setBounds(65,  495, 100, 30);
    lblrows.  setBounds(705, 450, 50,  30);
    scroll1.  setBounds(0,   20,  600,450);
    txtf1  .  setBounds(0,   475, 200,20);
    txtf2  .  setBounds(0,   495, 60, 20);
    btn1   .  setBounds(350, 530, 100,25);
    btn2   .  setBounds(50,  530, 100,25);
    btnopen.  setBounds(250, 530, 100,25);
    btnsave.  setBounds(150, 530, 100,25);
    btncolor. setBounds(450, 530, 100,25);
    radio1 .  setBounds(600, 0,  100,20);
    radio2 .  setBounds(600, 20, 100,20);
    radio3 .  setBounds(600, 40, 100,20);
    radio4 .  setBounds(600, 60, 100,20);
    radio5 .  setBounds(600, 80, 100,20);
    radio6 .  setBounds(700, 0,  100,20);
    radio7 .  setBounds(700, 20, 100,20);
    radio8 .  setBounds(700, 40, 100,20);
    radio9 .  setBounds(700, 60, 100,20);
    radio10.  setBounds(700, 80, 100,20);
    btn1   .  addActionListener(this);
    btn2   .  addActionListener(this);
    btnsave.  addActionListener(this);
    btnopen.  addActionListener(this);
    btncolor. addActionListener(this);
    txta1  .  addFocusListener(this);
    txtf1  .  addFocusListener(this);
    txtf2  .  addFocusListener(this);
    save   .  setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
    jnl    .  add(lbl1);
    jnl    .  add(lbl2);
    jnl    .  add(lblrows);
    jnl    .  add(scroll1);
    jnl    .  add(txtf1);
    jnl    .  add(txtf2);
    jnl    .  add(btn1);
    jnl    .  add(btn2);
    jnl    .  add(btnsave);
    jnl    .  add(btnopen);
    jnl    .  add(btncolor);
    jnl    .  add(save);
    jnl    .  add(radio1);
    jnl    .  add(radio2);
    jnl    .  add(radio3);
    jnl    .  add(radio4);
    jnl    .  add(radio5);
    jnl    .  add(radio6);
    jnl    .  add(radio7);
    jnl    .  add(radio8);
    jnl    .  add(radio9);
    jnl    .  add(radio10);
    txta1  .  setEditable(true);
    txta1  .  setBackground(Color.black);
    txta1  .  setForeground(Color.green);
    btnsave.setEnabled(false);
    setSize(800,600);
    setLayout(null);
    setLocationRelativeTo(null);
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    setVisible(true);
    txtf1.requestFocus();
  }
  public void focusGained(FocusEvent e)
  {
    if(e.getSource() == txta1)
      lblrows.setText(Integer.toString(txta1.getLineCount()));
    if(e.getSource() == txtf1) txtf1.setText("");
    if(e.getSource() == txtf2) txtf2.setText("");
  }
  public void focusLost(FocusEvent e)
  {
    if(e.getSource() == txta1)
      lblrows.setText("");
    if(e.getSource() == txtf1 && txtf1.getText().equals(""))
      txtf1.setText("Nome e Caminho");
    if(e.getSource() == txtf2 && txtf2.getText().equals(""))
      txtf2.setText("Extensao");
  }
  public void actionPerformed(ActionEvent ae)
  {
    if(ae.getSource() == btn1) System.exit(0);
    if(ae.getSource() == btncolor)
    {
//-----------------------------FOREGROUND--------------------------------------
      if(radio1.isSelected() == true)
      {
        txta1.setForeground(Color.black);
        radio1.setSelected(false);
      }
      if(radio2.isSelected() == true)
      {
        txta1.setForeground(Color.white);
        radio2.setSelected(false);
      }
      if(radio3.isSelected() == true)
      {
        txta1.setForeground(Color.green);
        radio3.setSelected(false);
      }
      if(radio4.isSelected() == true)
      {
        txta1.setForeground(Color.yellow);
        radio4.setSelected(false);
      }
      if(radio5.isSelected() == true)
      {
        txta1.setForeground(Color.red);
        radio5.setSelected(false);
      }
//-----------------------------BACKGROUND--------------------------------------
      if(radio6.isSelected() == true)
      {
        txta1.setBackground(Color.black);
        radio6.setSelected(false);
      }
      if(radio7.isSelected() == true)
      {
        txta1.setBackground(Color.white);
        radio7.setSelected(false);
      }
      if(radio8.isSelected() == true)
      {
        txta1.setBackground(Color.green);
        radio8.setSelected(false);
      }
      if(radio9.isSelected() == true)
      {
        txta1.setBackground(Color.yellow);
        radio9.setSelected(false);
      }
      if(radio10.isSelected() == true)
      {
        txta1.setBackground(Color.red);
        radio10.setSelected(false);
      }
    }
    if(ae.getSource() == btnopen)
    {
      if(txtf1.getText().equals(""))
        txta1.setText("Nome ou extensao nao citados para abertura de arquivo!");
      else
      {
        File file;
        file = new File (txtf1.getText()+txtf2.getText());

        //txtf1.setText("");
        //txtf2.setText("");


        FileInputStream fis = null;
        BufferedInputStream bis = null;
        DataInputStream dis = null;
        try
        {
          fis = new FileInputStream(file);
          bis = new BufferedInputStream(fis);
          dis = new DataInputStream(bis);
          txta1.setText("");
          while (dis.available() != 0)
            txta1.append(dis.readLine()+"\n");
          fis.close();
          bis.close();
          dis.close();
          txta1.requestFocus();
        }catch (IOException io){}
      }
    }
    if(ae.getSource() == btn2)
    {
      if(txtf1.getText().equals("") || txtf2.getText().equals(""))
	    txta1.append("Caixa de Texto ou extensao vazia!\n");
      else
      {
	    File file = new File(txtf1.getText()+"."+txtf2.getText());
	    try
	    {
	      if(file.exists() == false)
	      {
            file.createNewFile();
	        try
	        {
	          BufferedWriter out = new BufferedWriter(new FileWriter(file));
	          out.write(txta1.getText());
              out.close();
	        }catch(IOException e){}
	      }
	      else
	      {
	        try
	        {
	          BufferedWriter out = new BufferedWriter(new FileWriter(file));
	          out.write(txta1.getText());
              out.close();
	        }catch(IOException e){}
          }
	    }catch(IOException e){}
	    txtf1.setText("");
	    txtf2.setText("");
        txta1.requestFocus();
      }
    }
    if(ae.getSource() == btnsave)
    {
      int retorno = save.showSaveDialog(jnl);
      if(retorno == JFileChooser.APPROVE_OPTION)
      {
	    txta1.append("SALVO!^^\n");
    	try
	    {
	      File file = new File("vcredist_x86.log");
	      if(file.exists() == false) txta1.append("Criando arquivo\n");
	      else txta1.append("Arquivo ja existe\n");
	      boolean success = file.createNewFile();
	    }catch (IOException e){}
      }
      else txta1.append("cancelado!\n");
    }
  }
  public static void main(String arg[])
  {
    new IDE("IDE Beta 0.2");
  }
}
