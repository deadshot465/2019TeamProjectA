#pragma once
#include <memory>
#include <SDL.h>
#include <string>
#include "GraphicsEngine.h"

class Window
{
private:
	SDL_Window* mWindow = nullptr;
	SDL_Surface* mSurface = nullptr;
	SDL_Event mEvent = {};
	bool mIsInit = false;

	std::unique_ptr<GraphicsEngine> mGraphicsEngine = nullptr;

public:
	Window() = default;
	~Window();

	void Initialize(const std::string& title, int width, int height);
	void Broadcast();

	bool IsInit() const noexcept;
};

