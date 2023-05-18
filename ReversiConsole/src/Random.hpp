#include <cstdint>

class Random
{
public:
	Random();
	Random(std::uint32_t seed);
	Random(const Random&);
	~Random() {}
	/// <summary>
	/// ®”—”‚ğ¶¬‚·‚é
	/// </summary>
	/// <returns>—”</returns>
	std::uint32_t Generate();

	/// <summary>
	/// [0, max)‚Ì”ÍˆÍ‚Å®”—”‚ğ¶¬‚·‚é
	/// </summary>
	/// <param name="max">¶¬‚·‚é—”‚ÌãŒÀ</param>
	/// <returns>—”</returns>
	std::uint32_t Generate(std::uint32_t max);
private:
	std::uint32_t x_;
};