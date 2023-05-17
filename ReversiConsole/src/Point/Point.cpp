#include "Point.hpp"

Point Point::operator +(Point point) const
{
	return Point(x_ + point.x_, y_ + point.y_);
}

Point Point::operator -(Point point) const
{
	return Point(x_ - point.x_, y_ - point.y_);
}

Point Point::operator *(int mulriplier) const
{
	return Point(x_ * mulriplier, y_ * mulriplier);
}

Point Point::operator /(int divisor) const
{
	return Point(x_ / divisor, y_ / divisor);
}

Point Point::operator %(int divisor) const
{
	return Point(x_ % divisor, y_ % divisor);
}

Point& Point::operator =(Point point)
{
	x_ = point.x_;
	y_ = point.y_;
	return *this;
}

Point& Point::operator +=(Point point)
{
	x_ += point.x_;
	y_ += point.y_;
	return *this;
}

Point& Point::operator -=(Point point)
{
	x_ -= point.x_;
	y_ -= point.y_;
	return *this;
}

Point& Point::operator *=(int multiplier)
{
	x_ *= multiplier;
	y_ *= multiplier;
	return *this;
}

Point& Point::operator /=(int divisor)
{
	x_ /= divisor;
	y_ /= divisor;
	return *this;
}

Point& Point::operator %=(int divisor)
{
	x_ %= divisor;
	y_ %= divisor;
	return *this;
}

bool Point::operator ==(Point point) const
{
	return x_ == point.x_ && y_ == point.y_;
}

bool Point::operator !=(Point point) const
{
	return x_ != point.x_ || y_ != point.y_;
}

std::ostream& operator <<(std::ostream& os, Point point)
{
	os << '(' << point.x_ << ',' << point.y_ << ')';
	return os;
}