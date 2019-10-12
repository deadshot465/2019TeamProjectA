#pragma once
#include <memory>
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include "Helper.h"
#include "Image.h"

class Projectile
{
private:
	RenderConfig mRenderConfig = {};
	SDL_Rect mCollisionBox = {};
	SDL_Rect mParryCollisionBox = {};
	float mSpeed = 0.0f;
	bool mParryCollisionBoxEnabled = true;

public:
	static struct CollisionResult {
		std::optional<std::list<std::unique_ptr<Projectile>>::iterator> projectile;
		bool result;
	};

	Projectile(int width, int height, int projectileXPos, int projectileYPos, float speed);
	~Projectile();

	void SetRenderConfig(const RenderConfig& renderConfig) noexcept;
	const RenderConfig& GetRenderConfig() const noexcept;
	const SDL_Rect& GetCollisionBox() const noexcept;
	const SDL_Rect& GetParryCollisionBox() const noexcept;

	void Update();
	void SetParryCollisionBoxEnabled(bool status) noexcept;

	bool CheckCollision(const SDL_Rect& other) const noexcept;
	bool CheckParryCollision(const SDL_Rect& other) const noexcept;
};

