#pragma once
#include <map>
#include <string>
class SceneManager;

class Scene
{
public:
	Scene(SceneManager* manager) : manager_(manager) {}
	virtual ~Scene() = default;

	/// <summary>
	/// �V�[�������g�ɐ؂�ւ�����ŏ��̃t���[���̍ŏ��ɌĂяo�����
	/// </summary>
	/// <param name="param">�O�̃V�[������n���ꂽ���</param>
	virtual void OnChanged(const std::map<std::string, int>& param) = 0;

	/// <summary>
	/// ���t���[���Ăяo�����`��p�֐�
	/// </summary>
	virtual void Draw() const = 0;

	/// <summary>
	/// ���t���[���Ăяo�����X�V�p�֐��D
	/// </summary>
	virtual void Update() = 0;

	static constexpr int FRAMES_PER_SECOND = 30;
protected:
	SceneManager* manager_;
};

