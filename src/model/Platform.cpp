#include "Platform.h"
#include "../view/TextureManager.h"

Platform::Platform(Position position, int count) {
    this->pos = position;
    this->count = count;
}

void Platform::draw(SDL_Texture *texture) {
    TextureManager::DrawTexture(texture,NULL,NULL);
}

