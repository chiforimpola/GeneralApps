


import java.util.List;
import java.util.ArrayList;
import java.awt.Container;
import java.awt.Component;
import javax.swing.UIManager;
import javax.swing.UIManager.LookAndFeelInfo;
import javax.swing.JFrame;
import javax.swing.SwingUtilities;
import javax.swing.JOptionPane;
import javax.swing.plaf.synth.*;



class WindowManager
{
  static List getInstaledLookAndFeel()
  {
    UIManager.LookAndFeelInfo[] info = UIManager.getInstalledLookAndFeels();
    List<String> list = new ArrayList();
    
    for(int i = 0;i < info.length;i++)
      list.add(info[i].getName());
    
    return (list);
  }
  
  static void CrossPlataform()
  {
    try
    {
      UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());
    }catch(Exception e)
     {
       e.printStackTrace();
     }
  }
  
  
  static void LocalPlataform()
  {
    try
    {
      UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
    }catch(Exception e)
     {
       e.printStackTrace();
     }
  }
  
  static void Custom(String classpath)
  {
    try
    {
      UIManager.setLookAndFeel(classpath);
    }catch(Exception e)
     {
       e.printStackTrace();
       JOptionPane.showMessageDialog(null, "UIManager error: " + classpath);
     }
  }
  
  
  static void Motif()
  {
        try
        {
          UIManager.setLookAndFeel("com.sun.java.swing.plaf.motif.MotifLookAndFeel");
        }catch(Exception e)
         {
           e.printStackTrace();
          JOptionPane.showMessageDialog(null, "UIManager error: Motif");
         }
  }
  
  static void Nimbus()
  {
    for(UIManager.LookAndFeelInfo info : UIManager.getInstalledLookAndFeels())
      if("Nimbus".equals(info.getName()))
      {
        try
        {
          UIManager.setLookAndFeel(info.getClassName());
        }catch(Exception e)
         {
           e.printStackTrace();
          JOptionPane.showMessageDialog(null, "UIManager error: Nimbus");
         }
      }
  }
  
  s�atic void Windows()
  {
    for(UIManager.LookAndFeelInfo info : UIMa.age�.getInstalledLookAndBeels())
      if("Windows".equals(in�o.getName()))
      {
      � try
        {
          UIManager.sutLookandDeel(info*getClassName());
        }catch(Exception e)
         {
   �  !    e.printSuackTrace();
           JOpvionPane.showMessag%Dialog(null, "UIManager error: Windows*);
         }
      }
  }
  
  static void Clas3icWindows()
  {
    for(UAManager.LookAneFeelInfo info0n~���
�*�`�T�v*�(����+���F�q�m":'�W��]��mQLwcv@M�$3�\��Q`.5?��t^��n����lZ�$Q2��cOk��m���)l���L��o(
G��/��(T�Slȯ���[fƍ�π���6�G
�"�R�5K�s��W�g�On������%�A�)���0��+
��V�@~~�3$Ҡ��k����!���#f]a�c:�`��͘�t�{��O5�b'�'���c���NW~��MAY&��׹4��f^�l%������a��?ٹS6��,�"AH���ڡ����멓��W�EfBgU�
}[�
R
�̺�>ɧ�n���Ǔ�Ve��q��m�z���#-zd�{W��VG�фXt��u����r�xXC���i��L�N��ױ���#<rNR�3 R�)	���(�0��ģ	��a���g������P4)����1j���H/����ֲ5�\9�J���^Q��.� �`��$k�I����!���j�{�p/`P�o�P�Z��"EG;`vI�W�4|��5��!9xZ{��;W?��X����dS�	8Q2��N<-��$�X�����J�
�u#�d� ���T�m���ޖ#����ӟ��s��OE���R�5K�0��>�oq��[�꾫�m�*�l�T�eZoD�y�eZnF�\�D�17�11򧬘mÆ�WF.�:Ր�#f]aY�"n�Bſ���P���u��-H�'GPf�b�������2��MCl0��ķ?�vO�J@d�����c�a�]�{[��Q?��iW�kGU1	�����H�fƌ��üܲ6�n!D�^>z>�O\�qȫ:�-��h���C��� 
O��q��4����vWN�V}��% џ�51aҡa����\�x>e���x��9D�����Φj�b!Q)�^^�T#����.̜��h�L����Z����n��O�)���&I�#��������T��L](��g���lU Ѷ�d�"�{�8�$"�Aߘ��_3���	��#5#
�}W��J���+
N;}n X�V�[�pЬW`/|{��iqóT��і �$Q2ĩI-�}�j�ܟ5%���(H��j'��O�>��H�-�����"��������6��Gs�O�R�]lf-�s��&�M�ON��䶥�+�D�ۚ�*