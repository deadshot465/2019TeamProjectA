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

void Player::SetAnimationState(PlayerAnimation playerAnimation)
{
	mCurrentAnimation = playerAnimation;

	switch (playerAnimation)
	{
	case PlayerAnimation::Running:
		mSprite->SetRenderXPos(0);
		mSprite->SetRenderYPos(0);
		break;
	case PlayerAnimation::Guard:
		mSprite->SetRenderXPos(0);
		mSprite->SetRenderYPos(128);
		break;
	case PlayerAnimation::Parry:
		mSprite->SetRenderXPos(0);
		mSprite->SetRenderYPos(256);
		break;
	case PlayerAnimation::Injury:
		mSprite->SetRenderXPos(0);
		mSprite->SetRenderYPos(384);
		break;
	case PlayerAnimation::Beginning:
		mSprite->SetRenderXPos(0);
		mSprite->SetRenderYPos(512);
		break;
	default:
		break;
	}
}

void Player::UpdateAnimation()
{
	auto current_time = high_resolution_clock::now();
	auto elapsed = duration<float, seconds::period>(current_time - mAnimationTimer)
		.count();
	auto animation_elapsed = duration<float, seconds::period>(current_time - mAnimationStartTimer).count();

	if (elapsed > 0.2f) {
		mSprite->SetRenderXPos(mCurrentFrame * 128);
		mCurrentFrame = (mCurrentFrame + 1) % 3;
		mAnimationTimer = current_time;
	}

	if (mAnimationStarted && animation_elapsed > 0.6f) {
		mAnimationStarted = false;
		SetAnimationState(PlayerAnimation::Running);
	}
}

int Player::GetSpeed() const noexcept
{
	return mSpeed;
}

void Player::SetSpeed(int speed) noexcept
{
	mSpeed = speed;
}

int Player::GetWidth() const noexcept
{
    return mSprite->GetWidth();
}

void Player::SetAnimationStarted(bool started)
{
	mAnimationStarted = started;
	mAnimationStartTimer = high_resolution_clock::now();
}

bool Player::GetAnimationStarted() const noexcept
{
	return mAnimationStarted;
}

Player::Player(const std::string& filePath, SDL_Renderer* renderer, int renderXPos, int renderYPos, int initialXPos, int initialYPos) :
	mAnimationTimer(high_resolution_clock::now())
{
	mSprite = std::make_unique<Image>(filePath, renderer, renderXPos, renderYPos, true,
		128, 128);

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
