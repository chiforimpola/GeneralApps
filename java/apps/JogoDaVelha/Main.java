import java.awt.event.*;
import java.awt.*;
import javax.swing.*;
import java.io.*;

class Window extends JFrame implements ActionListener,MouseListener
{
  Container     wnd;
  JTextField    txtf[] = new JTextField[9];
  JButton       exit;
  JButton       btn[] = new JButton[LIMIT],reset;
  JLabel        player1,player2,vs,turn,won;
  static int    larg = 50,alt = 50;
  static int    LIMIT = 9,SCREENX = 640,SCREENY = 480;
  static int    btn_larg = 100,btn_alt = 25;
  static int    txtfX_ini = (SCREENX/2) - larg*2,txtfY_ini = (SCREENY/2) - alt*2;
  int           marcou[] = new int[LIMIT];
  int           btn_player1[] = new int[LIMIT],btn_player2[] = new int[LIMIT];
  int           index_player1 = 0,index_player2 = 0;
  int           player_turn,aux_win = 0;
  int           qtd_marcada = 0,vencedor = 0;
  Window(String nome)
  {
    super(nome);
    int x1 = txtfX_ini,y1 = txtfY_ini,cont =  player_turn = 0;
    wnd = getContentPane();
    for(int i = 0;i < LIMIT;i++)
    {
      marcou[i] = 0;
      txtf[i] = new JTextField();
      txtf[i] . addMouseListener(this);
      txtf[i] . setEditable(false);
      txtf[i] . setBounds(x1,y1,larg,alt);
      x1 += larg;
      cont++;
      if(cont == 3)
      {
        x1 = txtfX_ini;
        y1 += alt;
        cont = 0;
      }
      wnd . add(txtf[i]);
    }
    cont = 0;
    x1 = (SCREENX / 2) - btn_larg * 2;
    y1 = 50;
    for(int i = 0;i < LIMIT;i++)
    {
      btn[i] = new JButton("-");
      btn[i] . addActionListener(this);
      btn[i] . setBounds(x1,y1,btn_larg,btn_alt);
      x1 += btn_larg;
      cont++;
      if(cont == 3)
      {
        cont = 0;
        y1 += btn_alt;
        x1 = (SCREENX / 2) - btn_larg * 2;
      }
      wnd . add(btn[i]);
    }
    player1  = new JLabel("PLAYER 1");
    player2  = new JLabel("Player 2");
    vs       = new JLabel("VS");
    won      = new JLabel("");
    player1 . setBounds(0,0,100,50);
    vs      . setBounds(100,0,50,50);
    player2 . setBounds(200,0,100,50);
    turn     = new JLabel("!");
    turn    . setBounds(40,30,20,20);
    won     . setBounds( (SCREENX/2) - 100,SCREENY - 200,100,30);
    exit = new JButton("Exit");
    exit . setBounds( (SCREENX/2) - 100,SCREENY - 100,100,25);
    exit . addActionListener(this);
    reset    = new JButton("Reset");
    reset    . setBounds(0,SCREENY - 100,100,25);
    reset    . addActionListener(this);
    wnd  . add(player1);
    wnd  . add(player2);
    wnd  . add(vs);
    wnd  . add(turn);
    wnd  . add(won);
    wnd  . add(exit);
    wnd  . add(reset);
    addMouseListener(this);
    setSize(SCREENX,SCREENY);
    setLayout(null);
    setLocationRelativeTo(null);
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    setVisible(true);
  }
  //Organiza a ordem em que os botoes foram pressionados
  void Organiza()
  {
    int aux = 0;
    if(index_player2 > 2)
    {
      for(int i = 0;i < index_player2;i++)
      {
        for(int i2 = i+1;i2 < index_player2;i2++)
        if(btn_player2[i] > btn_player2[i2])
        {
          aux = btn_player2[i];
          btn_player2[i] = btn_player2[i2];
          btn_player2[i2] = aux;
          i2 = i + 1;
        }
      }
    }
    if(index_player1 > 2)
    {
      for(int i = 0;i < index_player1;i++)
      {
        for(int i2 = i+1;i2 < index_player1;i2++)
        if(btn_player1[i] > btn_player1[i2])
        {
          aux = btn_player1[i];
          btn_player1[i] = btn_player1[i2];
          btn_player1[i2] = aux;
          i2 = i + 1;
        }
      }
    }
  }
  void Won(int who)
  {
    switch(who)
    {
        case 0:
         won.setText("Player 1 venceu!");
         break;
        case 1:
         won.setText("Player 2 venceu!");
         break;
    }
    vencedor = 1;
  }
  public void mouseClicked (MouseEvent me){}
  public void mousePressed (MouseEvent me){}
  public void mouseReleased (MouseEvent me){} 
  public void mouseEntered (MouseEvent me){}
  public void mouseExited (MouseEvent me){}
  public void actionPerformed(ActionEvent ae)
  {
    if(ae.getSource() == exit)System.exit(0);
    else if(ae.getSource() != reset)
    {
      qtd_marcada++;
      for(int i = 0;i < LIMIT;i++)
      {
         if(ae.getSource() == btn[i] && marcou[i] == 0)
         {
           marcou[i] = 1;
           btn[i] . setEnabled(false);
           switch(player_turn)
           {
               case 0:
                 txtf[i] . setText("     X");
                 btn[i] . setText("X");
                 player1.setText("Player 1");
                 player2.setText("PLAYER 2");
                 player_turn = 1;
                 turn    . setBounds(240,30,20,20);
                 btn_player1[index_player1++] = i;
                 break;
               case 1:
                 txtf[i] . setText("     O");
                 btn[i] . setText("O");
                 player1.setText("PLAYER 1");
                 player2.setText("Player 2");
                 player_turn = 0;
                 turn    . setBounds(40,30,20,20);
                 btn_player2[index_player2++] = i;
                 break;
           }
         }
      }
    }
    else if(ae.getSource() == reset)
    {
      for(int i = 0; i < LIMIT;i++)
      {
        txtf[i].setText("");
        btn[i].setText("-");
        btn[i].setEnabled(true);
        marcou[i] = 0;
      }
      for(int i = 0;i < index_player1;i++)
        btn_player1[i] = -1;
      for(int i = 0;i < index_player2;i++)
        btn_player2[i] = -1;
      index_player1 = index_player2 = 0;
      player1.setText("PLAYER 1");
      player2.setText("Player 2");
      turn    . setBounds(40,30,20,20);
      won     . setText("");
      player_turn = 0;
      qtd_marcada = vencedor = 0;
    }
    Organiza();
    aux_win = 0;
    switch(player_turn)
    {
            /*Linhas
              0,1,2
              3,4,5
              6,7,8
              Colunas
              0,3,6
              1,4,7
              2,5,8
              Diagonais
              0,4,8
              2,4,6
            */
        case 0://Ultimo quem jogou foi player1
          if(index_player2 > 2)
          {
            for(int i = 0;i < index_player2;i++)
            {
                //Linhas
              for(int i2 = 0;i2 < 3;i2++)
              {
                if(btn_player2[i] == i2 && btn_player2[i+1] == i2+1 && btn_player2[i+2] == i2+2 && i2 == 0)
                  Won(1);
                if(btn_player2[i] == i2+3 && btn_player2[i+1] == i2+4 && btn_player2[i+2] == i2+5 && i2 == 0)
                  Won(1);
                if(btn_player2[i] == i2+6 && btn_player2[i+1] == i2+7 && btn_player2[i+2] == i2+8 && i2 == 0)
                  Won(1);
              }
            }
                //Colunas
              aux_win = 0;
              for(int i2 = 0;i2 < index_player2;i2++)
              {
                if(btn_player2[i2] == 0) aux_win++;
                if(btn_player2[i2] == 3) aux_win++;
                if(btn_player2[i2] == 6) aux_win++;
                if(aux_win == 3)
                  Won(1);
              }
              aux_win = 0;
              for(int i2 = 0;i2 < index_player2;i2++)
              {
                if(btn_player2[i2] == 1) aux_win++;
                if(btn_player2[i2] == 4) aux_win++;
                if(btn_player2[i2] == 7) aux_win++;
                if(aux_win == 3)
                  Won(1);
              }
              aux_win = 0;
              for(int i2 = 0;i2 < index_player2;i2++)
              {
                if(btn_player2[i2] == 2) aux_win++;
                if(btn_player2[i2] == 5) aux_win++;
                if(btn_player2[i2] == 8) aux_win++;
                if(aux_win == 3)
                  Won(1);
              }
                //Diagonais
             aux_win = 0;
             for(int i2 = 0;i2 < index_player2;i2++)
             {
               if(btn_player2[i2] == 0) aux_win++;
               if(btn_player2[i2] == 4) aux_win++;
               if(btn_player2[i2] == 8) aux_win++;
               if(aux_win == 3) Won(1);
             }
             aux_win = 0;
             for(int i2 = 0;i2 < index_player2;i2++)
             {
               if(btn_player2[i2] == 2) aux_win++;
               if(btn_player2[i2] == 4) aux_win++;
               if(btn_player2[i2] == 6) aux_win++;
               if(aux_win == 3) Won(1);
             }
          }
          break;
        case 1://Ultimo quem jogou foi player0
          if(index_player1 > 2)
          {
            for(int i = 0;i < index_player1;i++)
            {
                //Linhas
              for(int i2 = 0;i2 < 3;i2++)
              {
                if(btn_player1[i] == i2 && btn_player1[i+1] == i2+1 && btn_player1[i+2] == i2+2 && i2 == 0)
                  Won(0);
                if(btn_player1[i] == i2+3 && btn_player1[i+1] == i2+4 && btn_player1[i+2] == i2+5 && i2 == 0)
                  Won(0);
                if(btn_player1[i] == i2+6 && btn_player1[i+1] == i2+7 && btn_player1[i+2] == i2+8 && i2 == 0)
                  Won(0);
              }
            }
                //Colunas
              aux_win = 0;
              for(int i2 = 0;i2 < index_player1;i2++)
              {
                if(btn_player1[i2] == 0) aux_win++;
                if(btn_player1[i2] == 3) aux_win++;
                if(btn_player1[i2] == 6) aux_win++;
                if(aux_win == 3)
                  Won(0);
              }
              aux_win = 0;
              for(int i2 = 0;i2 < index_player1;i2++)
              {
                if(btn_player1[i2] == 1) aux_win++;
                if(btn_player1[i2] == 4) aux_win++;
                if(btn_player1[i2] == 7) aux_win++;
                if(aux_win == 3)
                  Won(0);
              }
              aux_win = 0;
              for(int i2 = 0;i2 < index_player1;i2++)
              {
                if(btn_player1[i2] == 2) aux_win++;
                if(btn_player1[i2] == 5) aux_win++;
                if(btn_player1[i2] == 8) aux_win++;
                if(aux_win == 3)
                  Won(0);
              }
                //Diagonais
             aux_win = 0;
             for(int i2 = 0;i2 < index_player1;i2++)
             {
               if(btn_player1[i2] == 0) aux_win++;
               if(btn_player1[i2] == 4) aux_win++;
               if(btn_player1[i2] == 8) aux_win++;
               if(aux_win == 3) Won(0);
             }
             aux_win = 0;
             for(int i2 = 0;i2 < index_player1;i2++)
             {
               if(btn_player1[i2] == 2) aux_win++;
               if(btn_player1[i2] == 4) aux_win++;
               if(btn_player1[i2] == 6) aux_win++;
               if(aux_win == 3) Won(0);
             }
          }
          break;
    }
    if(qtd_marcada == 9 && vencedor == 0) won.setText(">>>>Draw!<<<<");
  }
}

public class Main
{
    public Main(){}
    public static void main(String[] args)
    {
      Window wnd = new Window("****Jogo da Velha****");
    }
    
}
