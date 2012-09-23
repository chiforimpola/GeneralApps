
import java.lang.String;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.ClipboardOwner;
import java.awt.datatransfer.StringSelection;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.DataFlavor;
import java.awt.Toolkit;

public class StringClipBoard
{

  static String get()
  {
    Transferable t = Toolkit.getDefaultToolkit().getSystemClipboard().getContents(null);
  
    try
    {
      if(t != null && t.isDataFlavorSupported(DataFlavor.stringFlavor))
        return ( (String)t.getTransferData(DataFlavor.stringFlavor) );
    }catch(Exception e)
     {
     }
    return null;
  }
  
  static void set(String str)
  {
    StringSelection ss = new StringSelection(str);
    Toolkit.getDefaultToolkit().getSystemClipboard().setContents(ss, null);
  }

}
