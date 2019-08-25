#pragma once

class Vei2
{
public:
	Vei2() = default;
	Vei2(int x, int y);
	Vei2 operator+(const Vei2& rhs) const;
	Vei2& operator+=(const Vei2& rhs);
	Vei2 operator-(const Vei2& rhs) const;
	Vei2& operator-=(const Vei2& rhs);
	Vei2 operator*(int rhs) const;
	Vei2& operator*=(int rhs);
	Vei2 operator/(int rhs) const;
	Vei2& operator/=(int rhs);
	float GetLength() const;
	int GetLengthSq() const;
private:
	int x;
	int y;
};