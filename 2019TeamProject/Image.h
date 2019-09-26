#pragma once
#include <SDL.h>
#include <string>

class Image
{
private:
	SDL_Texture* mTexture = nullptr;
	int mWidth = 0;
	int mHeight = 0;
	int mRenderXPos = 0;
	int mRenderYPos = 0;

	static const Uint8 TRANSPARENT_R = 250;
	static const Uint8 TRANSPARENT_G = 125;
	static const Uint8 TRANSPARENT_B = 250;

public:
	Image(const std::string& filePath, SDL_Renderer* renderer,
		int renderXPos, int renderYPos);
	~Image();

	void Render(SDL_Renderer* renderer, int dstXPos, int dstYPos, float scaleX, float scaleY);
};

