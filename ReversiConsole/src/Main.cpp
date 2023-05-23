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


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Debug::FILENAME = "./Debug.txt";
	Debug::Reset();

	if (DxLib_Init() == -1)
	{
		return -1;
	}
	// DxLibの実行時初期設定
	SetGraphMode(1920, 1080, 32);         // 解像度の設定。人によってモニターが違うから変更できるようにする
	SetBackgroundColor(100, 100, 0); // 背景色の決定
	SetDrawArea(0, 0, 1921, 1081);   // 描画可能領域の設定
	SetMouseDispFlag(true);// カーソルの表示設定：オン

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