#include "Random.hpp"

Random::Random()
	: x_(123)
{
}

Random::Random(std::uint64_t seed)
	: x_(seed)
{
}

Random::Random(const Random& random)
	: x_(random.x_)
{
}

std::uint32_t Random::Generate()
{
	x_ ^= x_ << 13;
	x_ ^= x_ >> 17;
	x_ ^= x_ << 5;
	return x_;
}
