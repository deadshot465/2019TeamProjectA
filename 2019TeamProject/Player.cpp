#include "Player.h"

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
	mSprite = std::make_unique<Image>("texture/player.png", renderer, renderXPos, renderYPos);

	mRenderConfig.xPos = initialXPos;
	mRenderConfig.yPos = initialYPos;
	mRenderConfig.scaleX = 1.0f;
	mRenderConfig.scaleY = 1.0f;

	mCollisionBox.x = initialXPos;
	mCollisionBox.y = initialYPos;
	mCollisionBox.h = mSprite->GetHeight();
	mCollisionBox.w = mSprite->GetWidth();
}

Player::~Player()
{
	mSprite.reset();
}

void Player::Update(Uint8 keyState)
{
	if (keyState) {
		
	}
	else {
		mRenderConfig.xPos += speed;
		mCollisionBox.x += speed;
	}

}
