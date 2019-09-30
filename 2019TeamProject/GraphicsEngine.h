#pragma once
#include <memory>
#include <SDL.h>
#include "Enemy.h"
#include "Player.h"
#include "SpriteManager.h"

class GraphicsEngine
{
private:
	SDL_Renderer* mRenderer = nullptr;

	std::unique_ptr<SpriteManager> mSpriteManager = nullptr;
	std::unique_ptr<Enemy> mEnemy = nullptr;
	std::unique_ptr<Player> mPlayer = nullptr;

	RenderConfig mBackgroundPosition1 = { 0, 0, 1280.0f / 1920.0f, 768.0f / 1080.0f };
	RenderConfig mBackgroundPosition2 = { 1280, 0, 1280.0f / 1920.0f, 768.0f / 1080.0f };
	int mBackgroundMoveSpeed = 128;
	
	void UpdateBackground();
	void UpdatePlayer();

public:
	GraphicsEngine(SDL_Window* window);
	~GraphicsEngine();

	void ClearColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xFF);
	void Render();
};

