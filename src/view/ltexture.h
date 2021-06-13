#ifndef TALLER_PROG_I_2021_1C_KIWI_LTEXTURE_H
#define TALLER_PROG_I_2021_1C_KIWI_LTEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

//Texture wrapper class
class LTexture {
public:
  LTexture();

  //Initializes variables
  LTexture(SDL_Renderer *gRenderer);

  LTexture(const LTexture &texture);

  //Deallocates memory
  ~LTexture();

  //Loads image at specified path
  bool loadFromFile(std::string path);

//#if defined(SDL_TTF_MAJOR_VERSION)
  //Creates image from font string
  bool loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer);
//#endif

  //Deallocates texture
  void free();

  //Renders texture at given point
  void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL,
              SDL_RendererFlip flip = SDL_FLIP_NONE);

  void setRenderer(SDL_Renderer *aRenderer);

  int getWidth();

  int getHeight();

private:
  //The actual hardware texture
  SDL_Texture *texture;
  SDL_Renderer *gRenderer;

  //Image dimensions
  int width;
  int height;
};


#endif //TALLER_PROG_I_2021_1C_KIWI_LTEXTURE_H
