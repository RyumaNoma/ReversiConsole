#pragma once
#include <utility>
#include <string>

class GameFunction
{
public:
	/// <summary>
	/// �Q�[����ʂ̃T�C�Y���擾����
	/// </summary>
	/// <returns>(���̒����C�c�̒���)</returns>
	static std::pair<int, int> GetWindowSize();

	/// <summary>
	/// �Q�[�����t���X�N���[�����[�h�ɕύX����
	/// </summary>
	static void ChangeToFullScreenMode();

	/// <summary>
	/// �Q�[�����E�B���h�E���[�h�ɕύX����
	/// </summary>
	/// <param name="width">�E�B���h�E�̉���</param>
	/// <param name="height">�E�B���h�E�̏c��</param>
	static void ChangeToWindowMode(int width, int height);

	/// <summary>
	/// ������𒆉����낦�ɂ��邽�߂̍���̍��W�����߂�D
	/// </summary>
	/// <param name="x1">���[�̍��W</param>
	/// <param name="y1">��[�̍��W</param>
	/// <param name="x2">�E�[�̍��W</param>
	/// <param name="y2">���[�̍��W</param>
	/// <param name="text">�\�����镶����</param>
	/// <param name="font_size">�\������ۂ̃t�H���g�T�C�Y</param>
	/// <returns>����̍��W</returns>
	static std::pair<int, int> GetLeftTopToAlignCenter(int x1, int y1, int x2, int y2, std::string text, int font_size);
};