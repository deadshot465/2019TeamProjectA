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
		auto bounds = SDL_Rect();
		bounds.w = width;
		bounds.h = height;

		ThrowIfFailed(SDL_Init(SDL_INIT_VIDEO), "SDL failed to initialize.\n");

		/*auto displays = SDL_GetNumVideoDisplays();
		auto display_mode = SDL_DisplayMode();
		SDL_GetCurrentDisplayMode(displays - 1, &display_mode);
		SDL_GetDisplayBounds(displays - 1, &bounds);
		width = bounds.w;
		height = bounds.h;*/

		mWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
		//SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);

		mSurface = SDL_GetWindowSurface(mWindow);

		ThrowIfFailed(SDL_UpdateWindowSurface(mWindow), "SDL failed to update the surface.\n");

		mSceneManager = std::make_unique<SceneManager>(mWindow, bounds);

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
				case SDLK_SPACE:
				{
					switch (mSceneManager->GetCurrentScene())
					{
					case SceneName::Title:
						mSceneManager->GetScene(SceneName::Game);
						break;
					case SceneName::Game:
						break;
					default:
						break;
					}
				}
				default:
					break;
				}
			}
			}
		}

		mSceneManager->Update();

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
