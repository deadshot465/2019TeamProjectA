#pragma once

//�v���g�^�C�v�錾
struct SDL_Window;
struct SDL_Rect;
class CoreSystem {
public:
	CoreSystem(SDL_Window* window, const SDL_Rect& viewport) {}
	~CoreSystem();
};

//****************************************
//CoreSystem�N���X�̃R���X�g���N�^�[�ɂ͈����������F
//- SDL_Window* window
//- const SDL_Rect& viewport
//���̓�̈����͑��̃N���X���瑗�邩��A���Ȃ��Ƃ�SceneManager�N���X�̃R���X�g���N�^�[��
//���̓�̈����������Ăق����B
//SceneManager�̃����o�[�ϐ��A��{�I�ɂ�CoreSystem*�^�iCoreSystem�̃|�C���^�j�̃����o�[�ϐ�
//���K�v�B���̃����o�[�ϐ��̐錾��
//�܂��A�V�[����؂�ւ��邽�߁A�قȂ�V�[������ʂ�����@�i�ԍ��Ƃ��j���K�v�iint�������͗񋓑́j�B
//�V�[���̔ԍ��E���O�������Ƃ��Ď󂯂���public�����o�[�֐�������Ăق����B
//****************************************

class SceneManager
{
private:

public:
	
};

