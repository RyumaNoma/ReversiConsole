#include "ResultScene.hpp"
#include "SceneManager.hpp"
#include "DxLib.h"

void ResultScene::OnChanged(const std::map<std::string, int>& param)
{
}

void ResultScene::Draw() const
{
	// �v���C���[�H�̏����I
	// �R�}�̐�
	// ����E������
	// Press space to title
}

void ResultScene::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		manager_->Change("Match", std::map<std::string, int>());
	}
}
