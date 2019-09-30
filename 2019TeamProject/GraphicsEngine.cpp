#include "GraphicsEngine.h"
#include <chrono>
#include <SDL_image.h>
#include <cassert>
#include "Helper.h"

using namespace std::chrono;

void GraphicsEngine::UpdateBackground()
{
	static auto start_time = high_resolution_clock::now();
	auto current_time = high_resolution_clock::now();
	auto elapsed = duration<float, seconds::period>(current_time - start_time).count();

	if (elapsed > 1.0f) {
		mBackgroundPosition1.xPos -= mBackgroundMoveSpeed;
		mBackgroundPosition2.xPos -= mBackgroundMoveSpeed;
		start_time = current_time;
	}

	if (mBackgroundPosition1.xPos <= -1280) mBackgroundPosition1.xPos = 1280;
	if (mBackgroundPosition2.xPos <= -1280) mBackgroundPosition2.xPos = 1280;
}

GraphicsEngine::GraphicsEngine(SDL_Window* window)
{
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	mSpriteManager = std::make_unique<SpriteManager>();

	mSpriteManager->LoadStaticSprite("texture/bg.png", mRenderer);
	mEnemy = std::make_unique<Enemy>("texture/boss.png", mRenderer, 0, 0,
		"texture/bullet.png", 0, 0);
	mPlayer = std::make_unique<Player>("texture/player.png", mRenderer, 0, 0, 64, 512);
	
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
}

GraphicsEngine::~GraphicsEngine()
{
	mEnemy.reset();
	mSpriteManager.reset();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
}

void GraphicsEngine::ClearColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	assert(mRenderer);

	ThrowIfFailed(SDL_SetRenderDrawColor(mRenderer, r, g, b, a),
		"SDL failed to set the render color.\n");
	
	ThrowIfFailed(SDL_RenderClear(mRenderer), "SDL failed to clear the renderer.\n");
}

void GraphicsEngine::Render()
{
	try
	{
		assert(mRenderer);

		UpdateBackground();

		mSpriteManager->RenderStaticSprite(mRenderer, 0,
			mBackgroundPosition1);
		mSpriteManager->RenderStaticSprite(mRenderer, 0,
			mBackgroundPosition2);

		mEnemy->Update(mRenderer, { 640, 256, 1.0f, 1.0f });
		auto player_collision_box = mPlayer->GetCollisionBox();

		mEnemy->CheckCollisions(player_collision_box);

		auto key_states = SDL_GetKeyboardState(nullptr);
		mPlayer->Update(key_states[SDL_SCANCODE_SPACE]);

		mPlayer->Render(mRenderer);

		SDL_RenderPresent(mRenderer);
	}
	catch (const std::exception&)
	{
		throw;
	}
}
