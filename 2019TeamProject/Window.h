#pragma once
#include <memory>
#include <string>
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include "SceneManager.h"

class Window
{
private:
	SDL_Window* mWindow = nullptr;
	SDL_Surface* mSurface = nullptr;
	SDL_Event mEvent = {};
	bool mIsInit = false;

	std::unique_ptr<SceneManager> mSceneManager = nullptr;

public:
	Window() = default;
	~Window();

	void Initialize(const std::string& title, int width, int height);
	void Broadcast();

	bool IsInit() const noexcept;
};

