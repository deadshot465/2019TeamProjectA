#pragma once
#include "CoreSystem.h"
#include "Helper.h"

class SceneManager
{
private:
	CoreSystem mCoreSystem;
	SceneName mCurrentScene = {};

public:
	SceneManager(SDL_Window* window, const SDL_Rect& viewport);
	~SceneManager();

	void GetScene(SceneName scene) noexcept;
	
	void Update() noexcept;
};
