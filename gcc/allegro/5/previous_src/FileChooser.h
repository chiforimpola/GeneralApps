

#ifndef FILE_CHOOSER_H
#define FILE_CHOOSER_H

#define FILE_CHOOSER_DEFAULT_PATH     "C:\\"

/*
  Permite a escolha de arquivos com interface provida
    pelo S.O
*/

class FileChooser
{
  private:
    ALLEGRO_FILECHOOSER    *fc;
  public:

    void Create(char *path, char *title)
    {
      fc = al_create_native_file_dialog(
        path, 
        title, 
        NULL, 
        ALLEGRO_FILECHOOSER_FILE_MUST_EXIST);
    }
    
    void Show(ALLEGRO_DISPLAY *display)
    {
      if(fc != NULL) al_show_native_file_dialog(display, fc);
    }
    
    void Destroy()
    {
      if(fc != NULL) al_destroy_native_file_dialog(fc);
    }
    char *getPath()
    {
      char *aux = (char *)malloc(strlen(al_get_native_file_dialog_path(fc, 0) + 1));
      strcpy(aux, al_get_native_file_dialog_path(fc, 0));
      return (aux);
    }
    
    FileChooser(char *title)
    {
      Create(FILE_CHOOSER_DEFAULT_PATH, title);
    }
    
    FileChooser(char *path, char *title)
    {
      Create(path, title);
    }
};


#endif
