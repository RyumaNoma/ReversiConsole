#pragma once
#include <iostream>

class Point
{
private:
	int x_;
	int y_;
public:
	Point()
		: x_(0)
		, y_(0)
	{
	}
	Point(const Point& point)
		: x_(point.x_)
		, y_(point.y_)
	{
	}
	Point(int x, int y)
		: x_(x)
		, y_(y)
	{
	}
	~Point() = default;

	Point operator +(Point point) const;
	Point operator -(Point point) const;
	Point operator *(int multiplier) const;
	Point operator /(int divisor) const;
	Point operator %(int divisor) const;
	Point& operator =(Point point);
	Point& operator +=(Point point);
	Point& operator -=(Point point);
	Point& operator *=(int multiplier);
	Point& operator /=(int divisor);
	Point& operator %=(int divisor);
	bool operator ==(Point point) const;
	bool operator !=(Point point) const;

	int x() const noexcept
	{
		return x_;
	}
	int y() const noexcept
	{
		return y_;
	}

	friend std::ostream& operator <<(std::ostream& os, Point point);
};