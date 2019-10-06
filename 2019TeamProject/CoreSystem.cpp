#include "CoreSystem.h"
#include <chrono>
#ifdef _WIN32
#include <SDL_image.h>
#else
#include <SDL_image/SDL_image.h>
#endif
#include <cassert>

using namespace std::chrono;

void CoreSystem::UpdateBackground()
{
	static auto start_time = high_resolution_clock::now();
	auto current_time = high_resolution_clock::now();
	auto elapsed = duration<float, seconds::period>(current_time - start_time).count();

	if (elapsed > 1.0f) {
		mBackgroundPosition1.xPos -= mBackgroundMoveSpeed;
		mBackgroundPosition2.xPos -= mBackgroundMoveSpeed;
		start_time = current_time;
	}

	if (mBackgroundPosition1.xPos <= -(WINDOW_WIDTH * 2))
		mBackgroundPosition1.xPos = WINDOW_WIDTH;
	if (mBackgroundPosition2.xPos <= -(WINDOW_WIDTH * 2))
		mBackgroundPosition2.xPos = WINDOW_WIDTH;
}

void CoreSystem::UpdatePlayer()
{
	static auto start_time = high_resolution_clock::now();
	auto current_time = high_resolution_clock::now();
	auto elapsed = duration<float, seconds::period>(current_time - start_time).count();

	auto key_states = SDL_GetKeyboardState(nullptr);
	auto res = mEnemy->CheckCollisions(mPlayer->GetCollisionBox());
	
	if (key_states[SDL_SCANCODE_SPACE]) {
		if (res) mBackgroundMoveSpeed *= 1;
		else mBackgroundMoveSpeed = 0;
	}
	else {
		mBackgroundMoveSpeed = (WINDOW_WIDTH / 10) * 1;
	}
}

CoreSystem::CoreSystem(SDL_Window* window, const SDL_Rect& viewport) : mViewport(viewport)
{
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	mSpriteManager = std::make_unique<SpriteManager>();

	mSpriteManager->LoadStaticSprite("texture/background_resized.png", mRenderer);
	mSpriteManager->LoadStaticSprite("texture/sample_clock.png", mRenderer);
	mSpriteManager->LoadStaticSprite("texture/sample_indicator.png", mRenderer);
	mSpriteManager->LoadStaticSprite("texture/floor.png", mRenderer);
	
	mEnemy = std::make_unique<Enemy>("texture/boss1.png", mRenderer, 0, 0,
		"texture/bullet.png", 0, 0);
	mPlayer = std::make_unique<Player>("texture/sample_player.png", mRenderer, 0, 0, 64, WINDOW_HEIGHT * 0.75f);
	
	mMixer = std::make_unique<Mixer>();
}

CoreSystem::~CoreSystem()
{
	mEnemy.reset();
	mSpriteManager.reset();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
}

void CoreSystem::ClearColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	assert(mRenderer);

	ThrowIfFailed(SDL_SetRenderDrawColor(mRenderer, r, g, b, a),
		"SDL failed to set the render color.\n");
	
	ThrowIfFailed(SDL_RenderClear(mRenderer), "SDL failed to clear the renderer.\n");
}

void CoreSystem::Render()
{
	static auto start_time = high_resolution_clock::now();
	static auto angle = 6.0;
	static auto game_time = 0.0;
	auto current_time = high_resolution_clock::now();
	auto elapsed = duration<float, seconds::period>(current_time - start_time).count();
	

	try
	{
		assert(mRenderer);

		mSpriteManager->RenderStaticSprite(mRenderer,
			static_cast<int>(StaticSpriteList::Background),
			{ 0, 0, SCALE_SIZE, SCALE_SIZE });
		mSpriteManager->RenderStaticSprite(mRenderer,
			static_cast<int>(StaticSpriteList::Floor),
			mBackgroundPosition1);
		mSpriteManager->RenderStaticSprite(mRenderer,
			static_cast<int>(StaticSpriteList::Floor),
			mBackgroundPosition2);
		mSpriteManager->RenderStaticSprite(mRenderer,
			static_cast<int>(StaticSpriteList::Clock),
			{ 64, static_cast<int>(WINDOW_WIDTH * 0.05f), 1.0f, 1.0f });

		if (elapsed >= 1.0f) {
			angle += 6.0;
			start_time = current_time;
			game_time += elapsed;
		}

		mSpriteManager->RenderStaticSprite(mRenderer,
			static_cast<int>(StaticSpriteList::Indicator),
			{ 64, static_cast<int>(WINDOW_WIDTH * 0.05f), 1.0f, 1.0f }, angle);

		mEnemy->Update(mRenderer,
			{ static_cast<int>(mViewport.w * 0.6f),
			static_cast<int>(mViewport.h * 0.25f), SCALE_SIZE, SCALE_SIZE });
		
		UpdatePlayer();
		UpdateBackground();
		mPlayer->Render(mRenderer);

		SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0xFF, 0xFF);
		SDL_RenderDrawRect(mRenderer, &(mPlayer->GetCollisionBox()));
		SDL_RenderPresent(mRenderer);
	}
	catch (const std::exception&)
	{
		throw;
	}
}
