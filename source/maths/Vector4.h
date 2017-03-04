#ifndef VECTOR4_H
#define VECTOR4_H
#pragma once

#include "Matrix4.h"

template <typename T>
class Matrix4;

template<typename T>
class Vector4
{
	friend Matrix4<T>;
	
	bool fixedWComponent;
public:
	T x;
	T y;
	T z;
	T w;

	Vector4();
	Vector4( T x, T y, T z, T w );
	~Vector4();
	
	Vector4<T> Cross(Vector4<T>& other) const;
	
	double Dot(Vector4<T>& other) const;
	
	double Length() const;
	double LengthSquared() const;
	
	void Normalize();
	Vector4<T> Normalized() const;

	bool IsPosition() const;
	bool IsDirection() const;
	
	//Vector4<T> operator*(const Matrix4<T>& matrix) const;
	
	Vector4<T> operator-(const Vector4<T>& other) const;
};

#endif // VECTOR4_H