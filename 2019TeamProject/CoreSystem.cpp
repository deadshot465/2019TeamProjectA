#include "CoreSystem.h"
#include <algorithm>
#ifdef _WIN32
#include <SDL_image.h>
#else
#include <SDL2_image/SDL_image.h>
#endif
#include <cassert>

using namespace std::chrono;

void CoreSystem::UpdateBackground()
{
	if (mFadeStarted) return;
	static auto start_time = high_resolution_clock::now();
	auto current_time = high_resolution_clock::now();
	auto elapsed = duration<float, seconds::period>(current_time - start_time).count();

	if (elapsed > mBackgroundFloorUpdateDuration) {
		mFloorPosition1.xPos -= mFloorMoveSpeed;
		mFloorPosition2.xPos -= mFloorMoveSpeed;
        mBackgroundPosition -= mBackgroundMoveSpeed;
		mEnemyPosition.xPos -= mFloorMoveSpeed / 4;
		start_time = current_time;
	}

	if (mFloorPosition1.xPos <= -(WINDOW_WIDTH * 2))
		mFloorPosition1.xPos = WINDOW_WIDTH * 2;
	if (mFloorPosition2.xPos <= -(WINDOW_WIDTH * 2))
		mFloorPosition2.xPos = WINDOW_WIDTH * 2;
}

void CoreSystem::UpdatePlayer()
{
	if (mFadeStarted) return;
    if (!mPlayer->GetAnimationStarted()) mFloorMoveSpeed = FLOOR_MOVE_SPEED;
    if (!mPlayer->GetAnimationStarted()) mBackgroundMoveSpeed = 10;
	if (!mPlayer->GetAnimationStarted()) mBackgroundFloorUpdateDuration = 1.0f;

	auto key_states = SDL_GetKeyboardState(nullptr);
    auto parry_res = mCurrentEnemy->CheckParryCollisions(mPlayer->GetCollisionBox());
    
    if (parry_res.result && parry_res.projectile.has_value()) {
        if (key_states[SDL_SCANCODE_SPACE]) {
            if (!(mPlayer->GetAnimationStarted())) {
                mPlayer->SetAnimationState(PlayerAnimation::Parry);
                mPlayer->SetAnimationStarted(true);
                mCurrentEnemy->DestroyProjectile(parry_res.projectile.value());
				mPlayerScore += PARRY_SCORE;
				mBackgroundFloorUpdateDuration = 0.5f;
				return;
            }
        }
        if (parry_res.projectile.value()->get()->GetReferencePoint().x <
            mPlayer->GetCollisionBox().x + (mPlayer->GetWidth()))
            parry_res.projectile.value()->get()->SetParryCollisionBoxEnabled(false);
    }
    else {

        auto res = mCurrentEnemy->CheckCollisions(mPlayer->GetCollisionBox());
        if (res.result && res.projectile.has_value()) {
                
                if (!(mPlayer->GetAnimationStarted())) {
                    mFloorMoveSpeed = FLOOR_BACK_SPEED;
                    mBackgroundMoveSpeed = 0;
                    mPlayer->SetAnimationState(PlayerAnimation::Injury);
                    mPlayer->SetAnimationStarted(true);

					//************************************
					//リーくんが見てほしい
					//これは大丈夫ですか。
					//************************************
					
                }
            mCurrentEnemy->DestroyProjectile(res.projectile.value());
        }
    }

	auto special_res = mCurrentEnemy->CheckSpecialCollisions(mPlayer->GetCollisionBox());

	if (special_res.result && special_res.projectile.has_value()) {

		if (key_states[SDL_SCANCODE_SPACE]) {
            mFloorMoveSpeed = FLOOR_STOP_SPEED;
            mBackgroundMoveSpeed = 0;
			if (!(mPlayer->GetAnimationStarted())) {
				mPlayer->SetAnimationState(PlayerAnimation::Guard);
				mPlayer->SetAnimationStarted(true);

				//************************************
				//リーくんが見てほしい
				//これは大丈夫ですか。
				//************************************
				
				
			}
		}
		else {
			if (!(mPlayer->GetAnimationStarted())) {
               
				mPlayer->SetAnimationState(PlayerAnimation::Injury);
				mPlayer->SetAnimationStarted(true);

				//************************************
				//リーくんが見てほしい
				//これは大丈夫ですか。
				//************************************
                mFloorMoveSpeed = FLOOR_BACK_SPEED;
                mBackgroundMoveSpeed = 0;
			}
		}
		mCurrentEnemy->DestroySpecialProjectile(special_res.projectile.value());
	}

	if (mCurrentEnemy->CheckSelfCollision(mPlayer->GetCollisionBox())) {
		if (key_states[SDL_SCANCODE_SPACE] && !mFadeStarted) {

			if (!(mPlayer->GetAnimationStarted())) {
				mPlayer->SetAnimationState(PlayerAnimation::Parry);
				mPlayer->SetAnimationStarted(true);
				mPlayerScore += 300;
				mFadeStarted = true;
				return;
			}

		}
		else {
			if (!(mPlayer->GetAnimationStarted())) {
				mPlayer->SetAnimationState(PlayerAnimation::Injury);
				mPlayer->SetAnimationStarted(true);

				mEnemyPosition.xPos += 128;

				//************************************
				//リーくんが見てほしい
				//これは大丈夫ですか。
				//************************************
				mFloorMoveSpeed = FLOOR_STOP_SPEED;
				mBackgroundMoveSpeed = 0;
			}
		}
	}

	mPlayer->UpdateAnimation();
}

void CoreSystem::RenderTitleScreen()
{
	static auto start_time = high_resolution_clock::now();
	auto current_time = high_resolution_clock::now();
	auto elapsed = duration<float, seconds::period>(current_time - start_time).count();

	bool interval = (static_cast<int>(elapsed) % 2 == 0);

	mSpriteManager->RenderStaticSprite(mRenderer,
		interval ? static_cast<size_t>(StaticSpriteList::TitleScreenAppear) :
		static_cast<size_t>(StaticSpriteList::TitleScreenDisappear),
		{ 0, 0, SCALE_SIZE, SCALE_SIZE });
}

void CoreSystem::RenderGameScreen()
{
	auto current_time = high_resolution_clock::now();
	auto elapsed = duration<float, seconds::period>(current_time - mGameTimer).count();

	mSpriteManager->RenderStaticSprite(mRenderer,
		static_cast<int>(StaticSpriteList::Background),
		{ mBackgroundPosition, 0, SCALE_SIZE, SCALE_SIZE });
	mSpriteManager->RenderStaticSprite(mRenderer,
		static_cast<int>(StaticSpriteList::Floor),
		mFloorPosition1);
	mSpriteManager->RenderStaticSprite(mRenderer,
		static_cast<int>(StaticSpriteList::Floor),
		mFloorPosition2);
	mSpriteManager->RenderStaticSprite(mRenderer,
		static_cast<int>(StaticSpriteList::Clock),
		{ 64, static_cast<int>(WINDOW_HEIGHT * 0.05f), 1.0f, 1.0f });

	mSpriteManager->RenderNumbers(mRenderer,
		static_cast<int>(StaticSpriteList::ComboCount), mPlayerScore / 1 % 10,
		{ WINDOW_WIDTH - 128,
		static_cast<int>(WINDOW_HEIGHT * 0.05f), 1.0f, 1.0f });
	mSpriteManager->RenderNumbers(mRenderer,
		static_cast<int>(StaticSpriteList::ComboCount), mPlayerScore / 10 % 10,
		{ WINDOW_WIDTH - 192,
		static_cast<int>(WINDOW_HEIGHT * 0.05f), 1.0f, 1.0f });
	mSpriteManager->RenderNumbers(mRenderer,
		static_cast<int>(StaticSpriteList::ComboCount), mPlayerScore / 100 % 10,
		{ WINDOW_WIDTH - 256,
		static_cast<int>(WINDOW_HEIGHT * 0.05f), 1.0f, 1.0f });
	mSpriteManager->RenderNumbers(mRenderer,
		static_cast<int>(StaticSpriteList::ComboCount), mPlayerScore / 1000 % 10,
		{ WINDOW_WIDTH - 320,
		static_cast<int>(WINDOW_HEIGHT * 0.05f), 1.0f, 1.0f });
	mSpriteManager->RenderNumbers(mRenderer,
		static_cast<int>(StaticSpriteList::ComboCount), mPlayerScore / 10000 % 10,
		{ WINDOW_WIDTH - 384,
		static_cast<int>(WINDOW_HEIGHT * 0.05f), 1.0f, 1.0f });
		
	if (elapsed >= 1.0f && !mFadeStarted) {
		mClockAngle += 6.0f;
		mGameTimer = current_time;
		mGameElapsedTime += elapsed;
	}

	mSpriteManager->RenderStaticSprite(mRenderer,
		static_cast<int>(StaticSpriteList::Indicator),
		{ 64, static_cast<int>(WINDOW_WIDTH * 0.03f), 1.0f, 1.0f }, mClockAngle);

	UpdatePlayer();
	UpdateBackground();

	mCurrentEnemy->Update(mRenderer, mEnemyPosition, mFadeStarted);

	mPlayer->Render(mRenderer);

#ifdef _DEBUG
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderDrawRect(mRenderer, &(mPlayer->GetCollisionBox()));
#else
#endif

	if (mGameElapsedTime > 60.0f) {
		mGameClear = true;
	}
}

void CoreSystem::RenderGameClearScreen()
{
	static auto start_time = high_resolution_clock::now();
	auto current_time = high_resolution_clock::now();
	auto elapsed = duration<float, seconds::period>(current_time - start_time).count();

	bool interval = (static_cast<int>(elapsed) % 2 == 0);

	mSpriteManager->RenderStaticSprite(mRenderer,
		interval ? static_cast<size_t>(StaticSpriteList::GameClearAppear) :
		static_cast<size_t>(StaticSpriteList::GameClearDisappear),
		{ 0, 0, SCALE_SIZE, SCALE_SIZE });
}

void CoreSystem::FadeInOut()
{
	static auto start_time = high_resolution_clock::now();
	auto current_time = high_resolution_clock::now();
	auto elapsed = duration<float, seconds::period>(current_time - start_time).count();
	static Uint8 alpha = 0x00;
	static auto total_elapsed = 0.0f;
	static bool fade_out = false;

	if (elapsed > 0.1f) {
		mSpriteManager
			->SetAlphaBlend(static_cast<size_t>(StaticSpriteList::Fade), alpha);
		alpha += (fade_out) ? -25 : 25;
		total_elapsed += elapsed;
		start_time = current_time;
	}

	if (total_elapsed > 1.0f) {
		fade_out = true;
	}

	if (fade_out && alpha <= 0) {
		mFadeStarted = false;
		ResetEnemy();
		fade_out = false;
		alpha = 0x00;
		total_elapsed = 0.0f;
	}
}

void CoreSystem::ResetEnemy()
{
	mEnemyPosition
		= { static_cast<int>(mViewport.w * 0.8f), static_cast<int>(mViewport.h * 0.4f), SCALE_SIZE, SCALE_SIZE };
	mCurrentEnemyIndex = GetRandomIntegerNumber<int>(0, mEnemies.size() - 1);
	mCurrentEnemy = mEnemies[mCurrentEnemyIndex].get();
}

CoreSystem::CoreSystem(SDL_Window* window, const SDL_Rect& viewport)
	: mViewport(viewport), mGameTimer(high_resolution_clock::now()),
	mMixer(std::make_unique<Mixer>())
{
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
#ifdef _WIN32
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
#else
	mRenderer = SDL_GetRenderer(window);
#endif
	mSpriteManager = std::make_unique<SpriteManager>();

	mSpriteManager->LoadStaticSprite("texture/background.png", mRenderer);
	mSpriteManager->LoadStaticSprite("texture/sample_clock.png", mRenderer);
	mSpriteManager->LoadStaticSprite("texture/sample_indicator.png", mRenderer);
	mSpriteManager->LoadStaticSprite("texture/floor.png", mRenderer);
	mSpriteManager->LoadStaticSprite("texture/sample_title.png", mRenderer);
	mSpriteManager->LoadStaticSprite("texture/sample_title_disappear.png", mRenderer);
	mSpriteManager->LoadStaticSprite("texture/sample_game_clear.png", mRenderer);
	mSpriteManager->LoadStaticSprite("texture/sample_game_clear_disappear.png", mRenderer);
	mSpriteManager->LoadStaticSprite("texture/numbers.png", mRenderer, true, 64, 64);
	mSpriteManager->LoadStaticSprite("texture/fade.png", mRenderer);

	mEnemies.emplace_back(std::make_unique<Enemy>("texture/boss1.png", mRenderer, 0, 0,
		"texture/bullet.png", 0, 0));
	mEnemies.emplace_back(std::make_unique<Enemy>("texture/boss2.png", mRenderer, 0, 0,
		"texture/bullet.png", 0, 0, 0));
	mEnemies.emplace_back(std::make_unique<Enemy>("texture/boss3.png", mRenderer, 0, 0,
		"texture/bullet.png", 0, 0, 64));
	mPlayer = std::make_unique<Player>("texture/player_revised.png", mRenderer, 0, 0, 64, static_cast<int>(WINDOW_HEIGHT * 0.4f),
		"texture/moji.png");

	mCurrentEnemyIndex = GetRandomIntegerNumber<int>(0, mEnemies.size() - 1);
	mCurrentEnemy = mEnemies[mCurrentEnemyIndex].get();

	mEnemyPosition = {
		static_cast<int>(mViewport.w * 0.8f),
		static_cast<int>(mViewport.h * 0.4f),
		SCALE_SIZE, SCALE_SIZE
	};
}

CoreSystem::~CoreSystem()
{
	mMixer.reset();
	
	for (auto& enemy : mEnemies) {
		enemy.reset();
	}

	mPlayer.reset();
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

void CoreSystem::Render(SceneName scene)
{
	try
	{
		assert(mRenderer);

		switch (scene)
		{
		case SceneName::Title:
			RenderTitleScreen();
			break;
		case SceneName::Game:
			RenderGameScreen();
			break;
		case SceneName::GameClear:
			RenderGameClearScreen();
			break;
		default:
			break;
		}

		if (mFadeStarted) {
			FadeInOut();
			mSpriteManager->RenderStaticSprite(mRenderer,
				static_cast<size_t>(StaticSpriteList::Fade),
				{ 0, 0, SCALE_SIZE, SCALE_SIZE });
		}
		
		SDL_RenderPresent(mRenderer);
	}
	catch (const std::exception&)
	{
		throw;
	}
}

void CoreSystem::SetGameClearState(bool state) noexcept
{
	mGameClear = state;
}

bool CoreSystem::GetGameClearState() const noexcept
{
	return mGameClear;
}

void CoreSystem::ClearGameStates() noexcept
{
	mPlayerScore = 0;
	ResetEnemy();
	mGameClear = false;
	mGameTimer = high_resolution_clock::now();
	mClockAngle = 0.0f;
	mGameElapsedTime = 0.0f;
    mBackgroundPosition = 0;
}
