#include "DxLib.h"
#include <Windows.h>
#include <cassert>
// �f�o�b�O
#include "Debug/Debug.hpp"
// �V�[���֘A
#include "SceneManager.hpp"
#include "MatchScene.hpp"
#include "TitleScene.hpp"
#include "ResultScene.hpp"
// �ėp
#include "Point/Point.hpp"
#include "Timer/Timer.hpp"


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Debug::FILENAME = "./Debug.txt";
	Debug::Reset();

	if (DxLib_Init() == -1)
	{
		return -1;
	}
	// DxLib�̎��s�������ݒ�
	SetGraphMode(1920, 1080, 32);         // �𑜓x�̐ݒ�B�l�ɂ���ă��j�^�[���Ⴄ����ύX�ł���悤�ɂ���
	SetBackgroundColor(100, 100, 0); // �w�i�F�̌���
	SetDrawArea(0, 0, 1921, 1081);   // �`��\�̈�̐ݒ�
	SetMouseDispFlag(true);// �J�[�\���̕\���ݒ�F�I��

	SceneManager manager;
	TitleScene ts(&manager);
	MatchScene ms(&manager);
	ResultScene rs(&manager);
	assert(manager.Add("Title", &ts));
	assert(manager.Add("Match", &ms));
	assert(manager.Add("Result", &rs));
	assert(manager.SetStartUpScene("Title"));

	Timer t;
	int loop = 0;
	while (manager && ProcessMessage() == 0)
	{
		t.Reset();
		ClearDrawScreen();
		manager.Update();
		auto elapsed = t.ElapsedMilliseconds();
		if (elapsed < 33)
		{
			Sleep(33 - elapsed);
		}
	}

	DxLib_End();

	return 0;
}