#ifndef TALLER_PROG_I_2021_1C_KIWI_PLAYEREVENT_H
#define TALLER_PROG_I_2021_1C_KIWI_PLAYEREVENT_H

enum EventType {
    PlayerJump,
    PlayerWasDamaged,
    PlayerGrabHammer,
    PlayerKilledAnEnemy,
    PlayerClimbedALadder,
    PlayerMutedMusic,
    PlayerWon,
    PlayerLost,
    NoEvent
};

class PlayerEvent {
private:
    EventType type;
    char eventSymbol [9] = {'j', 'd', 'h', 'k', 'c', 'm', 'w', 'l', 'n'};

public:
    PlayerEvent();
    void playerJumped();

    char getEventSymbol();

    char extractEvent();

    void playerGotDamaged();

    void playerGrabbedAHammer();

    void playerKilledAnEnemy();

    void playerClimbedALadder();

    void playerMutedMusic();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLAYEREVENT_H
