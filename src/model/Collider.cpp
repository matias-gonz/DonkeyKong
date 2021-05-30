#include "Collider.h"

bool Collider::RectCollides(SDL_Rect r1, SDL_Rect r2) {
    //printf("%i,%i,%i,%i\n%i,%i,%i,%i\n\n",r1.x,r1.y,r1.w,r1.h,r2.x,r2.y,r2.w,r2.h);
    return( (r1.x < r2.x + r2.w) && (r1.x + r1.w > r2.x) &&
            (r1.y < r2.y + r2.h) && (r1.y + r1.h > r2.y));
}

void Collider::ResolvePlayerCollision(Player *Player, SDL_Rect rect) {
    SDL_Rect playerRect = Player->getRectangle();
    int dy;

    if(playerRect.y + playerRect.h - 10 < rect.y ){
        dy = playerRect.y + playerRect.h - rect.y;
        Player->moveUp(dy);
        Player->resetVelY();
        Player->setGrounded();
    }else if(playerRect.y + playerRect.h < rect.y){
        //dy = rect.y + rect.h - playerRect.y;
        //player->moveDown(dy);
        //player->resetVelY();
    }

}


