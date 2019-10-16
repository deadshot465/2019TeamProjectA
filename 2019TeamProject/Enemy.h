#pragma once
#include <chrono>
#include <list>
#include <memory>
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

	std::list<std::unique_ptr<Projectile>> mProjectiles;
	std::list<RenderConfig> mProjectileConfigs;

	void UpdateProjectiles();

public:
	Enemy(const std::string& filePath, SDL_Renderer* renderer,
		int renderXPos, int renderYPos,
		const std::string& projectileFilePath,
		int projectileXPos, int projectileYPos, int projectileRenderXPos = 32);
	~Enemy();

	Projectile::CollisionResult CheckCollisions(const SDL_Rect& playerCollisionBox) noexcept;
	Projectile::CollisionResult CheckParryCollisions(const SDL_Rect& playerCollisionBox) noexcept;

	void Update(SDL_Renderer* renderer, const RenderConfig& renderConfig);
	void DestroyProjectile(const std::list<std::unique_ptr<Projectile>>::iterator& iter);
};

