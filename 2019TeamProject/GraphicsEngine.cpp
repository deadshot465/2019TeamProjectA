#include "GraphicsEngine.h"
#include <SDL_image.h>
#include <cassert>
#include "Helper.h"

GraphicsEngine::GraphicsEngine(SDL_Window* window)
{
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	mSpriteManager = std::make_unique<SpriteManager>();

	mSpriteManager->LoadStaticSprite("texture/bg.png", mRenderer);
	mEnemy = std::make_unique<Enemy>("texture/boss.png", mRenderer, 0, 0,
		"texture/bullet.png", 0, 0);
	
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

		mSpriteManager->RenderStaticSprite(mRenderer, 0,
			{ 0, 0, 1024.0f / 1920.0f, 768.0f / 1080.0f });

		mEnemy->Update(mRenderer, { 512, 256, 1.0f, 1.0f });

		SDL_RenderPresent(mRenderer);
	}
	catch (const std::exception&)
	{
		throw;
	}
}
