#include "Window.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include <string>

Window::Window(const char* title, int width, int height)
    :window(NULL), renderer(NULL)
{
    // Create the window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if ( window == NULL )
        std::cout << "Error Creating Window: " << SDL_GetError() << std::endl;
    
    // Tell the gameloop the window is open
    isOpen = true;

    // Create the renderer onto the window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if ( renderer == NULL )
        std::cout << "Error Creating Renderer: " << SDL_GetError() << std::endl; 
}

Window::Window(){}

// Polls too see if the user closed the window
void Window::pollEvents(SDL_Event &event)
{
    bool closedWindow = ( event.type == SDL_QUIT );
    bool pressedEscape = ( event.key.keysym.sym == SDLK_ESCAPE );
    if ( closedWindow || pressedEscape )
    {
        isOpen = false;
    }

}

void Window::destroyWindowAndRenderer()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

void Window::clearRenderer()
{
    SDL_RenderClear(renderer);
}

void Window::presentRenderer()
{
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Window::getRenderer()
{
    return renderer;
}

// Draws a black background
void Window::drawBackground()
{
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
}

// Draws the halfway line for the game
void Window::drawHalfwayLine()
{   
    for (int y = 12; y < 400; y=y+50)
    {   
        SDL_Rect dot = { static_cast<int>(300), static_cast<int>(y), 8, 25 };
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 40);
        SDL_RenderFillRect(renderer, &dot);
    }
}

// Draws the scores for the game
void Window::drawScores(TTF_Font* font, int player1Score, int player2Score)
{   
    SDL_Color White = {255, 255, 255};
    std::string scoreString = std::to_string(player1Score) + "  " + std::to_string(player2Score);
    const char* scoreDisplay = scoreString.c_str();
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, scoreDisplay, White); 
    // Better to use Textures to utilise the gpu
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 
    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 245;  //controls the rect's x coordinate 
    Message_rect.y = 10; // controls the rect's y coordinte
    Message_rect.w = 120; // controls the width of the rect
    Message_rect.h = 35; // controls the height of the rect

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    // Don't forget to free your surface and texture
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}