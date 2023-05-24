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

//DISPLAYMODEDATA ModeData;
//int i, ModeNum;
//
//int DesktopW, DesktopH;
//GetDefaultState(&DesktopW, &DesktopH, NULL);
//SetGraphMode(DesktopW, DesktopH, 32);
//Debug::Print(DesktopW, DesktopH);
//
//// ディスプレイモードの数を取得する
//ModeNum = GetDisplayModeNum();
//
//// ディスプレイモードの数だけループする
//for (i = 0; i < ModeNum; i++)
//{
//	// ディスプレイモードの情報を取得する
//	ModeData = GetDisplayMode(i);
//
//	// 画面にディスプレイモードの情報を描画する
//	DrawFormatString(i / 40 * 128, (i % 40) * 11, GetColor(255, 255, 255), "%dx%d %dbit %dHz",
//		ModeData.Width, ModeData.Height, ModeData.ColorBitDepth, ModeData.RefreshRate);
//}
// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Debug::FILENAME = "./Debug.txt";
	Debug::Reset();

	// DxLibの実行時初期設定
	// Windowモード
	ChangeWindowMode(true);
	// タイトル
	SetMainWindowText("Reversi");
	// カーソルの表示設定：オン
	SetMouseDispFlag(true);
	// 初期画面サイズをデスクトップサイズに合わせる
	GameFunction::ChangeToFullScreenMode();
	// 背景色の決定
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