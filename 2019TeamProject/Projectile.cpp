#include "Projectile.h"

void Projectile::Update()
{
	mRenderConfig.xPos += mSpeed;
	mInnerCollisionBox.x += mSpeed;
	mOuterCollisionBox.x += mSpeed;
}

Projectile::Projectile(int width, int height, int projectileXPos, int projectileYPos, float speed) : mSpeed(speed)
{
	mInnerCollisionBox.x = projectileXPos + width / 4;
	mInnerCollisionBox.y = projectileYPos;
	mInnerCollisionBox.h = height;
	mInnerCollisionBox.w = width / 2;

	mOuterCollisionBox.x = projectileXPos;
	mOuterCollisionBox.y = projectileYPos;
	mOuterCollisionBox.h = height;
	mOuterCollisionBox.w = width;

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

const SDL_Rect& Projectile::GetInnerCollisionBox() const noexcept
{
	return mInnerCollisionBox;
}

const SDL_Rect& Projectile::GetOuterCollisionBox() const noexcept
{
	return mOuterCollisionBox;
}


CollisionResult Projectile::CheckCollision(const SDL_Rect& other) const noexcept
{
	auto res = SDL_HasIntersection(&mInnerCollisionBox, &other);
	if (res) return CollisionResult::Parry;

	res = SDL_HasIntersection(&mOuterCollisionBox, &other);
	if (res) return CollisionResult::Guard;
	else return CollisionResult::None;
}
