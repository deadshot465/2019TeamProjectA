#pragma once
#include <memory>
#include <SDL.h>
#include "Helper.h"
#include "Image.h"

class Projectile
{
private:
	RenderConfig mRenderConfig = {};
	SDL_Rect mOuterCollisionBox = {};
	SDL_Rect mInnerCollisionBox = {};
	float mSpeed = 0.0f;

public:
	Projectile(int width, int height, int projectileXPos, int projectileYPos, float speed);
	~Projectile();

	void SetRenderConfig(const RenderConfig& renderConfig) noexcept;
	const RenderConfig& GetRenderConfig() const noexcept;
	const SDL_Rect& GetInnerCollisionBox() const noexcept;
	const SDL_Rect& GetOuterCollisionBox() const noexcept;

	void Update();

	CollisionResult CheckCollision(const SDL_Rect& other) const noexcept;
};

