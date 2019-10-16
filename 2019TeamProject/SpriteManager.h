#pragma once
#include <memory>
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <vector>
#include "Image.h"
#include "Helper.h"

class SpriteManager
{
private:
	std::vector<std::unique_ptr<Image>> mStaticSprites;

public:
	SpriteManager() = default;
	~SpriteManager();

	void LoadStaticSprite(const std::string& filePath, SDL_Renderer* renderer);

	void RenderStaticSprite(SDL_Renderer* renderer, size_t index, const RenderConfig& renderConfig);
	void RenderStaticSprite(SDL_Renderer* renderer, size_t index, const RenderConfig& renderConfig, double angle);
};

