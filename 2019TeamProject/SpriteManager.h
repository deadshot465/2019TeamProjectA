#pragma once
#include <memory>
#include <SDL.h>
#include <vector>
#include "Image.h"
#include "Helper.h"

class SpriteManager
{
private:
	std::vector<std::unique_ptr<Image>> mStaticSprites;
	std::vector<std::unique_ptr<Image>> mCharacterSprites;
	std::vector<std::unique_ptr<Image>> mProjectileSprites;

public:
	SpriteManager() = default;
	~SpriteManager();

	void LoadStaticSprite(const std::string& filePath, SDL_Renderer* renderer);
	int LoadCharacterSprite(const std::string& filePath, SDL_Renderer* renderer,
		int renderXPos = 0, int renderYPos = 0);

	void MoveBackground(int x);

	void RenderStaticSprite(SDL_Renderer* renderer, size_t index, const RenderConfig& renderConfig);
	void RenderStaticSprites(SDL_Renderer* renderer, const std::vector<RenderConfig>& renderConfigs);

	void RenderCharacterSprite(SDL_Renderer* renderer, size_t index, const RenderConfig& renderConfig);
	void RenderCharacterSprites(SDL_Renderer* renderer, const std::vector<RenderConfig>& renderConfigs);
};

