#include "SpriteManager.h"
#include <cassert>

SpriteManager::~SpriteManager()
{
	for (auto& sprite : mStaticSprites) {
		sprite.reset();
	}
}

void SpriteManager::LoadStaticSprite(const std::string& filePath, SDL_Renderer* renderer,
	bool isAnimation, int frameWidth, int frameHeight)
{
	mStaticSprites.emplace_back(std::make_unique<Image>(filePath, renderer, 0, 0,
		isAnimation, frameWidth, frameHeight));
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

void SpriteManager::RenderNumbers(SDL_Renderer* renderer, size_t index, int num, const RenderConfig& renderConfig)
{
	try
	{
		mStaticSprites[index]->SetRenderXPos(num * NUMBER_SPRITE_WIDTH);

		mStaticSprites[index]->Render(renderer,
			renderConfig.xPos, renderConfig.yPos,
			renderConfig.scaleX, renderConfig.scaleY);
	}
	catch (const std::exception&)
	{
		throw;
	}
}
