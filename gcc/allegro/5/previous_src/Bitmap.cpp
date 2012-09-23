#ifndef BITMAP_CPP
#define BITMAP_CPP

int Bitmap :: getH(){ return (al_get_bitmap_height(sprite)); }

int Bitmap :: getW(){ return (al_get_bitmap_width(sprite)); }

bool Bitmap :: open(char *path2, ALLEGRO_COLOR col)
{
  if( !IS_IMAGE_ADDON_INSTALLED )
  {
    al_init_image_addon();
    IS_IMAGE_ADDON_INSTALLED = true;
  }
  
  path = (char *)malloc(StringLengh(path2) + 1);
  strcpy(path, path2);
  
  sprite = al_load_bitmap(path);
  if(sprite == NULL)
    return (false);
  al_convert_mask_to_alpha(sprite, col);
  init = true;
  return (true);
}



void Bitmap :: print(int x, int y, int flag)
{
  if(sprite != NULL)
    al_draw_bitmap(sprite, x, y, flag);
}


void Bitmap :: resize(long int resizeW, long int resizeH)
{
  if(sprite != NULL)
  {
    ALLEGRO_BITMAP *aux = al_create_bitmap(resizeW, resizeH);
    
    al_set_target_bitmap(aux);
    al_draw_scaled_bitmap(sprite,
                          0, 0, getW(), getH(),
                          0, 0, resizeW, resizeH,
                          0);
    al_set_target_bitmap(al_get_backbuffer(display));
    
    al_destroy_bitmap(sprite);
    sprite = al_create_bitmap(resizeW, resizeH);
    al_set_target_bitmap(sprite);
    al_draw_bitmap(aux, 0, 0, 0);
    al_set_target_bitmap(al_get_backbuffer(display));
  }

}


ALLEGRO_BITMAP* Bitmap :: getImageResized(long int resizeW, long int resizeH)
{
  if(sprite != NULL)
  {
    ALLEGRO_BITMAP *aux = sprite;
    
    al_set_target_bitmap(aux);
    al_draw_scaled_bitmap(sprite,
                          0, 0, getW(), getH(),
                          0, 0, resizeW, resizeH,
                          0);
    al_set_target_bitmap(al_get_backbuffer(display));
    return (aux);
  }

}



void Bitmap :: printRegion(int x_ini, int y_ini, int x2, int y2, int x, int y, int flag)
{
  if(sprite != NULL)
    al_draw_bitmap_region(
      sprite,
      x_ini, y_ini,
      x2, y2, 
      x, y, 
      flag);
}

/*******************
  Util para printar
    cenarios
  Expande a imagem para 
  caber totalmente na
  tela
*******************/
void Bitmap :: printFullScreen(int flag)
{
  if(sprite != NULL)
    al_draw_scaled_bitmap(sprite, 0, 0, getW(), getH(), 0, 0, SCREEN_W, SCREEN_H, flag);
}


/*******************
  Expande ou a altura
  ou a largura, dependendo
  do parametro
*******************/
void Bitmap :: printFullScreen(int x, int y, int flag)
{
  if(sprite != NULL)
  {
    switch(flag)
    {
      case 0:
        al_draw_scaled_bitmap(sprite, 0, 0, getW(), SCREEN_H, x, y, SCREEN_W, SCREEN_H, 0);
        break;
      case 1:
        al_draw_scaled_bitmap(sprite, 0, 0, SCREEN_W, getH(), x, y, SCREEN_W, SCREEN_H, 0);
        break;
      case 2:
        al_draw_scaled_bitmap(sprite, 0, 0, getW(), getH(), x, y, SCREEN_W, SCREEN_H, 0);
        break;
    }
  }
}

#endif
