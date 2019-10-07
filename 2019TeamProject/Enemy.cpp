#include "Enemy.h"
#include <algorithm>

using namespace std::chrono;

void Enemy::UpdateProjectiles()
{
	auto current_time = high_resolution_clock::now();
	auto duration = std::chrono::duration<float, seconds::period>
		(current_time - mProjectileStartTime).count();

	if (duration > 0.25f) {
		
		auto iter = mProjectiles.begin();
		while (iter != mProjectiles.end()) {
			
			if (iter->get()->GetRenderConfig().xPos < -100) {
				iter = mProjectiles.erase(iter);
				continue;
			}

			iter->get()->Update();
			++iter;
		}
		mProjectileStartTime = current_time;
	}
}

Enemy::Enemy(const std::string& filePath, SDL_Renderer* renderer,
	int renderXPos, int renderYPos,
	const std::string& projectileFilePath,
	int projectileXPos, int projectileYPos) :
	mAttackStartTime(high_resolution_clock::now()),
	mProjectileStartTime(high_resolution_clock::now()),
	mAttackDuration(GetRandomFloatNumber<float>(1.0f, 5.0f))
{
	mSprite = std::make_unique<Image>(filePath, renderer, renderXPos, renderYPos, true,
		128, 128);
	mProjectile = std::make_unique<Image>(projectileFilePath, renderer, projectileXPos, projectileYPos, true, 32, 32);
	mProjectile->SetRenderXPos(32);
}

Enemy::~Enemy()
{
	mProjectile.reset();
	mSprite.reset();
}

bool Enemy::CheckCollisions(const SDL_Rect& playerCollisionBox) noexcept
{
	if (mProjectiles.empty()) return false;

	auto iter = mProjectiles.begin();
	
	while (iter != mProjectiles.end()) {
		auto res = iter->get()->CheckCollision(playerCollisionBox);
		if (res) {
			iter = mProjectiles.erase(iter);
			return res;
		}
		else {
			++iter;
		}
	}
}

void Enemy::Update(SDL_Renderer* renderer, const RenderConfig& renderConfig)
{
	auto current_time = high_resolution_clock::now();
	auto elapsed = std::chrono::duration<float, std::chrono::seconds::period>
		(current_time - mAttackStartTime).count();

	if (elapsed > mAttackDuration && !mAnimationStarted) {
		mAnimationStarted = true;
		mAnimationStartTime = high_resolution_clock::now();
		mSprite->SetRenderXPos(mSprite->GetWidth());

		mProjectiles.emplace_back(std::make_unique<Projectile>(mProjectile->GetWidth(), mProjectile->GetHeight(),
			renderConfig.xPos, renderConfig.yPos + 40, -25));
		mAttackStartTime = current_time;
		mAttackDuration = GetRandomFloatNumber<float>(1.0f, 5.0f);
	}

	auto animation_current_time = high_resolution_clock::now();
	auto animation_elapsed = duration<float, seconds::period>(animation_current_time - mAnimationStartTime).count();
	if (mAnimationStarted && animation_elapsed > 2.0f) {
		mAnimationStarted = false;
		mSprite->SetRenderXPos(0);
	}

	UpdateProjectiles();

	for (const auto& projectile : mProjectiles) {
		mProjectile->Render(renderer, projectile->GetRenderConfig().xPos,
			projectile->GetRenderConfig().yPos,
			projectile->GetRenderConfig().scaleX,
			projectile->GetRenderConfig().scaleY);

		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(renderer, &(projectile->GetCollisionBox()));
		SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawRect(renderer, &(projectile->GetCollisionBox()));
	}

	mSprite->Render(renderer, renderConfig.xPos, renderConfig.yPos,
		renderConfig.scaleX, renderConfig.scaleY);
}
