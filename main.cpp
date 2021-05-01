#include <stdio.h>
#include "src/view/background.h"

int main( int argc, char* args[] ) {
  Background background;

  background.renderImage();
  background.closeWindow();

  return 0;
}
