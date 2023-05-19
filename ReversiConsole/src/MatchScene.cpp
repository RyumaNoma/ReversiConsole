#include "MatchScene.hpp"
#include "DxLib.h"

MatchScene::MatchScene()
	: board_()
	, player{ nullptr, nullptr }
	, turn_(0)
{
}

MatchScene::MatchScene(Player* player1, Player* player2)
	: board_()
	, player{ player1, player2 }
	, turn_(0)
{
}

void MatchScene::OnChanged(const std::map<std::string, int>& param)
{
	Init();
}

void MatchScene::Draw() const
{
	// ��ʃT�C�Y�̎擾
	RECT rc;
	GetWindowRect(GetDesktopWindow(), &rc);
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;
	DrawBoard(width, height);
}

void MatchScene::Update()
{
	// TODO: �v���C���[�̃}���`�X���b�h��
}

void MatchScene::Init()
{
	turn_ = 0;
}

void MatchScene::DrawBoard(int window_width, int window_height) const
{
	const int mergin = window_height * 0.1;
	const int board_size = window_height * 0.8;
	const int cell_size = board_size / 8;
	// �w�i�Ղ�`��
	DrawBox(mergin, mergin, mergin + board_size, mergin + board_size, GetColor(0, 255, 0), true);
	// �Z����`��
	int begin = mergin;
	int end = mergin + board_size;
	// �c��
	for (int i = 0; i < 9; ++i)
	{
		int x = mergin + cell_size * i;
		DrawLine(x, begin, x, end, GetColor(0, 0, 0), 1);// �c��
		DrawLine(begin, x, end, x, GetColor(0, 0, 0), 1);// ����
	}
	// �R�}��\��
	std::uint64_t mask = 0x1;
	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			// �F
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
			// �`��
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
