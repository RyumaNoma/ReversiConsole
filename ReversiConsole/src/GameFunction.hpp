#pragma once
#include <utility>

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
};