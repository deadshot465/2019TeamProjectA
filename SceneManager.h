#pragma once

//�v���g�^�C�v�錾
struct SDL_Window;
struct SDL_Rect;
class CoreSystem {
private:



public:
	CoreSystem(SDL_Window* window, const SDL_Rect& viewport) {}
	~CoreSystem();
    bool gameOver = false;
};

//****************************************
//CoreSystem�N���X�̃R���X�g���N�^�[�ɂ͈����������F
//- SDL_Window* window
//- const SDL_Rect& viewport
//���̓�̈����͑��̃N���X���瑗�邩��A���Ȃ��Ƃ�SceneManager�N���X�̃R���X�g���N�^�[��
//���̓�̈����������Ăق����B
//SceneManager�̃����o�[�ϐ��A��{�I�ɂ�CoreSystem*�^�iCoreSystem�̃|�C���^�j�̃����o�[�ϐ�
//���K�v�B���̃����o�[�ϐ��̐錾�Ə����������肢���܂��B
//�܂��A�V�[����؂�ւ��邽�߁A�قȂ�V�[������ʂ�����@�i�ԍ��Ƃ��j���K�v�iint�������͗񋓑́j�B
//�V�[���̔ԍ��E���O�������Ƃ��Ď󂯂���public�����o�[�֐�������Ăق����B
//****************************************

class SceneManager
{
private:
    enum SceneName
    {
        SCENE_TITLE,
        SCENE_GAME,
        SCENE_GAMEOVER
    };
    CoreSystem* CoreSystem;
    SceneName imanosiin
public:
    SceneManager(SDL_Window* window, const SDL_Rect& viewport) {
        
        CoreSystem�@ = new CoreSystem(window, viewport);

    }
    ~SceneManager()
    {
        delete CoreSystem;
    }

    int getscene(SceneName scene) {
        imanosiin = scene;
        switch (scene)
        {
        case SceneManager::SCENE_TITLE:
            break;
        case SceneManager::SCENE_GAME:
            break;
        case SceneManager::SCENE_GAMEOVER:
            break;
        default:
            break;
        }
    }

    void update() {
        switch (imanosiin)
        {
        case SceneManager::SCENE_TITLE:
            break;
        case SceneManager::SCENE_GAME:
            break;
        case SceneManager::SCENE_GAMEOVER:
            break;
        default:
            break;
        }
    }

};

