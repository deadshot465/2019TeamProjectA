#include "Window.h"
#include <iostream>
#include "Helper.h"

Window::~Window()
{
	SDL_FreeSurface(mSurface);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Window::Initialize(const std::string& title, int width, int height)
{
	try
	{
		ThrowIfFailed(SDL_Init(SDL_INIT_VIDEO), "SDL failed to initialize.\n");

		mWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

		mSurface = SDL_GetWindowSurface(mWindow);

		ThrowIfFailed(SDL_UpdateWindowSurface(mWindow), "SDL failed to update the surface.\n");

		mGraphicsEngine = std::make_unique<GraphicsEngine>(mWindow);

		mIsInit = true;
	}
	catch (const std::exception&)
	{
		throw;
	}
}

void Window::Broadcast()
{
	try
	{
		while (SDL_PollEvent(&mEvent)) {
			switch (mEvent.type) {
			case SDL_EventType::SDL_QUIT:
				mIsInit = false;
				break;
			case SDL_EventType::SDL_KEYDOWN: {
				switch (mEvent.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					mIsInit = false;
					break;
				default:
					break;
				}
			}
			}
		}

		mGraphicsEngine->ClearColor(0xFF, 0x00, 0xFF);
		mGraphicsEngine->Render();

		SDL_Delay(1);
	}
	catch (const std::exception&)
	{
		throw;
	}
}

bool Window::IsInit() const noexcept
{
	return mIsInit;
}
