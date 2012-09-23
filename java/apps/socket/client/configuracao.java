/*
  O construtor desta classe recebe como parametro um vetor de strings cujo o tamanho
  sera equivalente ao numero de caixas de textos e labels que aparecerao na tela.
  O botao confirma, quando clicado, retornara um vetor de strings equivalente as caixas
  de texto(na ordem em que elas aparecem)
*/

  import javax.swing.*;
  import java.awt.*;
  import java.awt.event.*;

  public class configuracao extends JFrame implements ActionListener
  {
    int 			    porta     = 0,
				    MAX_TXTF  = 0,
				    SCREEN_W  = 1,
				    SCREEN_H  = 1;

    String			    IP	      = null;
    String[]			    _lbl      = null,
				    retorno   = null;
/*
  Apenas 'true' quando todas as caixas de texto possuem alguma coisa e quando
  ha o evento de clique com o botao
*/
    boolean			    ACERTOU   = false;
    Container			    wnd       = getContentPane();
    JLabel[]			    lbl       = null;
    JTextField[]		    txtf      = null;
    JButton			    confirmar = new JButton("confirmar");

    boolean  isFinished(){ return (ACERTOU); }
/*
  apenas deve ser chamado quando a string estiver pronta,
  por isso deve ser usado em conjunto com o metodo isFinished()
*/
    String[] getValues()
    {
      ACERTOU = false;
      setVisible(false);
      return (retorno);
    }

    void Mount(String[] str)
    {
/* Vejo a qtd de strings no vetor */
      while(str[MAX_TXTF] != null) MAX_TXTF++;
      txtf = new JTextField[MAX_TXTF];
      retorno = new String[MAX_TXTF];
      lbl  = new JLabel[MAX_TXTF];
      _lbl = new String[MAX_TXTF];
      _lbl = str;
    }

    void addComponents()
    {
      int x = 0,
	  y = 0,
	  lbl_w   = 50,
	  lbl_h   = 20,
	  txtf_w  = 100,
	  txtf_h  = 20,
	  btn_w   = 100,
	  btn_h   = 20,
	  distance= 20;
      SCREEN_W = txtf_w * 2;
      SCREEN_H = ((txtf_h * MAX_TXTF) + btn_h) * 2;
      //Caixa de texto e Labels
      for(int i = 0;i < MAX_TXTF;i++)
      {
	lbl[i]	= new JLabel(_lbl[i]);
	lbl[i].setBounds(x, y, lbl_w, lbl_h);
	txtf[i] = new JTextField();
	txtf[i].setBounds(x + lbl_w, y, txtf_w, txtf_h);
	wnd.add(txtf[i]);
	wnd.add(lbl[i]);
	y += distance;
      }
      //Botao
      confirmar.setMnemonic(KeyEvent.VK_C);
      confirmar.setBounds((SCREEN_W / 2) - (btn_w/2) , y, btn_w, btn_h);
      confirmar.addActionListener(new ActionListener()
      {
	public void actionPerformed(ActionEvent e)
	{
	  boolean acertou = false;
	  acertou = true;
	  for(int i = 0;i < MAX_TXTF;i++) if(txtf[i].getText().equals(""))
	  {
	    acertou = false;
	    break;
	  }
	  if(acertou)
	    for(int i = 0;i < MAX_TXTF;i++)
	    {
	      retorno[i] = txtf[i].getText();
	      txtf[i].setText("");
	      if(i == MAX_TXTF-1) ACERTOU = true;
	    }
	  else
	    JOptionPane.showMessageDialog(wnd, "Todas as caixas de texto devem possuir valores.");
	}
      });
      wnd.add(confirmar);
    }

    void Finalize()
    {
      setResizable(false);
      setSize(SCREEN_W, SCREEN_H);
      setLayout(null);
      setLocationRelativeTo(null);
      setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
      setVisible(false);
    }

    void Visible(boolean v) { setVisible(v); }

    public void actionPerformed(ActionEvent e){ }

    void addButtons(){ }

    configuracao(String[] str)
    {
      super("Configuracao");
      Mount(str);
      addComponents();
      Finalize();
    }
  }
