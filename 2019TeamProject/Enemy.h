#pragma once
#include <chrono>
#include <list>
#include <memory>
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <string>
#include "Helper.h"
#include "Image.h"
#include "Projectile.h"

class Enemy
{
private:
	std::chrono::time_point<std::chrono::steady_clock> mAttackStartTime;
	std::chrono::time_point<std::chrono::steady_clock> mProjectileStartTime;
	std::chrono::time_point<std::chrono::steady_clock> mAnimationStartTime;
	bool mAnimationStarted = false;
	float mAttackDuration = 0.0f;

	std::unique_ptr<Image> mSprite = nullptr;
	std::unique_ptr<Image> mProjectile = nullptr;

	SDL_Rect mCollisionBox = {};
	SDL_Rect mParryCollisionBox = {};

	std::list<std::unique_ptr<Projectile>> mProjectiles;
	std::list<std::unique_ptr<Projectile>> mSpecialProjectiles;
	std::list<RenderConfig> mProjectileConfigs;

	void UpdateProjectiles();
	void UpdateCollisionBox(const RenderConfig& renderConfig) noexcept;

public:
	Enemy(const std::string& filePath, SDL_Renderer* renderer,
		int renderXPos, int renderYPos,
		const std::string& projectileFilePath,
		int projectileXPos, int projectileYPos, int projectileRenderXPos = 32);
	~Enemy();

	Projectile::CollisionResult CheckCollisions(const SDL_Rect& playerCollisionBox) noexcept;
	Projectile::CollisionResult CheckParryCollisions(const SDL_Rect& playerCollisionBox) noexcept;
	Projectile::CollisionResult CheckSpecialCollisions(const SDL_Rect& playerCollisionBox) noexcept;
	Projectile::CollisionResult CheckSpecialParryCollisions(const SDL_Rect& playerCollisionBox) noexcept;
	bool CheckSelfCollision(const SDL_Rect& playerCollisionBox) const noexcept;
	bool CheckSelfParryCollision(const SDL_Rect& playerCollisionBox) const noexcept;

	void Update(SDL_Renderer* renderer, const RenderConfig& renderConfig,
		bool fadeStarted);
	void DestroyProjectile(const std::list<std::unique_ptr<Projectile>>::iterator& iter);
	void DestroySpecialProjectile(const std::list<std::unique_ptr<Projectile>>::iterator& iter);

	const SDL_Rect& GetCollisionBox() const noexcept;
	const SDL_Rect& GetParryCollisionBox() const noexcept;
};

