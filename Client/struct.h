#pragma once
#include <assert.h>
#include <cmath>

struct Vec2
{
	float x;
	float y;

public:
	bool IsZero()
	{
		if (x == 0.f && y == 0.f)
			return true;
		return false;
	}

	float Length()
	{
		return (float)sqrt(x * x + y * y);
	}
	Vec2& Normalize()
	{
		float fLen = Length();

		assert(fLen != 0.f && "노말라이즈된 벡터에 0이 있음");
		x /= fLen;
		y /= fLen;

		return *this;
	}

public:
	Vec2& operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

	Vec2 operator + (Vec2 _vOther)
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}
	void operator += (Vec2 _vOther)
	{
		x += _vOther.x;
		y += _vOther.y;
	}
	void operator -= (Vec2 _vOther)
	{
		x -= _vOther.x;
		y -= _vOther.y;
	}

	Vec2 operator - (Vec2 _vOther)
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}
	Vec2 operator * (Vec2 _vOther)
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}
	Vec2 operator / (Vec2 _vOther)
	{
		assert (!(0.f == _vOther.x || 0.f == _vOther.y) && "벡터 나눗셈에 0이 있습니다");
		return Vec2(x / _vOther.x, y / _vOther.y);
	}

	Vec2 operator * (float _f)
	{
		return Vec2(x * _f, y * _f);
	}

	Vec2 operator * (int _i)
	{
		return Vec2(x * (float)_i, y * (float)_i);
	}
	Vec2 operator * (UINT _i)
	{
		return Vec2(x * (float)_i, y * (float)_i);
	}
	Vec2 operator / (float _f)
	{
		assert(!(0.f == _f) && "나눌 float 값이 0입니다.");
		return Vec2(x / _f, y / _f);
	}
	bool operator == (Vec2 _vOther)
	{
		if (x == _vOther.x && y == _vOther.y)
			return true;
		else
			return false;
	}
	bool operator != (Vec2 _vOther)
	{
		return !((*this) == _vOther);
	}
	bool operator <= (Vec2 _vOther)
	{
		if (x <= _vOther.x && y <= _vOther.y)
			return true;
		else
			return false;
	}
	bool operator >= (Vec2 _vOther)
	{
		if (x >= _vOther.x && y >= _vOther.y)
			return true;
		else
			return false;
	}
	bool operator < (Vec2 _vOther)
	{
		if (x < _vOther.x && y < _vOther.y)
			return true;
		else
			return false;
	}
	bool operator > (Vec2 _vOther)
	{
		if (x > _vOther.x && y > _vOther.y)
			return true;
		else
			return false;
	}
public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}
	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}
	Vec2(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{}
	Vec2(LONG _x, LONG _y)
		: x((float)_x)
		, y((float)_y)
	{}

	Vec2(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{}
};