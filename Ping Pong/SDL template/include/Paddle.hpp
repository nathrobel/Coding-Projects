#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Paddle{

    private:
        int speed;
        float y_pos;
        SDL_Rect paddle;
        SDL_Scancode up_key;
        SDL_Scancode down_key;
        

    public:
        Paddle();
        Paddle(int x_pos, float y_pos, SDL_Scancode up_key, SDL_Scancode down_key);
        void pollEvents(const Uint8 *state);
        void draw(SDL_Renderer* renderer);
        int getPos();
        int getSpeed();
        void setPos(int newPos);
        bool moveUp(float cpu_speed);
        bool moveDown(float cpu_speed);

};