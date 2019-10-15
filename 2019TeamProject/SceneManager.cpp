#include "SceneManager.h"

SceneManager::SceneManager(SDL_Window* window, const SDL_Rect& viewport)
	: mCoreSystem(window, viewport)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::GetScene(SceneName scene) noexcept
{
	mCurrentScene = scene;

	switch (scene)
	{
	case SceneName::Title:
		break;
	case SceneName::Game:
		break;
	case SceneName::GameClear:
		break;
	default:
		break;
	}
}

void SceneManager::Update() noexcept
{
	switch (mCurrentScene)
	{
	case SceneName::Title:
		break;
	case SceneName::Game:
		break;
	case SceneName::GameClear:
		break;
	default:
		break;
	}
}
