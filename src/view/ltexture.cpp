#include "ltexture.h"

LTexture::LTexture() {
  this->gRenderer = NULL;
  this->texture = NULL;
  this->width = 0;
  this->height = 0;
}

LTexture::LTexture(SDL_Renderer *aRenderer) {
  //Initialize
  this->gRenderer = aRenderer;
  this->texture = NULL;
  this->width = 0;
  this->height = 0;
}

LTexture::LTexture(const LTexture &texture) {
  //Initialize
  this->gRenderer = texture.gRenderer;
  this->texture = texture.texture;
  this->width = texture.width;
  this->height = texture.height;
}

LTexture::~LTexture() {
  //Deallocate
  free();
}

void LTexture::free() {
  //Free texture if it exists
  if (texture != NULL) {
    SDL_DestroyTexture(texture);
    texture = NULL;
    width = 0;
    height = 0;
  }
}


bool LTexture::loadFromFile(std::string path) {
  //The final texture
  SDL_Texture *newTexture = NULL;

  //Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface != NULL) {
    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (newTexture == NULL) {
      printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    } else {
      //Get image dimensions
      width = 50;
      height = 50;
    }

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);

  } else {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
  }

  //Return success
  texture = newTexture;
  return texture != NULL;
}

void LTexture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip) {
  //Set rendering space and render to screen
  SDL_Rect renderQuad = {x, y, this->width, this->height};

  //Set clip rendering dimensions
  if (clip != NULL) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  //Render to screen
  SDL_RenderCopy(this->gRenderer, this->texture, clip, &renderQuad);
}

int LTexture::getWidth() {
  return this->width;
}

int LTexture::getHeight() {
  return this->height;
}

void LTexture::setRenderer(SDL_Renderer *aRenderer) {
  this->gRenderer = aRenderer;
}

//#if defined(SDL_TTF_MAJOR_VERSION)
bool
LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font *font, SDL_Renderer *renderer) {
  //Get rid of preexisting texture
  free();
  //Render text surface
  this->gRenderer = renderer;
  SDL_Surface *textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
  if (textSurface != NULL) {
    //Create texture from surface pixels
    this->texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (this->texture == NULL) {
      printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    } else {
      //Get image dimensions
      this->width = textSurface->w;
      this->height = textSurface->h;
    }

    //Get rid of old surface
    SDL_FreeSurface(textSurface);
  }

  //Return success
  return this->texture != NULL;
}
//#endif



