#pragma once
#include <memory>
#include <SDL.h>
#include "Helper.h"
#include "Image.h"

class Projectile
{
private:
	RenderConfig mRenderConfig = {};
	SDL_Rect mCollisionBox = {};
	float mSpeed = 0.0f;

public:
	Projectile(int width, int height, int projectileXPos, int projectileYPos, float speed);
	~Projectile();

	void SetRenderConfig(const RenderConfig& renderConfig) noexcept;
	const RenderConfig& GetRenderConfig() const noexcept;
	const SDL_Rect& GetCollisionBox() const noexcept;

	void Update();

	bool CheckCollision(const SDL_Rect& other) const noexcept;
};

