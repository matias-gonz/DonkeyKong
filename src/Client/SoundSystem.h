#ifndef TALLER_PROG_I_2021_1C_KIWI_SOUNDSYSTEM_H
#define TALLER_PROG_I_2021_1C_KIWI_SOUNDSYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
class SoundSystem {
public:
    SoundSystem();

    ~SoundSystem();

    void playGameMusic();

    void reproducePlayerSoundBasedOn(char lastEvent);

private:
    Mix_Music *bgm ;
    Mix_Chunk *jumpSoundEffect ;
    Mix_Chunk *getHitSoundEffect ;
    Mix_Chunk *grabHammerSoundEffect ;
    Mix_Chunk *killEnemySoundEffect ;
    Mix_Chunk *climbLadderSoundEffect ;
    Mix_Chunk *startGodModeSoundEffect ;
    Mix_Chunk *reachThePrincessSoundEffect ;
    Mix_Chunk *playerDieSoundEffect ;


    void changeMusicReprductionStatus();

    void manageSoundSystemWith(char i);

    bool soundEffectsActive;

    void reproduceSoundEffectBasedOn(char event);

    void changeSoundEffectReprductionStatus();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_SOUNDSYSTEM_H
