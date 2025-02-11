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
	static constexpr int NUMBER_SPRITE_WIDTH = 64;

public:
	SpriteManager() = default;
	~SpriteManager();

	void LoadStaticSprite(const std::string& filePath, SDL_Renderer* renderer,
		bool isAnimation = false, int frameWidth = 0, int frameHeight = 0);

	void SetAlphaBlend(size_t index, Uint8 alpha);

	void RenderStaticSprite(SDL_Renderer* renderer, size_t index, const RenderConfig& renderConfig);
	void RenderStaticSprite(SDL_Renderer* renderer, size_t index, const RenderConfig& renderConfig, double angle);
	void RenderNumbers(SDL_Renderer* renderer, size_t index, int num,
		const RenderConfig& renderConfig);
};

