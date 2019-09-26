#pragma once
#include <memory>
#include <SDL.h>
#include "Enemy.h"
#include "SpriteManager.h"

class GraphicsEngine
{
private:
	SDL_Renderer* mRenderer = nullptr;

	std::unique_ptr<SpriteManager> mSpriteManager = nullptr;
	std::unique_ptr<Enemy> mEnemy = nullptr;

public:
	GraphicsEngine(SDL_Window* window);
	~GraphicsEngine();

	void ClearColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xFF);
	void Render();
};

