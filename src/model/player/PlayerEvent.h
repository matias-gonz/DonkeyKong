#ifndef TALLER_PROG_I_2021_1C_KIWI_PLAYEREVENT_H
#define TALLER_PROG_I_2021_1C_KIWI_PLAYEREVENT_H

enum EventType {
    PlayerJump,
    PlayerWasDamaged,
    PlayerGrabHammer,
    PlayerKilledAnEnemy,
    PlayerClimbedALadder,
    PlayerMutedMusic,
    PlayerMutedSoundEffects,
    PlayerStartedGodMode,
    PlayerWon,
    PlayerLost,
    NoEvent
};

class PlayerEvent {
private:
    EventType type;
    char eventSymbol [11] = {'j', 'd', 'h', 'k', 'c', 'm', 'e','g','w', 'l', 'n'};

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

    void playerStartedGodMode();

    void playermutedSoundEffects();

    void playerDied();

    void playerReachedThePrincess();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLAYEREVENT_H
