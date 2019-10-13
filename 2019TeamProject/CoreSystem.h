#pragma once
#include <memory>
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include "Enemy.h"
#include "Helper.h"
#include "Mixer.h"
#include "Player.h"
#include "SpriteManager.h"

class CoreSystem
{
private:
	SDL_Renderer* mRenderer = nullptr;

	std::unique_ptr<SpriteManager> mSpriteManager = nullptr;
	std::unique_ptr<Enemy> mEnemy = nullptr;
	std::unique_ptr<Player> mPlayer = nullptr;
	std::unique_ptr<Mixer> mMixer = nullptr;

	RenderConfig mBackgroundPosition1 = { 0, WINDOW_HEIGHT - 248, SCALE_SIZE, SCALE_SIZE };
	RenderConfig mBackgroundPosition2 = { WINDOW_WIDTH * 2, WINDOW_HEIGHT - 248, SCALE_SIZE, SCALE_SIZE };

    
	int mBackgroundMoveSpeed = WINDOW_WIDTH / 10;




































































































































































	SDL_Rect mViewport = {};
	
	void UpdateBackground();
	void UpdatePlayer();

	enum class StaticSpriteList {
		Background,
		Clock,
		Indicator,
		Floor
	};

public:
	CoreSystem(SDL_Window* window, const SDL_Rect& viewport);
	~CoreSystem();

	void ClearColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xFF);
	void Render();
};

