#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// A wrapper for SDL_Window and SDL_Renderer, contains generic methods to do with managing the renderer and window
// Drawing objects to the window should be done in a class like GameScreen
class Window{
    
    private:
        SDL_Renderer* renderer;
        SDL_Window* window;
        TTF_Font* font;
        
    public:
        bool isOpen;
        Window();
        // TODO need to make fullscreen an option, and pass width and height everywhere that uses it 
        Window(const char* title, int width, int height);
        void pollEvents(SDL_Event &event);
        void destroyWindowAndRenderer();
        void clearRenderer();
        void presentRenderer();
        void initFont();
        SDL_Window* getWindow();
        SDL_Renderer* getRenderer();
        TTF_Font* getFont();
        void drawBackground();
        void drawHalfwayLine();
        void drawScores(TTF_Font* font, int player1Score, int player2Score);

};