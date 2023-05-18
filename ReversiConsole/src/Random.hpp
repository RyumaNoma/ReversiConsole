#include <cstdint>

class Random
{
public:
	Random();
	Random(std::uint32_t seed);
	Random(const Random&);
	~Random() {}
	/// <summary>
	/// ���������𐶐�����
	/// </summary>
	/// <returns>����</returns>
	std::uint32_t Generate();

	/// <summary>
	/// [0, max)�͈̔͂Ő��������𐶐�����
	/// </summary>
	/// <param name="max">�������闐���̏��</param>
	/// <returns>����</returns>
	std::uint32_t Generate(std::uint32_t max);
private:
	std::uint32_t x_;
};