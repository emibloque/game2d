
#include "Game.h"
#include "GameLayer.h"

Game::Game()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "Error SDL_Init" << SDL_GetError() << endl;
	}
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0)
	{
		cout << "Error Window y Renderer" << SDL_GetError() << endl;
	}
	SDL_SetWindowTitle(window, "Juego de Naves");
	// Escalado de imágenes de calidad
	// https://wiki.libsdl.org/SDL_HINT_RENDER_SCALE_QUALITY
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	gameLayer = new GameLayer(this);

	loopActive = true; // bucle activo
	loop();
}

void Game::loop()
{
	int initTick;				// ms de inicio loop
	int endTick;				// ms de fin de loop
	int differenceTick; // fin - inicio
	SDL_Event e;

	while (loopActive)
	{

		initTick = SDL_GetTicks();

		gameLayer->processControls();
		gameLayer->update();
		gameLayer->draw();
		// Actualizar elementos
		// Dibujar

		endTick = SDL_GetTicks();
		differenceTick = endTick - initTick;

		if (differenceTick < (1000 / 30))
		{
			SDL_Delay((1000 / 30) - differenceTick);
		}
	}
}
