#include "MatchScene.hpp"
#include "DxLib.h"
#include "Player.hpp"
#include "Point/Point.hpp"
#include "MCTS.hpp"
#include "Human.hpp"
#include "Debug/Debug.hpp"
#include <ctime>

MatchScene::MatchScene(SceneManager* manager)
	: board_()
	, last_board_()
	, player_{ nullptr, nullptr }
	, turn_(0)
	, state_(MatchState::BeforeMatch)
	, count_frame_(0)
	, human_side_(0)
	, Scene(manager)
{
}

void MatchScene::OnChanged(const std::map<std::string, int>& param)
{
	// 時間を乱数として用いる
	human_side_ = time(NULL) % 2;
	if (human_side_ == 0)
	{
		SetPlayers(new Human(), new MCTS(10000, 10));
	}
	else
	{
		SetPlayers(new MCTS(10000, 10), new Human());
	}
	Init();
}

void MatchScene::Draw() const
{
	switch (state_)
	{
	case MatchState::BeforeMatch:
		DrawBeforeMatch();
		break;
	case MatchScene::MatchState::Think:
		DrawThink();
		break;
	case MatchScene::MatchState::PlayAnimation:
		DrawPlayAnimation();
		break;
	case MatchScene::MatchState::AfterMatch:
		DrawAfterMatch();
		break;
	default:
		break;
	}
}

void MatchScene::Update()
{
	// TODO: プレイヤーのマルチスレッド化
	switch (state_)
	{
	case MatchState::BeforeMatch:
		BeforeMatch();
		break;
	case MatchScene::MatchState::Think:
		Think();
		break;
	case MatchScene::MatchState::PlayAnimation:
		PlayAnimation();
		break;
	case MatchScene::MatchState::AfterMatch:
		break;
	default:
		break;
	}
	++count_frame_;
}

void MatchScene::BeforeMatch()
{
	if (count_frame_ == FRAMES_PER_SECOND)
	{
		state_ = MatchState::Think;
		count_frame_ = 0;
	}
}

void MatchScene::Think()
{
	if (board_.LegalPublic())
	{
		Point action = player_[turn_ % 2]->Act(board_);
		last_board_ = board_;
		board_.Act(action);
	}
	else // pass
	{
		board_.Swap();
	}
	// ターン終了処理
	++turn_;
	state_ = MatchState::PlayAnimation;
	count_frame_ = 0;
}

void MatchScene::PlayAnimation()
{
	if (count_frame_ == FRAMES_PER_SECOND)
	{
		state_ = MatchState::Think;
		count_frame_ = 0;
	}
}

void MatchScene::Init()
{
	board_.Init();
	for (int i = 0; i < 2; ++i)
	{
		player_[i]->Init();
	}
	turn_ = 0;
	state_ = MatchState::BeforeMatch;
}

void MatchScene::SetPlayers(Player* first_player, Player* second_player)
{
	player_[0] = first_player;
	player_[1] = second_player;
}

void MatchScene::DrawBeforeMatch() const
{
	// 画面サイズの取得
	RECT rc;
	GetWindowRect(GetDesktopWindow(), &rc);
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	DrawBoard(width, height);
	DrawBox(0, height * 0.3, width, height * 0.7, GetColor(255, 0, 0), true);
	// TODO: 中央ぞろえ
	SetFontSize(64);
	std::string human_side_str = (human_side_) ? "後手(白)" : "先手(黒)";
	DrawString(0, height * 0.3, "対戦開始", GetColor(255, 255, 255), GetColor(255, 255, 255));
	DrawString(0, height * 0.3 + 64, std::string("あなたは　" + human_side_str).c_str(), GetColor(255, 255, 255), GetColor(255, 255, 255));
}

void MatchScene::DrawThink() const
{
	// 画面サイズの取得
	RECT rc;
	GetWindowRect(GetDesktopWindow(), &rc);
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	DrawBoard(width, height);
}

void MatchScene::DrawPlayAnimation() const
{
	// 画面サイズの取得
	RECT rc;
	GetWindowRect(GetDesktopWindow(), &rc);
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	DrawBoard(width, height);
}

void MatchScene::DrawAfterMatch() const
{
	// 画面サイズの取得
	RECT rc;
	GetWindowRect(GetDesktopWindow(), &rc);
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	DrawBoard(width, height);
}

void MatchScene::DrawBoard(int window_width, int window_height) const
{
	const int mergin = window_height * 0.1;
	const int board_size = window_height * 0.8;
	const int cell_size = board_size / 8;
	// 背景盤を描画
	DrawBox(mergin, mergin, mergin + board_size, mergin + board_size, GetColor(0, 255, 0), true);
	// セルを描画
	int begin = mergin;
	int end = mergin + board_size;
	// 縦線
	for (int i = 0; i < 9; ++i)
	{
		int x = mergin + cell_size * i;
		DrawLine(x, begin, x, end, GetColor(0, 0, 0), 1);// 縦線
		DrawLine(begin, x, end, x, GetColor(0, 0, 0), 1);// 横線
	}
	// コマを表示
	std::uint64_t mask = 0x1;
	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			// 色
			unsigned int color[2] = { 0, 0 };
			if (turn_ % 2 == 0)
			{
				color[0] = GetColor(0, 0, 0);
				color[1] = GetColor(255, 255, 255);
			}
			else
			{
				color[0] = GetColor(255, 255, 255);
				color[1] = GetColor(0, 0, 0);
			}
			// 描画
			int pos_x = mergin + cell_size * x + cell_size / 2;
			int pos_y = mergin + cell_size * y + cell_size / 2;
			for (int i = 0; i < 2; ++i)
			{
				if (board_.board_[i] & mask)
				{
					DrawCircle(pos_x, pos_y, cell_size / 2 - 1, color[i]);
				}
			}
			mask <<= 1;
		}
	}
}
