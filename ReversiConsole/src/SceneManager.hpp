#pragma once
#include <string>
#include <map>
#include <queue>
#include <chrono>
#include "Scene.hpp"

class SceneManager
{
public:
	SceneManager();
	~SceneManager() {}

	/// <summary>
	/// ���t���[���Ăяo���D
	/// ���݂̃V�[����Draw��Update���Ăяo��
	/// </summary>
	/// <returns>����ɏI��������true</returns>
	bool Update();

	/// <summary>
	/// �Ǘ�����V�[���Q�ɃV�[����ǉ�����
	/// </summary>
	/// <param name="scene_name">�V�[����</param>
	/// <param name="scene">�V�[��</param>
	/// <returns>����ɏI��������true</returns>
	bool Add(std::string scene_name, Scene* scene);

	/// <summary>
	/// �ŏ��ɋN�������Ƃ��ɌĂяo�����V�[����ݒ肷��
	/// </summary>
	/// <param name="scene_name">�X�^�[�g�A�b�v�V�[��</param>
	/// <returns>�ʏ�ɏI��������true</returns>
	bool SetStartUpScene(std::string scene_name);

	/// <summary>
	/// ���̃t���[������Ăяo���V�[����ύX����D
	/// ��ʓI�ɁC�V�[���N���X������Ăяo�����D
	/// </summary>
	/// <param name="scene_name">�ݒ肷��V�[��</param>
	/// <param name="tell_game_data">���̃V�[���ɓ`����Q�[���f�[�^</param>
	/// <returns>�ʏ�ɏI��������true</returns>
	bool Change(std::string scene_name, const std::map<std::string, int>& tell_game_data);

	/// <summary>
	/// �Ǘ����Ă���V�[���Q���󂩂𔻒肷��
	/// </summary>
	/// <returns>�V�[���Q����Ȃ�true</returns>
	bool Empty() const;

	/// <summary>
	/// Exit()���Ăяo�������̃t���[������operator bool()��false��Ԃ��悤�ɂȂ�
	/// </summary>
	void Exit();

	/// <summary>
	/// �Ǘ����Ă���V�[���̌������߂�
	/// </summary>
	/// <returns>�Ǘ����Ă���V�[���̌�</returns>
	size_t Size() const;

	operator bool() const;
private:
	std::map<std::string, Scene*> scenes_;
	std::string startup_scene_;
	std::string now_scene_;//TODO: Scene*�^�ɕύX����
	bool changed_;
	std::map<std::string, int> game_data_;
	bool valid_exec_;
	std::queue<std::chrono::system_clock::time_point> frame_time_queue_;
};