#include <cstdint>

class Random
{
public:
	Random();
	Random(std::uint64_t seed);
	Random(const Random&);
	~Random() {}

	std::uint32_t Generate();
private:
	std::uint32_t x_;
};