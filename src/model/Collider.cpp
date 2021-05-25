#include "Collider.h"

bool Collider::RectCollides(SDL_Rect r1, SDL_Rect r2) {
    //printf("%i,%i,%i,%i\n%i,%i,%i,%i\n\n",r1.x,r1.y,r1.w,r1.h,r2.x,r2.y,r2.w,r2.h);
    return( (r1.x < r2.x + r2.w) && (r1.x + r1.w > r2.x) &&
            (r1.y < r2.y + r2.h) && (r1.y + r1.h > r2.y));
}

void Collider::ResolveCollision(Player *player, SDL_Rect rect) {
    SDL_Rect playerRect = player->getRectangle();
    int dy = playerRect.y + playerRect.h - rect.y;

    player->moveUp(dy);
    player->setGrounded();
}


