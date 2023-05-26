#include "MatchScene.hpp"
#include <ctime>
#include "DxLib.h"
// シーン関連
#include "SceneManager.hpp"
// プレイヤー関連
#include "Player.hpp"
#include "MCTS.hpp"
#include "Human.hpp"
// 汎用
#include "Point/Point.hpp"
#include "Debug/Debug.hpp"
#include "GameFunction.hpp"
#include "Color.hpp"

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
		SetPlayers(new Human(), new MCTS(10000000, 1000));
	}
	else
	{
		SetPlayers(new MCTS(10000000, 1000), new Human());
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
	switch (state_)
	{
	case MatchState::BeforeMatch:
		UpdateBeforeMatch();
		break;
	case MatchScene::MatchState::Think:
		UpdateThink();
		break;
	case MatchScene::MatchState::PlayAnimation:
		UpdatePlayAnimation();
		break;
	default:
		break;
	}
	++count_frame_;
}

void MatchScene::UpdateBeforeMatch()
{
	if (count_frame_ == FRAMES_PER_SECOND)
	{
		state_ = MatchState::Think;
		count_frame_ = 0;
	}
}

void MatchScene::UpdateThink()
{
	if (board_.IsFinish())
	{
		//Debug::Print("Human:", ((human_side_) ? "後手" : "先手"));
		//Debug::Print(board_);
		//Debug::Print("Human Stones:", HumanStones());
		//Debug::Print("AI Stones:", AIStones());

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

void MatchScene::UpdatePlayAnimation()
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
	last_board_.Init();
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
	auto [width, height] = GameFunction::GetWindowSize();
	const int BandTop = static_cast<int>(height * 0.3);
	const int BandBottom = static_cast<int>(height * 0.7);
	const int FontSize = static_cast<int>(height * 0.1);

	DrawBoard(width, height);
	DrawBox(0, BandTop, width, BandBottom, Color::BEFORE_MATCH_EFFECT_BAND, true);
	SetFontSize(FontSize);
	std::string human_side_str = (human_side_) ? "後手" : "先手";
	unsigned int human_side_color = (human_side_) ? Color::SECOND_PLAYER_STONE : Color::FIRST_PLAYER_STONE;
	DrawString(0, BandTop + FontSize, "対戦開始", Color::BEFORE_MATCH_EFFECT_CHAR);
	DrawString(0, BandTop + FontSize * 2, "あなたは　", Color::BEFORE_MATCH_EFFECT_CHAR);
	DrawString(GetDrawStringWidth("あなたは　", -1), BandTop + FontSize * 2, human_side_str.c_str(), human_side_color);
}

void MatchScene::DrawThink() const
{
	// 画面サイズの取得
	auto [width, height] = GameFunction::GetWindowSize();
	const int Mergin = static_cast<int>(height * 0.1);
	const int BoardSize = static_cast<int>(height * 0.8);
	const int CellSize = BoardSize / 8;
	const int EffectCircleRound = CellSize / 6;
	const int FontSize = static_cast<int>(height * 0.09);

	//どちらのターンか
	SetFontSize(FontSize);
	const std::string PlayerName = ((turn_ % 2 == human_side_) ? "あなた" : "AI");
	const unsigned int PlayerColor = ((turn_ % 2) ? Color::SECOND_PLAYER_STONE : Color::FIRST_PLAYER_STONE);
	const int StrWidth = GetDrawStringWidth(PlayerName.c_str(), -1);
	DrawString(Mergin, 0, PlayerName.c_str(), PlayerColor);
	DrawString(Mergin + StrWidth + 10, 0, "のターン", Color::TELL_TURN_CHAR);
	// 盤面の表示
	DrawBoard(width, height);
	// 合法手の表示
	std::vector<Point> legal_actions = board_.LegalActions();
	for (const Point& p : legal_actions)
	{
		const int x = Mergin + p.X() * CellSize + CellSize / 2;
		const int y = Mergin + p.Y() * CellSize + CellSize / 2;
		DrawCircle(x, y, EffectCircleRound, Color::LEGAL_ACTION_EFFECT);
	}
}

void MatchScene::DrawPlayAnimation() const
{
	// 画面サイズの取得
	auto [width, height] = GameFunction::GetWindowSize();
	const int Mergin = static_cast<int>(height * 0.1);
	const int BoardSize = static_cast<int>(height * 0.8);
	const int CellSize = BoardSize / 8;
	const int EffectCircleRound = CellSize / 6;

	
	DrawBoard(width, height);

	if (is_pass_)
	{
		const int Left = 0;
		const int Right = width;
		const int Top = height / 3;
		const int Bottom = height / 3 * 2;
		const int FontSize = static_cast<int>(height * 0.3);
		const auto [StrLeft, StrTop] = GameFunction::GetLeftTopToAlignCenter(Left, Top, Right, Bottom, "PASS", FontSize);
		
		DrawBox(Left, Top, Right, Bottom, Color::PASS_EFFECT_BAND, 1);
		SetFontSize(FontSize);
		DrawString(StrLeft, StrTop, "PASS", Color::PASS_EFFECT_CHAR);
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
					const int CenterX = Mergin + x * CellSize + CellSize / 2;
					const int CenterY = Mergin + y * CellSize + CellSize / 2;
					DrawCircle(CenterX, CenterY, EffectCircleRound, Color::SWAP_EFFECT, true);
				}
				diff >>= 1;
			}
		}
	}
}

void MatchScene::DrawBoard(int window_width, int window_height) const
{
	const int Mergin = static_cast<int>(window_height * 0.1);
	const int BoardSize = static_cast<int>(window_height * 0.8);
	const int CellSize = BoardSize / 8;
	const int EffectCircleRound = CellSize / 6;

	const int BoardLeft = Mergin;
	const int BoardRight = BoardLeft + BoardSize;
	const int BoardTop = Mergin;
	const int BoardBottom = BoardTop + BoardSize;
	// 背景盤を描画
	DrawBox(BoardLeft, BoardTop, BoardRight, BoardBottom, Color::BOARD_BACKGROUND, true);
	// セルを描画
	const int Begin = Mergin;
	const int End = Begin + BoardSize;
	// 縦線
	for (int i = 0; i < 9; ++i)
	{
		const int Step = Mergin + CellSize * i;
		DrawLine(Step, Begin, Step, End, Color::BOARD_LINE, 1);// 縦線
		DrawLine(Begin, Step, End, Step, Color::BOARD_LINE, 1);// 横線
	}
	// コマを表示
	const int StoneRound = CellSize / 2 - 2;
	std::uint64_t mask = 0x1;
	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			// 色
			unsigned int color[2] = { 0, 0 };
			if (turn_ % 2 == 0)
			{
				color[0] = Color::FIRST_PLAYER_STONE;
				color[1] = Color::SECOND_PLAYER_STONE;
			}
			else
			{
				color[0] = Color::SECOND_PLAYER_STONE;
				color[1] = Color::FIRST_PLAYER_STONE;
			}
			// 描画
			const int PosX = Mergin + CellSize * x + CellSize / 2;
			const int PosY = Mergin + CellSize * y + CellSize / 2;
			for (int i = 0; i < 2; ++i)
			{
				if (board_.board_[i] & mask)
				{
					DrawCircle(PosX, PosY, StoneRound, color[i]);
				}
			}
			mask <<= 1;
		}
	}
}
