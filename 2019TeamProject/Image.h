#pragma once
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
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
		int renderXPos, int renderYPos, bool isAnimation = false,
		int frameWidth = 0, int frameHeight = 0);
	~Image();

	void SetRenderXPos(int xPos) noexcept;
	void SetRenderYPos(int yPos) noexcept;

	void Render(SDL_Renderer* renderer, int dstXPos, int dstYPos, float scaleX, float scaleY);
	void Render(SDL_Renderer* renderer, int dstXPos, int dstYPos,
		float scaleX, float scaleY, double angle);

	int GetWidth() const noexcept;
	int GetHeight() const noexcept;
};

