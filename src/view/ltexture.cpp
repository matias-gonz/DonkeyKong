#include "ltexture.h"

LTexture::LTexture() {
    this-> gRenderer = NULL;
    this-> texture = NULL;
    this-> width = 0;
    this-> height = 0;
}

LTexture::LTexture( SDL_Renderer* aRenderer)
{
    //Initialize
    this-> gRenderer = aRenderer;
    this-> texture = NULL;
    this-> width = 0;
    this-> height = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

void LTexture::free()
{
    //Free texture if it exists
    if(texture != NULL )
    {
        SDL_DestroyTexture(texture );
        texture = NULL;
        width = 0;
        height = 0;
    }
}


bool LTexture::loadFromFile( std::string path)
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            width = 50;
            height = 50;
            //Get image dimensions
            //width = loadedSurface->w;
            //height = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    texture = newTexture;
    return texture != NULL;
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture rgb
    SDL_SetTextureColorMod(texture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode(texture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod(texture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, this->width, this->height };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(this->gRenderer, this->texture, clip, &renderQuad, angle, center, flip );
}

void LTexture::setRenderer(SDL_Renderer *aRenderer) {
    this->gRenderer = aRenderer;
}



int LTexture::getWidth()
{
    return width;
}

int LTexture::getHeight()
{
    return height;
}