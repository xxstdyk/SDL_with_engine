#include "Engine.h"

int Engine::Init(const char* _title, int _xPos, int _yPos, int _width, int _height, int _flags) {

	std::cout << "Starting initialization" << std::endl;

	// Check for Init fail
	if (!SDL_Init(SDL_INIT_EVERYTHING)) {

		// Create window
		m_pWindow = SDL_CreateWindow(_title, _xPos, _yPos, _width, _height, _flags);

		// Check for window fail
		if (m_pWindow != nullptr) {

			// Create renderer
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, NULL);

			// Check for renderer fail
			if (m_pRenderer != nullptr) {

				// Check for img initialization fail
				if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0) {
					
					InitSprites();
				} else return false;
			} else return false;
		} else return false;
	} else return false;

	// Convert FPS into ms
	m_fps = (Uint32)round(1 / (double)FPS * 1000);

	// Get keyboard state
	m_keystates = SDL_GetKeyboardState(nullptr);

	// Set gamestate to true
	m_running = true;

	std::cout << "Initialization successful" << std::endl;

	return true;
}

void Engine::InitSprites() {


}

// Sets class member variable m_start to the amount of ticks at the beginning of a frame
void Engine::Wake() {

	m_start = SDL_GetTicks();
}

// Catch-all function to handle events
void Engine::HandleEvents() {

	SDL_Event event;

	while (SDL_PollEvent(&event)) {

		switch (event.type) {

			case SDL_QUIT:
				m_running = false;
				break;
		}
	}
}

bool Engine::KeyDown(SDL_Scancode sc) {

	return static_cast<bool>(m_keystates[sc] == 1);
}

void Engine::Update() {

}

// Draws everything to the renderer
void Engine::Render() {

	// Sets Render Colour
	SDL_SetRenderDrawColor(m_pRenderer, 0xFA, 0xC5, 0xB1, 0xFF);

	// Fills Screen with Render Colour
	SDL_RenderClear(m_pRenderer);

	//SDL_RenderCopy(m_pRenderer, m_pTexture, &m_player.m_source, &m_player.m_destination);

	// Sends Render to Window
	SDL_RenderPresent(m_pRenderer);
}

// Called after renderer is finished, waits for the remaining time left in a frame after all processing is done so fps is smooth
void Engine::Sleep() {

	m_end = SDL_GetTicks();
	m_delta = m_end - m_start;

	if (m_delta < m_fps) {
		SDL_Delay(m_fps - m_delta);
	}
}

// Destroys everything 
void Engine::Clean() {

	std::cout << "Cleaning." << std::endl;

	// Destroying Window and Renderer
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);

	//Destroy Textures
	//SDL_DestroyTexture(m_pTexture);

	// Exiting program
	IMG_Quit();
	SDL_Quit();
}

// Main loop
int Engine::Run() {

	if (m_running) {

		return 1;
	} else {

		if (!Init("GAME1007 LE4", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, NULL))
			return 2;

		while (m_running) {

			Wake();
			HandleEvents();
			Update();
			Render();
			if (m_running)
				Sleep();
		}

		Clean();
		return 0;
	}
}