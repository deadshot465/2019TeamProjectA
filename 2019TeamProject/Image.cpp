#include "Image.h"
#include <SDL_image.h>
#include "Helper.h"

Image::Image(const std::string& filePath, SDL_Renderer* renderer,
	int renderXPos, int renderYPos)
{
	auto surface = IMG_Load(filePath.c_str());
	
	ThrowIfFailed(SDL_SetColorKey(surface, SDL_TRUE,
		SDL_MapRGBA(surface->format, TRANSPARENT_R, TRANSPARENT_G, TRANSPARENT_B, 0xFF)),
		"SDL failed to set the color key.\n");

	mTexture = SDL_CreateTextureFromSurface(renderer, surface);
	mWidth = surface->w;
	mHeight = surface->h;
	mRenderXPos = renderXPos;
	mRenderYPos = renderYPos;

	SDL_FreeSurface(surface);
}

Image::~Image()
{
	SDL_DestroyTexture(mTexture);
}

void Image::Render(SDL_Renderer* renderer, int dstXPos, int dstYPos,
	float scaleX, float scaleY)
{
	SDL_Rect src_rect = { mRenderXPos, mRenderYPos, mWidth, mHeight };
	SDL_Rect dst_rect = { dstXPos, dstYPos, mWidth * scaleX, mHeight * scaleY };

	SDL_RenderCopy(renderer, mTexture, &src_rect, &dst_rect);
}

void Image::Render(SDL_Renderer* renderer, int dstXPos, int dstYPos,
	float scaleX, float scaleY, double angle)
{
	SDL_Rect src_rect = { mRenderXPos, mRenderYPos, mWidth, mHeight };
	SDL_Rect dst_rect = { dstXPos, dstYPos, mWidth * scaleX, mHeight * scaleY };

	SDL_RenderCopyEx(renderer, mTexture, &src_rect, &dst_rect,
		angle, nullptr, SDL_FLIP_NONE);
}

int Image::GetWidth() const noexcept
{
	return mWidth;
}

int Image::GetHeight() const noexcept
{
	return mHeight;
}
