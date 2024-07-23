#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "Window.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "GameEngine.hpp"

int main(int argc, char *argv[])
{
	GameEngine gameEngine = GameEngine();
	gameEngine.initSDL();

	// Gameplay loop
	while (gameEngine.isRunning())
	{

		switch (gameEngine.gameState)
		{
		case 0: // Start-menu state

			// get inputs
			gameEngine.handleStartInputs();
			// update objects
			// Render frame
			gameEngine.RenderNewStartFrame();

			break;

		case 1: // Gameplay state

			gameEngine.handleGameInputs();
			gameEngine.checkAllCollisions();
			gameEngine.RenderNewGameFrame();

			break;

		case 2: // Game over state

			gameEngine.handleEndInputs();
			gameEngine.RenderNewEndFrame();
			break;
		}
		// delta time
		// --- TODO ----
		// Delay
		SDL_Delay(5);
		// Present Renderer & clear for next
		gameEngine.presentRenderer();
	}

	gameEngine.closeAll();

	return 0;
}