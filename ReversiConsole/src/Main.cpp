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
#include "GameFunction.hpp"
#include "Color.hpp"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Debug::FILENAME = "./Debug.txt";
	//Debug::Reset();

	// DxLib�̎��s�������ݒ�
	// �^�C�g��
	SetMainWindowText("Reversi");
	// ������ʃT�C�Y���f�X�N�g�b�v�T�C�Y�ɍ��킹��
	GameFunction::ChangeToFullScreenMode();
	// �w�i�F�̌���
	SetBackgroundColor(Color::BACKGROUND_R, Color::BACKGROUND_G, Color::BACKGROUND_B);

	if (DxLib_Init() == -1)
	{
		return -1;
	}
	
	//int num = GetDisplayModeNum();
	//DISPLAYMODEDATA dmm = GetDisplayMode(0);
	//GameFunction::ChangeToWindowMode(dmm.Width, dmm.Height);
	// �J�[�\���̕\���ݒ�F�I��
	SetMouseDispFlag(true);

	SceneManager manager;
	TitleScene ts(&manager);
	MatchScene ms(&manager);
	ResultScene rs(&manager);
	manager.Add("Title", &ts);
	manager.Add("Match", &ms);
	manager.Add("Result", &rs);
	manager.SetStartUpScene("Title");

	Timer t;
	int loop = 0;
	SetDrawScreen(DX_SCREEN_BACK);
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