#pragma once
#include <cstdint>

class Random
{
public:
	Random();
	Random(std::uint32_t seed);
	Random(const Random&);
	~Random() {}
	/// <summary>
	/// 整数乱数を生成する
	/// </summary>
	/// <returns>乱数</returns>
	std::uint32_t Generate();

	/// <summary>
	/// [0, max)の範囲で整数乱数を生成する
	/// </summary>
	/// <param name="max">生成する乱数の上限</param>
	/// <returns>乱数</returns>
	std::uint32_t Generate(std::uint32_t max);
private:
	std::uint32_t x_;
};