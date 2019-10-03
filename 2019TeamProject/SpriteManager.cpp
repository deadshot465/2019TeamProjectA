#include "SpriteManager.h"

SpriteManager::~SpriteManager()
{
	for (auto& sprite : mCharacterSprites) {
		sprite.reset();
	}

	for (auto& sprite : mStaticSprites) {
		sprite.reset();
	}
}

void SpriteManager::LoadStaticSprite(const std::string& filePath, SDL_Renderer* renderer)
{
	mStaticSprites.emplace_back(std::make_unique<Image>(filePath, renderer, 0, 0));
}

int SpriteManager::LoadCharacterSprite(const std::string& filePath, SDL_Renderer* renderer, int renderXPos, int renderYPos)
{
	int index = static_cast<int>(mCharacterSprites.size());
	mCharacterSprites.emplace_back(std::make_unique<Image>(filePath, renderer, renderXPos, renderYPos));
	return index;
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

void SpriteManager::RenderStaticSprites(SDL_Renderer* renderer, const std::vector<RenderConfig>& renderConfigs)
{
	try
	{
		for (auto i = 0; i < renderConfigs.size(); ++i) {
			mStaticSprites[i]->Render(renderer,
				renderConfigs[i].xPos, renderConfigs[i].yPos,
				renderConfigs[i].scaleX, renderConfigs[i].scaleY);
		}
	}
	catch (const std::exception&)
	{
		throw;
	}
}

void SpriteManager::RenderCharacterSprite(SDL_Renderer* renderer, size_t index, const RenderConfig& renderConfig)
{
	try
	{
		mCharacterSprites[index]->Render(renderer,
			renderConfig.xPos, renderConfig.yPos,
			renderConfig.scaleX, renderConfig.scaleY);
	}
	catch (const std::exception&)
	{
		throw;
	}
}

void SpriteManager::RenderCharacterSprites(SDL_Renderer* renderer, const std::vector<RenderConfig>& renderConfigs)
{
	try
	{
		for (auto i = 0; i < renderConfigs.size(); ++i) {
			mCharacterSprites[i]->Render(renderer,
				renderConfigs[i].xPos, renderConfigs[i].yPos,
				renderConfigs[i].scaleX, renderConfigs[i].scaleY);
		}
	}
	catch (const std::exception&)
	{
		throw;
	}
}
