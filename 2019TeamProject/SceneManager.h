#pragma once
#include "CoreSystem.h"
#include "Helper.h"

class SceneManager
{
private:
	CoreSystem mCoreSystem;
	SceneName mCurrentScene = SceneName::Title;

public:
	SceneManager(SDL_Window* window, const SDL_Rect& viewport);
	~SceneManager();

	void GetScene(SceneName scene = SceneName::Title) noexcept;
	void Update() noexcept;
	void ClearGameStates() noexcept;

	const SceneName& GetCurrentScene() const noexcept;
};
