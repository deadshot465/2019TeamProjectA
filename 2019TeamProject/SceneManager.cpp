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
}

void SceneManager::Update() noexcept
{
	mCoreSystem.ClearColor(0xFF, 0x00, 0xFF);
	mCoreSystem.Render(mCurrentScene);

	if (mCoreSystem.GetGameClearState())
		mCurrentScene = SceneName::GameClear;
}

void SceneManager::ClearGameStates() noexcept
{
	mCoreSystem.ClearGameStates();
}

const SceneName& SceneManager::GetCurrentScene() const noexcept
{
	return mCurrentScene;
}
