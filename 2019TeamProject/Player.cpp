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
	
}

int Player::GetSpeed() const noexcept
{
	return mSpeed;
}

void Player::SetSpeed(int speed) noexcept
{
	mSpeed = speed;
}

Player::Player(const std::string& filePath, SDL_Renderer* renderer, int renderXPos, int renderYPos, int initialXPos, int initialYPos)
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