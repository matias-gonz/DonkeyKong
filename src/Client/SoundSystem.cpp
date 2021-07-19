#include "SoundSystem.h"

SoundSystem::SoundSystem() {
  //Initialize the audio config
  SDL_Init(SDL_INIT_AUDIO);
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    std::cout << "Error: " << Mix_GetError() << std::endl;
  }

  bgm = Mix_LoadMUS("resources/sounds/game_music.mp3");
  jumpSoundEffect = Mix_LoadWAV("resources/sounds/jump_sound_effect.wav");
  getHitSoundEffect = Mix_LoadWAV("resources/sounds/player_get_hit_sound_effect.wav");
  grabHammerSoundEffect = Mix_LoadWAV("resources/sounds/grab_hammer_sound_effect.wav");
  killEnemySoundEffect = Mix_LoadWAV("resources/sounds/kill_an_enemy_sound_effect.wav");
  climbLadderSoundEffect = Mix_LoadWAV("resources/sounds/climb_ladder_sound_effect.wav");
}

SoundSystem::~SoundSystem() {
  Mix_FreeMusic(bgm);
  Mix_FreeChunk(jumpSoundEffect);
  Mix_FreeChunk(getHitSoundEffect);
  Mix_FreeChunk(grabHammerSoundEffect);
  Mix_FreeChunk(killEnemySoundEffect);
  Mix_FreeChunk(climbLadderSoundEffect);

  bgm = nullptr;
  jumpSoundEffect = nullptr;
  getHitSoundEffect = nullptr;
  grabHammerSoundEffect = nullptr;
  killEnemySoundEffect = nullptr;
  climbLadderSoundEffect = nullptr;

  Mix_Quit();
}

void SoundSystem::playGameMusic() {
  if (!Mix_PlayingMusic())
    Mix_PlayMusic(bgm, -1);
}

void SoundSystem::reproducePlayerSoundBasedOn(char lastEvent) {
  if (lastEvent == 'j')
      Mix_PlayChannel(-1, jumpSoundEffect, 0);
  if (lastEvent == 'd')
    Mix_PlayChannel(-1, getHitSoundEffect, 0);
  if (lastEvent == 'h')
    Mix_PlayChannel(-1, grabHammerSoundEffect, 0);
  if (lastEvent == 'k')
    Mix_PlayChannel(-1, killEnemySoundEffect, 0);
  if (lastEvent == 'c')
    Mix_PlayChannel(-1, climbLadderSoundEffect, 0);
  if (lastEvent == 'm')
    this->changeMusicReprductionStatus();
}

void SoundSystem::changeMusicReprductionStatus() {
  if (Mix_PausedMusic())
    Mix_ResumeMusic();
  else
    Mix_PauseMusic();
}
