#pragma once
#include <chrono>
#include <memory>
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <vector>
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
	std::vector<std::unique_ptr<Enemy>> mEnemies;
	Enemy* mCurrentEnemy = nullptr;
	std::unique_ptr<Player> mPlayer = nullptr;
	std::unique_ptr<Mixer> mMixer = nullptr;

	RenderConfig mFloorPosition1 = { 0, 0, SCALE_SIZE, SCALE_SIZE };
	RenderConfig mFloorPosition2 = { WINDOW_WIDTH * 2, 0, SCALE_SIZE, SCALE_SIZE };
    int mBackgroundPosition = 0.0f;
	int mBackgroundMoveSpeed = 10;
    int mFloorMoveSpeed = FLOOR_MOVE_SPEED;
	float mBackgroundFloorUpdateDuration = 1.0f;
	bool mFadeStarted = false;

	RenderConfig mEnemyPosition = {};

	SDL_Rect mViewport = {};
	
	bool mGameClear = false;
	std::chrono::time_point<std::chrono::steady_clock> mGameTimer;
	float mClockAngle = 0.0f;
	float mGameElapsedTime = 0.0f;
	size_t mCurrentEnemyIndex = 0;
	int mPlayerScore = 0;
	
	void UpdateBackground();
	void UpdatePlayer();

	enum class StaticSpriteList {
		Background,
		Clock,
		Indicator,
		Floor,
		TitleScreenAppear,
		Zan,
		GameClearAppear,
		GameClearDisappear,
		ComboCount,
		Fade,
        Help,
	};

	void RenderTitleScreen();
	void RenderGameScreen();
	void RenderGameClearScreen();
	void FadeInOut();
	void ResetEnemy();

public:
	CoreSystem(SDL_Window* window, const SDL_Rect& viewport);
	~CoreSystem();

	void ClearColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xFF);
	void Render(SceneName scene);
	
	void SetGameClearState(bool state) noexcept;
	bool GetGameClearState() const noexcept;
	void ClearGameStates() noexcept;
};

