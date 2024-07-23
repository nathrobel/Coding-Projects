#pragma once 

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

class AudioManager{ 
    private:
        Mix_Chunk* sound;
        Mix_Music* music;

    public:
        AudioManager();
        // Imperfect solution, but only need to play one sound effect and music at a time
        // could be a static class
        void loadSound(const char* filePath);
        void loadMusic(const char* filePath);
        void playSound();
        void playMusic();
        void freeSound();
        void freeMusic();
};