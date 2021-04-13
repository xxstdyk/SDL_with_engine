#ifndef ENGINE_H_
#define ENGINE_H_

#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#define FPS 60
#define WIDTH 1024
#define HEIGHT 768

class Engine {

	bool m_running = false;
	
	Uint32 m_start, m_end, m_delta, m_fps;
	
	const Uint8* m_keystates;
	
	SDL_Window* m_pWindow;

	SDL_Renderer* m_pRenderer;

	int Init(const char* _title, int _xPos, int _yPos, int _width, int _height, int _flags);
	void InitSprites();
	void Wake();
	void HandleEvents();
	bool KeyDown(SDL_Scancode);
	void Update();
	void Render();
	void Sleep();
	void Clean();

	public:
	int Run();
};

#endif
