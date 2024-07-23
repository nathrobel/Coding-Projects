#include "Ball.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cmath>

Ball::Ball(int start_x, int start_y)
{   
    // Setting the initial position of the ball
    x_pos = start_y;
    y_pos = start_x;
    // Size of the ball
    ball.w = ball.h = 10;
    // Start velocitiy of the ball
    x_velocity = 1.0;
    y_velocity = 0.6;

}

Ball::Ball(){}

void Ball::draw(SDL_Renderer* renderer)
{
    // Move according to the current velocities
    x_pos += x_velocity;
    y_pos += y_velocity;
    
    // Setting the position of the ball like this and not setting ball.x allows 
    // Ball to move by decimal amounts, but is only visually moves when x_pos or y_pos 
    // changes by a whole number (ie at least one pixel)
    SDL_Rect ball = { static_cast<int>(x_pos), static_cast<int>(y_pos), 10, 10 };
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &ball);
}

bool Ball::checkFloorOrCeilingCollision()
{
    if ( y_pos > 400 - ball.h || y_pos < 0)
    {
        y_velocity *= -1;
        return true;
    }

    return false;
}

bool Ball::checkPaddleCollision(int paddle1_y, int paddle2_y, int paddle1_vel, int paddle2_vel)
{
    bool ballPaddle1SameX = x_pos < 10;
    bool ballPaddle2SameX = x_pos > 590 - ball.w;
    bool ballPaddle1SameY = paddle1_y < y_pos && y_pos < paddle1_y + 100;
    bool ballPaddle2SameY = paddle2_y < y_pos && y_pos < paddle2_y + 100;

    if (( ballPaddle1SameX && ballPaddle1SameY ))
    {   
        calcNewXSpeed(paddle1_y);
        x_pos = 10; // Reset to paddle surface
        y_velocity = calcNewYSpeed(paddle1_vel);
        return true;
    } else if ( ballPaddle2SameX && ballPaddle2SameY )
    {
        calcNewXSpeed(paddle2_y);
        x_pos = 590 - ball.w;
        y_velocity = calcNewYSpeed(paddle2_vel);
        return true;
    }
    return false;
}

// Returns the player number that scored, or 0 if no-one scored
int Ball::checkIfPlayerScored()
{
    bool ballInPlayer1Area = x_pos < 0;
    bool ballInPlayer2Area = x_pos > 600 - ball.w;

    if ( ballInPlayer1Area )
        return 2;
    else if ( ballInPlayer2Area )
        return 1;
    
    return 0;
}

void Ball::resetRound()
{
    x_pos = 290;
    y_pos = 210;

    // Reset the ball speed and set direction so losing player gets first hit 
    x_velocity = ( x_velocity / std::fabs(x_velocity));
    y_velocity = 1; // TODO make this a random value between -1.5 and 1.5


}

// Increase the x_velocity if the ball hits closer to the middle of the paddle
// Decrease the velocity if hits the edges 
void Ball::calcNewXSpeed(int paddle_pos)
{   
    double x_multiplier;
    const float MAX_SPEED = 2.5;
    const float MIN_SPEED = 0.8;
    // The point the ball hit the paddle relative to the paddle 
    float relative_y =  -1 * (y_pos - paddle_pos);

    // curve : x = -1/2800 * (y)(y+100) + 0.4
    x_multiplier = -1.0/2800.0 * (relative_y) * (relative_y+100) + 0.33;
    x_velocity *= -1 * x_multiplier;

    if ( std::fabs(x_velocity) < MIN_SPEED )
    {
        // Correct direction of new velocity
        if ( x_velocity < 0)
            x_velocity = -MIN_SPEED;
        else
            x_velocity = MIN_SPEED;
    } else if ( std::fabs(x_velocity) > MAX_SPEED )
    {
        //  Correct direction of new velocity
        if ( x_velocity < 0)
            x_velocity = -MAX_SPEED;
        else
            x_velocity = MAX_SPEED;
    }
}

// Give the Ball a new y_velocity randomly, but in the direction of the paddles last movement
// in order to give the feeling of the paddle being 'grippy'
float Ball::calcNewYSpeed(int paddle_vel)
{   
    // TODO check this is actually randomising
    double randNum; 
    randNum = rand() % 70 + 50; // Generate random int between 50-120
    randNum /= 100; // Convert to single digit number 

    if ( paddle_vel < 0 )
        return randNum * -1;
    
    return randNum;

}

float Ball::getYPos()
{
    return y_pos;
}