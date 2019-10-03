#include "Player.h"
#include <chrono>

using namespace std::chrono;

const SDL_Rect& Player::GetCollisionBox()
{
	return mCollisionBox;
}

void Player::Render(SDL_Renderer* renderer)
{
	mSprite->Render(renderer, mRenderConfig.xPos, mRenderConfig.yPos,
		mRenderConfig.scaleX, mRenderConfig.scaleY);
}

Player::Player(const std::string& filePath, SDL_Renderer* renderer, int renderXPos, int renderYPos, int initialXPos, int initialYPos)
{
	mSprite = std::make_unique<Image>(filePath, renderer, renderXPos, renderYPos);

	mRenderConfig.xPos = initialXPos;
	mRenderConfig.yPos = initialYPos;
	mRenderConfig.scaleX = SCALE_SIZE;
	mRenderConfig.scaleY = SCALE_SIZE;

	mCollisionBox.x = initialXPos;
	mCollisionBox.y = initialYPos;
	mCollisionBox.h = mSprite->GetHeight() * SCALE_SIZE;
	mCollisionBox.w = mSprite->GetWidth() * SCALE_SIZE;
}

Player::~Player()
{
	mSprite.reset();
}

void Player::UpdateSpeed(const CollisionResult& result)
{
	if (result == CollisionResult::Guard) {
		mSpeed = 0;
	}
	else if (result == CollisionResult::Parry) {
		mSpeed *= 3;
	}
}

void Player::Update(const std::chrono::time_point<std::chrono::steady_clock>& startTime)
{
	static auto start_time = time_point<steady_clock>();

	if (startTime != time_point<steady_clock>()) {
		start_time = startTime;
		auto current_time = high_resolution_clock::now();
		auto elapsed = duration<float, seconds::period>(current_time - start_time).count();

		if (elapsed > 2.0f) {
			mSpeed = 25;
		}
	}

	mRenderConfig.xPos += mSpeed;
	mCollisionBox.x += mSpeed;
}
