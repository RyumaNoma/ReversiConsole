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
};