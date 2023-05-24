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

//DISPLAYMODEDATA ModeData;
//int i, ModeNum;
//
//int DesktopW, DesktopH;
//GetDefaultState(&DesktopW, &DesktopH, NULL);
//SetGraphMode(DesktopW, DesktopH, 32);
//Debug::Print(DesktopW, DesktopH);
//
//// �f�B�X�v���C���[�h�̐����擾����
//ModeNum = GetDisplayModeNum();
//
//// �f�B�X�v���C���[�h�̐��������[�v����
//for (i = 0; i < ModeNum; i++)
//{
//	// �f�B�X�v���C���[�h�̏����擾����
//	ModeData = GetDisplayMode(i);
//
//	// ��ʂɃf�B�X�v���C���[�h�̏���`�悷��
//	DrawFormatString(i / 40 * 128, (i % 40) * 11, GetColor(255, 255, 255), "%dx%d %dbit %dHz",
//		ModeData.Width, ModeData.Height, ModeData.ColorBitDepth, ModeData.RefreshRate);
//}
// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Debug::FILENAME = "./Debug.txt";
	Debug::Reset();

	// DxLib�̎��s�������ݒ�
	// Window���[�h
	ChangeWindowMode(true);
	// �^�C�g��
	SetMainWindowText("Reversi");
	// �J�[�\���̕\���ݒ�F�I��
	SetMouseDispFlag(true);
	// ������ʃT�C�Y���f�X�N�g�b�v�T�C�Y�ɍ��킹��
	GameFunction::ChangeToFullScreenMode();
	// �w�i�F�̌���
	SetBackgroundColor(100, 100, 0);

	if (DxLib_Init() == -1)
	{
		return -1;
	}	

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