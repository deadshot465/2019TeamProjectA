#include "CoreSystem.h"
#include <chrono>
#include <SDL_image.h>
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

	if (mBackgroundPosition1.xPos <= -WINDOW_WIDTH)
		mBackgroundPosition1.xPos = WINDOW_WIDTH;
	if (mBackgroundPosition2.xPos <= -WINDOW_WIDTH)
		mBackgroundPosition2.xPos = WINDOW_WIDTH;
}

void CoreSystem::UpdatePlayer()
{
	static auto start_time = high_resolution_clock::now();
	static auto acceleration_start_time = high_resolution_clock::now();
	static bool accelerated = false;
	static auto stored_result = CollisionResult::None;

	auto current_time = high_resolution_clock::now();
	auto acceleration_current_time = high_resolution_clock::now();
	auto elapsed = duration<float, seconds::period>(current_time - start_time).count();
	auto acceleration_elapsed =
		duration<float, seconds::period>(acceleration_current_time - acceleration_start_time).count();

	if (elapsed > 0.5f) {
		
		if (!accelerated) {
			auto key_states = SDL_GetKeyboardState(nullptr);
			auto res = CollisionResult();

			if (key_states[SDL_SCANCODE_SPACE] && !accelerated) {
				auto player_collision_box = mPlayer->GetCollisionBox();
				res = mEnemy->CheckCollisions(player_collision_box);
				mPlayer->UpdateSpeed(res);

				if (res != CollisionResult::None) {
					accelerated = true;
					acceleration_start_time = acceleration_current_time;
					
					if (res == CollisionResult::Guard) {
						mBackgroundMoveSpeed = 0;
					}
					else {
						mBackgroundMoveSpeed *= 3;
					}

					mPlayer->Update(acceleration_start_time);
					return;
				}
			}
			mPlayer->Update(time_point<steady_clock>());
		}
		else {
			if (acceleration_elapsed > 2.0f) {
				accelerated = false;
				mBackgroundMoveSpeed = WINDOW_WIDTH / 10;
			}
			mPlayer->Update(time_point<steady_clock>());
		}
		
		start_time = current_time;
	}
}

CoreSystem::CoreSystem(SDL_Window* window, const SDL_Rect& viewport) : mViewport(viewport)
{
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	mSpriteManager = std::make_unique<SpriteManager>();

	mSpriteManager->LoadStaticSprite("texture/sample_bg.png", mRenderer);
	mEnemy = std::make_unique<Enemy>("texture/sample_boss.png", mRenderer, 0, 0,
		"texture/sample_bullet.png", 0, 0);
	mPlayer = std::make_unique<Player>("texture/sample_player.png", mRenderer, 0, 0, 64, WINDOW_HEIGHT * 0.75f);
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
	try
	{
		assert(mRenderer);

		mSpriteManager->RenderStaticSprite(mRenderer, 0,
			mBackgroundPosition1);
		mSpriteManager->RenderStaticSprite(mRenderer, 0,
			mBackgroundPosition2);

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
