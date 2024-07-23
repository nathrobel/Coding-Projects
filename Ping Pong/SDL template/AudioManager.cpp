#include "AudioManager.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>

AudioManager::AudioManager()
{
    if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0 )
        std::cout << "Error Opening audio device: " << Mix_GetError() << std::endl;
}

void AudioManager::loadSound(const char* filePath)
{
    sound = Mix_LoadWAV(filePath);
    if ( sound == NULL )
        std::cout << "Error loading sound from filePath" << Mix_GetError() << std::endl;
}

void AudioManager::playSound()
{
    Mix_PlayChannel(-1, sound, 0);
}

void AudioManager::freeSound()
{
    Mix_FreeChunk(sound);
}

void AudioManager::loadMusic(const char* filePath)
{
    music = Mix_LoadMUS(filePath);
}