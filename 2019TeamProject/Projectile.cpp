#include "Projectile.h"

void Projectile::Update()
{
	mRenderConfig.xPos += mSpeed;
	mCollisionBox.x += mSpeed;
	mParryCollisionBox.x += mSpeed;
	mParryCollisionBoxReferencePoint.x += mSpeed;
}

void Projectile::SetParryCollisionBoxEnabled(bool status) noexcept
{
	mParryCollisionBoxEnabled = status;
}

Projectile::Projectile(int width, int height, int projectileXPos, int projectileYPos, float speed) : mSpeed(speed)
{
	mCollisionBox.x = projectileXPos;
	mCollisionBox.y = projectileYPos;
	mCollisionBox.h = height;
	mCollisionBox.w = width;

	mParryCollisionBox.x = projectileXPos - width;
	mParryCollisionBox.y = projectileYPos;
	mParryCollisionBox.h = height;
	mParryCollisionBox.w = width;
    
    mParryCollisionBoxReferencePoint.x = mParryCollisionBox.x + (width / 2);
    mParryCollisionBoxReferencePoint.y = mParryCollisionBox.y + (height / 2);

	mRenderConfig.xPos = projectileXPos;
	mRenderConfig.yPos = projectileYPos;
	mRenderConfig.scaleX = SCALE_SIZE;
	mRenderConfig.scaleY = SCALE_SIZE;
}

Projectile::~Projectile()
{
}

void Projectile::SetRenderConfig(const RenderConfig& renderConfig) noexcept
{
	mRenderConfig = renderConfig;
}

const RenderConfig& Projectile::GetRenderConfig() const noexcept
{
	return mRenderConfig;
}

const SDL_Rect& Projectile::GetCollisionBox() const noexcept
{
	return mCollisionBox;
}

const SDL_Rect& Projectile::GetParryCollisionBox() const noexcept
{
	return mParryCollisionBox;
}

const SDL_Point& Projectile::GetReferencePoint() const noexcept
{
    return mParryCollisionBoxReferencePoint;
}

bool Projectile::CheckCollision(const SDL_Rect& other) const noexcept
{
	return SDL_HasIntersection(&mCollisionBox, &other);
}

bool Projectile::CheckParryCollision(const SDL_Rect& other) const noexcept
{
	if (!mParryCollisionBoxEnabled) return false;
	return SDL_HasIntersection(&mParryCollisionBox, &other);
}
