#include "DxLib.h"
#include <Windows.h>
#include <cassert>
// デバッグ
#include "Debug/Debug.hpp"
// シーン関連
#include "SceneManager.hpp"
#include "MatchScene.hpp"
#include "TitleScene.hpp"
#include "ResultScene.hpp"
// 汎用
#include "Point/Point.hpp"
#include "Timer/Timer.hpp"
#include "GameFunction.hpp"
#include "Color.hpp"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Debug::FILENAME = "./Debug.txt";
	//Debug::Reset();

	// DxLibの実行時初期設定
	// タイトル
	SetMainWindowText("Reversi");
	// 初期画面サイズをデスクトップサイズに合わせる
	GameFunction::ChangeToFullScreenMode();
	// 背景色の決定
	SetBackgroundColor(Color::BACKGROUND_R, Color::BACKGROUND_G, Color::BACKGROUND_B);

	if (DxLib_Init() == -1)
	{
		return -1;
	}
	
	//int num = GetDisplayModeNum();
	//DISPLAYMODEDATA dmm = GetDisplayMode(0);
	//GameFunction::ChangeToWindowMode(dmm.Width, dmm.Height);
	// カーソルの表示設定：オン
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