#pragma once

template<typename T>
class Vector4
{
public:
	T x;
	T y;
	T z;
	T w;

	Vector4();
	Vector4( T x, T y, T z, T w );
	~Vector4();

	bool IsPosition();
	bool IsDirection();
};
