#pragma once
#include <chrono>
#include <list>
#include <memory>
#include <string>
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include "Helper.h"
#include "Image.h"

class Player
{
private:
	std::chrono::time_point<std::chrono::steady_clock> mAnimationTimer;

	std::unique_ptr<Image> mSprite = nullptr;
	int mSpeed = 25;

	SDL_Rect mCollisionBox = {};
	RenderConfig mRenderConfig = {};
	PlayerAnimation mCurrentAnimation = {};

public:
	Player(const std::string& filePath, SDL_Renderer* renderer,
		int renderXPos, int renderYPos, int initialXPos, int initialYPos);
	~Player();

	const SDL_Rect& GetCollisionBox();

	void Render(SDL_Renderer* renderer);
	void SetAnimationState(PlayerAnimation playerAnimation);
	void UpdateAnimation();

	int GetSpeed() const noexcept;
	void SetSpeed(int speed) noexcept;
};

