#include "Enemy.h"

void Enemy::UpdateProjectiles()
{
	auto current_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration<float, std::chrono::seconds::period>
		(current_time - mProjectileStartTime).count();

	if (duration > 0.25f) {
		
		auto iter = mProjectileConfigs.begin();
		while (iter != mProjectileConfigs.end()) {
			
			if (iter->xPos < -100) {
				iter = mProjectileConfigs.erase(iter);
				continue;
			}

			iter->xPos -= 25;
			++iter;
		}

		mProjectileStartTime = current_time;
	}
}

Enemy::Enemy(const std::string& filePath, SDL_Renderer* renderer,
	int renderXPos, int renderYPos,
	const std::string& projectileFilePath,
	int projectileXPos, int projectileYPos) :
	mAttackStartTime(std::chrono::high_resolution_clock::now()),
	mProjectileStartTime(std::chrono::high_resolution_clock::now()),
	mAttackDuration(GetRandomFloatNumber<float>(1.0f, 5.0f))
{
	mSprite = std::make_unique<Image>(filePath, renderer, renderXPos, renderYPos);
	mProjectile = std::make_unique<Image>(projectileFilePath, renderer, projectileXPos, projectileYPos);
}

Enemy::~Enemy()
{
	mSprite.reset();
}

void Enemy::Update(SDL_Renderer* renderer, const RenderConfig& renderConfig)
{
	auto current_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration<float, std::chrono::seconds::period>
		(current_time - mAttackStartTime).count();

	if (duration > mAttackDuration) {
		RenderConfig config = { renderConfig.xPos, renderConfig.yPos + 256, 1.0f, 1.0f };
		mProjectileConfigs.emplace_back(config);
		mAttackStartTime = current_time;
		mAttackDuration = GetRandomFloatNumber<float>(1.0f, 5.0f);
	}

	UpdateProjectiles();

	for (const auto& config : mProjectileConfigs) {
		mProjectile->Render(renderer, config.xPos, config.yPos, config.scaleX, config.scaleY);
	}

	mSprite->Render(renderer, renderConfig.xPos, renderConfig.yPos,
		renderConfig.scaleX, renderConfig.scaleY);
}
