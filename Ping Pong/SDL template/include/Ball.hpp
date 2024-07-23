#pragma once 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Ball{

    private:
        float x_velocity;
        float y_velocity;
        float x_pos;
        float y_pos;
        SDL_Rect ball;

    public:
        Ball();
        Ball(int start_x, int start_y);
        void draw(SDL_Renderer* renderer);
        bool checkFloorOrCeilingCollision();
        bool checkPaddleCollision(int paddle1_y, int paddle2_y, int paddle1_vel, int paddle2_vel);
        void calcNewXSpeed(int paddle_pos);
        float calcNewYSpeed(int paddle_vel);
        int checkIfPlayerScored();
        void resetRound();
        float getYPos();

};
