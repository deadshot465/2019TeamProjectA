#include "Projectile.h"

void Projectile::Update()
{
	mRenderConfig.xPos += mSpeed;
	mCollisionBox.x += mSpeed;
}

Projectile::Projectile(int width, int height, int projectileXPos, int projectileYPos, float speed) : mSpeed(speed)
{
	mCollisionBox.x = projectileXPos + width / 4;
	mCollisionBox.y = projectileYPos;
	mCollisionBox.h = height;
	mCollisionBox.w = width / 2;

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

bool Projectile::CheckCollision(const SDL_Rect& other) const noexcept
{
	return SDL_HasIntersection(&mCollisionBox, &other);
}
