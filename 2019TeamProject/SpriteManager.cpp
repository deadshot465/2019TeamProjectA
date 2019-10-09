#include "SpriteManager.h"

SpriteManager::~SpriteManager()
{
	for (auto& sprite : mStaticSprites) {
		sprite.reset();
	}
}

void SpriteManager::LoadStaticSprite(const std::string& filePath, SDL_Renderer* renderer)
{
	mStaticSprites.emplace_back(std::make_unique<Image>(filePath, renderer, 0, 0));
}

void SpriteManager::RenderStaticSprite(SDL_Renderer* renderer, size_t index, const RenderConfig& renderConfig)
{
	try
	{
		mStaticSprites[index]->Render(renderer,
			renderConfig.xPos, renderConfig.yPos,
			renderConfig.scaleX, renderConfig.scaleY);
	}
	catch (const std::exception&)
	{
		throw;
	}
}

void SpriteManager::RenderStaticSprite(SDL_Renderer* renderer, size_t index, const RenderConfig& renderConfig, double angle)
{
	try
	{
		mStaticSprites[index]->Render(renderer,
			renderConfig.xPos, renderConfig.yPos,
			renderConfig.scaleX, renderConfig.scaleY, angle);
	}
	catch (const std::exception&)
	{
		throw;
	}
}