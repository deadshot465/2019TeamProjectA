#pragma once

//プロトタイプ宣言
struct SDL_Window;
struct SDL_Rect;
class CoreSystem {
public:
	CoreSystem(SDL_Window* window, const SDL_Rect& viewport) {}
	~CoreSystem();
};

//****************************************
//CoreSystemクラスのコンストラクターには引数二つがある：
//- SDL_Window* window
//- const SDL_Rect& viewport
//この二つの引数は他のクラスから送るから、少なくともSceneManagerクラスのコンストラクターも
//この二つの引数があってほしい。
//SceneManagerのメンバー変数、基本的にはCoreSystem*型（CoreSystemのポインタ）のメンバー変数
//が必要。このメンバー変数の宣言と
//また、シーンを切り替えるため、異なるシーンを区別する方法（番号とか）が必要（intもしくは列挙体）。
//シーンの番号・名前を引数として受けられるpublicメンバー関数も作ってほしい。
//****************************************

class SceneManager
{
private:

public:
	
};

