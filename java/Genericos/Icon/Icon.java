

import java.awt.image.BufferedImage;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.imageio.ImageIO;;

public class Icon
{
  static void setIcon(JFrame frame, String path)
  {
    BufferedImage image = null;
    
    try
    {
      image = ImageIO.read(frame.getClass().getResource(path));
    } catch (Exception e)
      {
        e.printStackTrace();
      }
    frame.setIconImage(image);
  }
}
