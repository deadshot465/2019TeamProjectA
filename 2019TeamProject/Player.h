#pragma once
#include <chrono>
#include <list>
#include <memory>
#include <string>
#include <SDL.h>
#include "Helper.h"
#include "Image.h"

class Player
{
private:
	std::chrono::time_point<std::chrono::steady_clock> mMoveTimer;

	std::unique_ptr<Image> mSprite = nullptr;
	int mSpeed = 25;

	SDL_Rect mCollisionBox = {};
	RenderConfig mRenderConfig = {};

public:
	Player(const std::string& filePath, SDL_Renderer* renderer,
		int renderXPos, int renderYPos, int initialXPos, int initialYPos);
	~Player();

	const SDL_Rect& GetCollisionBox();

	void UpdateSpeed(const CollisionResult& result);
	void Update(const std::chrono::time_point<std::chrono::steady_clock>& startTime);
	void Render(SDL_Renderer* renderer);
};

