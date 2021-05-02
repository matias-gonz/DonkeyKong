#include <stdio.h>
#include "src/view/background.h"
#include "src/view/ltexture.h"
#include "src/model/barrel.h"

int main( int argc, char* args[] ) {
  Background background;

  background.renderImage();
  background.closeWindow();

  LTexture texturaBarril;
  if( !texturaBarril.loadFromFile("/home/agustin/CLionProjects/Taller-Prog-I-2021-1C-KIWI/resources/sprites/search.png", background.getRenderer()) )
  {
      printf( "Failed to load barrel texture!\n" );
  }
  Barrel barrel;
  barrel.setTexture(texturaBarril);
  barrel.render();


  return 0;
}
