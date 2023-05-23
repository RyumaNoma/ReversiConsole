#include "MatchScene.hpp"
#include "DxLib.h"
#include "Player.hpp"
#include "Point/Point.hpp"
#include "MCTS.hpp"
#include "Human.hpp"
#include "Debug/Debug.hpp"
#include "SceneManager.hpp"
#include <ctime>

MatchScene::MatchScene(SceneManager* manager)
	: board_()
	, last_board_()
	, player_{ nullptr, nullptr }
	, turn_(0)
	, state_(MatchState::BeforeMatch)
	, count_frame_(0)
	, human_side_(0)
	, is_pass_(false)
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
	if (board_.IsFinish())
	{
		std::map<std::string, int> game_data;
		game_data["Level"] = 1;// TODO: Level選択機能
		game_data["NumberHumanStones"] = HumanStones();
		game_data["NumberAIStones"] = AIStones();
		game_data["HumanResult"] = HumanResult();
		game_data["Turn"] = turn_;

		manager_->Change("Result", game_data);
		return;
	}
	if (board_.LegalPublic())
	{
		Point action = player_[turn_ % 2]->Act(board_);
		board_.Act(action);
		is_pass_ = false;
	}
	else // pass
	{
		board_.Swap();
		is_pass_ = true;
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
		last_board_ = board_;
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
	is_pass_ = false;
}

void MatchScene::SetPlayers(Player* first_player, Player* second_player)
{
	player_[0] = first_player;
	player_[1] = second_player;
}

int MatchScene::HumanResult() const
{
	double result;
	if (turn_ % 2 == human_side_)
	{
		result = board_.Result();
	}
	else
	{
		result = 1 - board_.Result();
	}

	if (result == 1.0)
	{
		return 1;
	}
	else if (result == 0.5)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

int MatchScene::HumanStones() const
{
	if (turn_ % 2 == human_side_)
	{
		return board_.CountStones(false);
	}
	else
	{
		return board_.CountStones(true);
	}
}

int MatchScene::AIStones() const
{
	if (turn_ % 2 == human_side_)
	{
		return board_.CountStones(true);
	}
	else
	{
		return board_.CountStones(false);
	}
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
	const int mergin = height * 0.1;
	const int board_size = height * 0.8;
	const int cell_size = board_size / 8;

	DrawBoard(width, height);
	// 合法手の表示
	std::vector<Point> legal_actions = board_.LegalActions();
	for (const Point& p : legal_actions)
	{
		int x = mergin + p.X() * cell_size + cell_size / 2;
		int y = mergin + p.Y() * cell_size + cell_size / 2;
		DrawCircle(x, y, cell_size / 6, GetColor(192, 192, 192));
	}
}

void MatchScene::DrawPlayAnimation() const
{
	// 画面サイズの取得
	RECT rc;
	GetWindowRect(GetDesktopWindow(), &rc);
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;
	const int mergin = height * 0.1;
	const int board_size = height * 0.8;
	const int cell_size = board_size / 8;

	
	DrawBoard(width, height);

	if (is_pass_)
	{
		// TODO: 中央ぞろえ
		int left = 0;
		int right = width;
		int top = height / 3;
		int bottom = height / 3 * 2;
		DrawBox(left, top, right, bottom, GetColor(244, 173, 163), 1);
		SetFontSize(300);
		DrawString(left, top, "PASS", GetColor(0, 0, 0));
	}
	else
	{
		// 前の盤面との差分を強調する
		std::uint64_t diff = 0;
		for (int i = 0; i < 1; ++i)
		{
			diff |= (board_.board_[i] ^ last_board_.board_[1 - i]);
		}
		for (int y = 0; y < 8; ++y)
		{
			for (int x = 0; x < 8; ++x)
			{
				if (diff & 1)
				{
					int center_x = mergin + cell_size * x + cell_size / 2;
					int center_y = mergin + cell_size * y + cell_size / 2;
					DrawCircle(center_x, center_y, cell_size / 6, GetColor(244, 173, 163), true);
				}
				diff >>= 1;
			}
		}
	}
}

// TODO: 縦画面に対応(min(width, height))
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
