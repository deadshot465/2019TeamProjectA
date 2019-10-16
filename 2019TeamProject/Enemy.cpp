#include "Enemy.h"
#include <algorithm>
#include <optional>

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

		auto _iter = mSpecialProjectiles.begin();
		while (_iter != mSpecialProjectiles.end()) {

			if (_iter->get()->GetRenderConfig().xPos < -100) {
				_iter = mSpecialProjectiles.erase(_iter);
				continue;
			}

			_iter->get()->Update();
			++_iter;
		}

		mProjectileStartTime = current_time;
	}
}

void Enemy::UpdateCollisionBox(const RenderConfig& renderConfig) noexcept
{
	mCollisionBox.x = renderConfig.xPos;
	mCollisionBox.y = renderConfig.yPos;
}

Enemy::Enemy(const std::string& filePath, SDL_Renderer* renderer,
	int renderXPos, int renderYPos,
	const std::string& projectileFilePath,
	int projectileXPos, int projectileYPos, int projectileRenderXPos) :
	mAttackStartTime(high_resolution_clock::now()),
	mProjectileStartTime(high_resolution_clock::now()),
	mAttackDuration(GetRandomFloatNumber<float>(1.0f, 5.0f))
{
	mSprite = std::make_unique<Image>(filePath, renderer, renderXPos, renderYPos, true,
		128, 128);
	mProjectile = std::make_unique<Image>(projectileFilePath, renderer, projectileXPos, projectileYPos, true, 32, 32);
	mProjectile->SetRenderXPos(projectileRenderXPos);

	mCollisionBox.h = 128;
	mCollisionBox.w = 128;
}

Enemy::~Enemy()
{
	mProjectile.reset();
	mSprite.reset();
}

Projectile::CollisionResult Enemy::CheckCollisions(const SDL_Rect& playerCollisionBox) noexcept
{
	if (mProjectiles.empty()) return { std::nullopt, false };

	auto iter = mProjectiles.begin();
	
	while (iter != mProjectiles.end()) {
		auto res = iter->get()->CheckCollision(playerCollisionBox);
		if (res) {
			return { iter, res };
		}
		else {
			++iter;
		}
	}
	return { std::nullopt, false };
}

Projectile::CollisionResult Enemy::CheckParryCollisions(const SDL_Rect& playerCollisionBox) noexcept
{
	if (mProjectiles.empty()) return { std::nullopt, false };

	auto iter = mProjectiles.begin();

	while (iter != mProjectiles.end()) {
		auto res = iter->get()->CheckParryCollision(playerCollisionBox);
		if (res) {
			return { iter, res };
		}
		else {
			++iter;
		}
	}
	return { std::nullopt, false };
}

Projectile::CollisionResult Enemy::CheckSpecialCollisions(const SDL_Rect& playerCollisionBox) noexcept
{
	if (mSpecialProjectiles.empty()) return { std::nullopt, false };

	auto iter = mSpecialProjectiles.begin();

	while (iter != mSpecialProjectiles.end()) {
		auto res = iter->get()->CheckCollision(playerCollisionBox);
		if (res) {
			return { iter, res };
		}
		else {
			++iter;
		}
	}
	return { std::nullopt, false };
}

Projectile::CollisionResult Enemy::CheckSpecialParryCollisions(const SDL_Rect& playerCollisionBox) noexcept
{
	if (mSpecialProjectiles.empty()) return { std::nullopt, false };

	auto iter = mSpecialProjectiles.begin();

	while (iter != mSpecialProjectiles.end()) {
		auto res = iter->get()->CheckParryCollision(playerCollisionBox);
		if (res) {
			return { iter, res };
		}
		else {
			++iter;
		}
	}
	return { std::nullopt, false };
}

bool Enemy::CheckSelfCollision(const SDL_Rect& playerCollisionBox) const noexcept
{
	return SDL_HasIntersection(&mCollisionBox, &playerCollisionBox);
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

		if (GetRandomIntegerNumber<int>(0, 1) == 0) {
			mProjectiles.emplace_back(std::make_unique<Projectile>(mProjectile->GetWidth(), mProjectile->GetHeight(),
				renderConfig.xPos, renderConfig.yPos + 20, -25));
		}
		else {
			mSpecialProjectiles.emplace_back(std::make_unique<Projectile>(mProjectile->GetWidth() * 2, mProjectile->GetHeight() * 2,
				renderConfig.xPos, renderConfig.yPos + 20, -25, 2));
		}

		
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
		SDL_RenderDrawRect(renderer, &(projectile->GetParryCollisionBox()));
	}

	for (const auto& projectile : mSpecialProjectiles) {
		mProjectile->Render(renderer, projectile->GetRenderConfig().xPos,
			projectile->GetRenderConfig().yPos,
			projectile->GetRenderConfig().scaleX,
			projectile->GetRenderConfig().scaleY);

		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(renderer, &(projectile->GetCollisionBox()));
		SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawRect(renderer, &(projectile->GetParryCollisionBox()));
	}

	UpdateCollisionBox(renderConfig);

	mSprite->Render(renderer, renderConfig.xPos, renderConfig.yPos,
		renderConfig.scaleX, renderConfig.scaleY);
}

void Enemy::DestroyProjectile(const std::list<std::unique_ptr<Projectile>>::iterator& iter)
{
	mProjectiles.erase(iter);
}

void Enemy::DestroySpecialProjectile(const std::list<std::unique_ptr<Projectile>>::iterator& iter)
{
	mSpecialProjectiles.erase(iter);
}

const SDL_Rect& Enemy::GetCollisionBox() const noexcept
{
	return mCollisionBox;
}
