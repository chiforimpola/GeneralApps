import java.awt.event.*;
import java.awt.*;
import javax.swing.*;
import java.io.*;
import java.util.Random;

class JogoDaForca extends JFrame implements ActionListener,KeyListener
{
  Container           wnd;
  JLabel              lbl_dica,lbl_erros;
  JTextField          txtf[] = new JTextField[LIMIT],letra;
  JTextArea           txta_erros;
  JButton             confirmar,sair;
  static int          LIMIT = 20;
  static int          SCREENX = 640,SCREENY = 480;
  int                 random_number;
  int                 erros = 0,acertos = 0;
  int                 cont = 0,total;
  int                 iletras_certas = 0;
  String              palavra[] = new String[LIMIT],dica[] = new String[LIMIT];
  JogoDaForca(String titulo){ super(titulo); }
  
  void CriarJanela()
  {
      int x = 0;
//Crio qtd de labels baseado no numero de letras que a string possui
      //lbl = new JLabel[palavra[random_number].length()];
      for(int i = 0;i < palavra[random_number].length();i++)
      {
        txtf[i] = new JTextField();
        txtf[i].setBounds(x,200,50,50);
        txtf[i].setEditable(false);
        x += 50;
        wnd.add(txtf[i]);
      }
    total = palavra[random_number].length();
    confirmar = new JButton("Confirmar");
    confirmar.setBounds(0,SCREENY-100,100,35);
    confirmar.addActionListener(this);
    confirmar.setEnabled(false);
    sair = new JButton("SAIR");
    sair.setBounds(100,SCREENY-100,100,35);
    sair.addActionListener(this);
    letra = new JTextField();
    letra.setBounds(0,SCREENY-200,50,50);
    letra.addKeyListener(this);
    txta_erros = new JTextArea("");
    txta_erros . setBounds(0,150,200,30);
    txta_erros . setEditable(false);
    lbl_dica = new JLabel("Dica: " + dica[random_number]);
    lbl_dica.setBounds(0,0,200,30);
    lbl_erros = new JLabel("Erros: " + erros);
    lbl_erros.setBounds(0,40,100,30);
    wnd.add(lbl_dica);
    wnd.add(lbl_erros);
    wnd.add(letra);
    wnd.add(txta_erros);
    wnd.add(confirmar);
    wnd.add(sair);
    setSize(SCREENX,SCREENY);
    setLayout(null);
    setLocationRelativeTo(null);
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    setVisible(true);
    letra.requestFocus();
  }
  
  void LerDB()
  {
    int i = 0,cont = 0;
    Random rand = new Random();
    try
    {
      BufferedReader in = new BufferedReader(new FileReader("Strings.txt"));
      String aux;
      while( in.ready() )
      {
        aux = in.readLine();
        switch(cont)
        {
          case 0://Leu a string
            palavra[i] = aux;
            cont = 1;
            break;
          case 1://Leu a dica
            dica[i++] = aux;
            cont = 0;
            break;
        }
      }
      palavra[random_number] = palavra[random_number].toUpperCase();
      System.out.print(
      "-> "           + palavra[random_number] +
      "\n-> Dica: "   + dica[random_number]    +
      "\n-> Random: " + random_number          +
      "\n-> Letras: " + palavra[random_number].length());
      in.close();
    }catch (IOException e)
     {
       System.out.print("Erro ao abrir ou ler arquivo!");
     }
//Gera um numero aleatorio baseado no numero de strings lidas
     random_number = rand.nextInt( i );
  }
  
  void init()
  {
    wnd = getContentPane();
    LerDB();
    CriarJanela();
  }
  
  public void keyTyped(KeyEvent e)
  {
    if(e.getSource() == letra)
    {
      if( !letra.getText().equals("") ) confirmar.setEnabled(true);
      else confirmar.setEnabled(false);
    }
  }

  
  public void keyPressed(KeyEvent e)  {}
  
  public void keyReleased(KeyEvent e)
  {
    if(e.getSource() == letra)
    {
      if( !letra.getText().equals("") ) confirmar.setEnabled(true);
      else confirmar.setEnabled(false);
    }
  }

  
  public void actionPerformed(ActionEvent ae)
  {
    String aux;
    int   acertou = 0;
    if(ae.getSource() == sair) System.exit(0);
    else if(ae.getSource() == confirmar)
    {
      aux = letra.getText();
      aux = aux.toUpperCase();
      for(int i = 0;i < palavra[random_number].length();i++)
      {
        if( aux.charAt(0) == palavra[random_number].charAt(i) )
        {
          txtf[i].setText("  " +  aux );
          confirmar.setEnabled(false);
          acertou = 1;
          acertos++;
        }
      }
      if(acertou == 0)//Caso tenha errado, incremento o numero de erros
      {
        confirmar.setEnabled(false);
        erros++;
        lbl_erros.setText( "Erros: " + erros );
        txta_erros.append(letra.getText() + " , ");
      }
      else acertou = 0;
      if(erros == total)
      {
        txta_erros.setText("Perdeu");
      }
      else if(acertos == total)
      {
        txta_erros.setText("Venceu");
      }
      letra.setText("");
      letra.requestFocus();
    }
  }
}

public class Main
{
    public Main(){}
    public static void main(String[] args)
    {
      JogoDaForca forca = new JogoDaForca("****Jogo da Forca****");
      forca.init();
    }
    
}
