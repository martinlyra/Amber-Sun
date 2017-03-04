#include "Matrix4.h"

#include "meta.h"

#include <iostream>

#define PI 3.14159265

#include <math.h>

TEMPLATE_IMPLEMENT_MATHEMATICAL_TYPES(Matrix4);

template <typename T>
Matrix4<T>::Matrix4(
	T _00, T _01, T _02, T _03,
	T _10, T _11, T _12, T _13,
	T _20, T _21, T _22, T _23,
	T _30, T _31, T _32, T _33
	)
{
	auto am = &data.asMatrix;
	
	am->_00 = _00; am->_01 = _01; am->_02 = _02; am->_03 = _03;
	am->_10 = _10; am->_11 = _11; am->_12 = _12; am->_13 = _13;
	am->_20 = _20; am->_21 = _21; am->_22 = _22; am->_23 = _23;
	am->_30 = _30; am->_31 = _31; am->_32 = _32; am->_33 = _33;
}

template <typename T>
Matrix4< T > Matrix4<T>::LookAlong(Vector4< T > eyePosition, Vector4< T > direction, Vector4< T > up)
{
	auto f = direction.Normalized();
	auto s = f.Cross(up).Normalized();
	auto u = s.Cross(f);
	
	return Matrix4<T>(
		s.x, u.x, -f.x, 0.0f,
		s.y, u.y, -f.y, 0.0f,
		s.z, u.z, -f.z, 0.0f,
		-s.Dot(eyePosition), u.Dot(eyePosition), f.Dot(eyePosition), 1.0f
	);
}

template <typename T>
Matrix4< T > Matrix4<T>::LookAt(const Vector4< T > eyePosition, const Vector4< T > targetPosition, const Vector4< T > up)
{
	auto delta = targetPosition - eyePosition;
	return LookAlong(eyePosition, delta, up);
}

template <typename T>
Matrix4< T > Matrix4<T>::Perspective(const T fov, const T ratio, const T zNear, const T zFar)
{
	const T zDistance = zFar - zNear;
	const T alpha = fov * PI/180;
	const T arg = tan(alpha/2);
	
	return Matrix4<T>(
		(1.0f / ( arg * ratio )),
		0.0f,
		0.0f,
		0.0f,
		
		0.0f,
		(1.0f / arg),
		0.0f,
		0.0f,
		
		0.0f,
		0.0f,
		- ((zFar + zNear) / zDistance),
		- 1.0f,
		
		0.0f,
		0.0f,
		- (2.0f * zFar * zNear / zDistance),
		0.0f
	);
}



template <typename T>
void Matrix4<T>::Concatenate(const Matrix4< T >& other)
{
	(*this) *= other;
}

template <typename T>
void Matrix4<T>::SetAsIdentity()
{
	auto tm = &this->data.asMatrix;
	
	tm->_00 = 1; tm->_01 = 0; tm->_02 = 0; tm->_03 = 0;
	tm->_10 = 0; tm->_11 = 1; tm->_12 = 0; tm->_13 = 0;
	tm->_20 = 0; tm->_21 = 0; tm->_22 = 1; tm->_23 = 0;
	tm->_30 = 0; tm->_31 = 0; tm->_32 = 0; tm->_33 = 1;
}

template <typename T>
void Matrix4<T>::SetAsZero()
{
	auto tm = &this->data.asMatrix;
	
	tm->_00 = 0; tm->_01 = 0; tm->_02 = 0; tm->_03 = 0;
	tm->_10 = 0; tm->_11 = 0; tm->_12 = 0; tm->_13 = 0;
	tm->_20 = 0; tm->_21 = 0; tm->_22 = 0; tm->_23 = 0;
	tm->_30 = 0; tm->_31 = 0; tm->_32 = 0; tm->_33 = 0;
}

template <typename T>
void Matrix4<T>::SetScaling(double x, double y, double z)
{
	auto tm = &this->data.asMatrix;
	
	tm->_00 = x; tm->_01 = 0; tm->_02 = 0; tm->_03 = 0;
	tm->_10 = 0; tm->_11 = y; tm->_12 = 0; tm->_13 = 0;
	tm->_20 = 0; tm->_21 = 0; tm->_22 = z; tm->_23 = 0;
	tm->_30 = 0; tm->_31 = 0; tm->_32 = 0; tm->_33 = 1;
}


template <typename T>
const T Matrix4<T>::operator()(int x, int y) const
{
	return data.asArray2D[x][y];
}

template <typename T>
const T* Matrix4<T>::operator[](int index) const
{
	return data.asArray2D[index];
}

template <typename T>
Matrix4< T > Matrix4<T>::operator*(const Matrix4< T >& other) const
{
	auto tm = &this->data.asMatrix;
	auto om = &other.data.asMatrix;
	
	return Matrix4<T>(
		tm->_00*om->_00 + tm->_01*om->_10 + tm->_02*om->_20 + tm->_03*om->_30,
		tm->_00*om->_01 + tm->_01*om->_11 + tm->_02*om->_21 + tm->_03*om->_31,
		tm->_00*om->_02 + tm->_01*om->_12 + tm->_02*om->_22 + tm->_03*om->_32,
		tm->_00*om->_03 + tm->_01*om->_13 + tm->_02*om->_23 + tm->_03*om->_33,
		
		tm->_10*om->_00 + tm->_11*om->_10 + tm->_12*om->_20 + tm->_13*om->_30,
		tm->_10*om->_01 + tm->_11*om->_11 + tm->_12*om->_21 + tm->_13*om->_31,
		tm->_10*om->_02 + tm->_11*om->_12 + tm->_12*om->_22 + tm->_13*om->_32,
		tm->_10*om->_03 + tm->_11*om->_13 + tm->_12*om->_23 + tm->_13*om->_33,
		
		tm->_20*om->_00 + tm->_21*om->_10 + tm->_22*om->_20 + tm->_23*om->_30,
		tm->_20*om->_01 + tm->_21*om->_11 + tm->_22*om->_21 + tm->_23*om->_31,
		tm->_20*om->_02 + tm->_21*om->_12 + tm->_22*om->_22 + tm->_23*om->_32,
		tm->_20*om->_03 + tm->_21*om->_13 + tm->_22*om->_23 + tm->_23*om->_33,
		
		tm->_30*om->_00 + tm->_31*om->_10 + tm->_32*om->_20 + tm->_33*om->_30,
		tm->_30*om->_01 + tm->_31*om->_11 + tm->_32*om->_21 + tm->_33*om->_31,
		tm->_30*om->_02 + tm->_31*om->_12 + tm->_32*om->_22 + tm->_33*om->_32,
		tm->_30*om->_03 + tm->_31*om->_13 + tm->_32*om->_23 + tm->_33*om->_33
	);
}

template <typename T>
Matrix4< T > Matrix4<T>::operator/(const Matrix4< T >& other) const
{
	auto tm = &this->data.asMatrix;
	auto om = &other.data.asMatrix;
	
	return Matrix4(
		tm->_00/om->_00 + tm->_01/om->_10 + tm->_02/om->_20 + tm->_03/om->_30,
		tm->_00/om->_01 + tm->_01/om->_11 + tm->_02/om->_21 + tm->_03/om->_31,
		tm->_00/om->_02 + tm->_01/om->_12 + tm->_02/om->_22 + tm->_03/om->_32,
		tm->_00/om->_03 + tm->_01/om->_13 + tm->_02/om->_23 + tm->_03/om->_33,
		
		tm->_10/om->_00 + tm->_11/om->_10 + tm->_12/om->_20 + tm->_13/om->_30,
		tm->_10/om->_01 + tm->_11/om->_11 + tm->_12/om->_21 + tm->_13/om->_31,
		tm->_10/om->_02 + tm->_11/om->_12 + tm->_12/om->_22 + tm->_13/om->_32,
		tm->_10/om->_03 + tm->_11/om->_13 + tm->_12/om->_23 + tm->_13/om->_33,
		
		tm->_20/om->_00 + tm->_21/om->_10 + tm->_22/om->_20 + tm->_23/om->_30,
		tm->_20/om->_01 + tm->_21/om->_11 + tm->_22/om->_21 + tm->_23/om->_31,
		tm->_20/om->_02 + tm->_21/om->_12 + tm->_22/om->_22 + tm->_23/om->_32,
		tm->_20/om->_03 + tm->_21/om->_13 + tm->_22/om->_23 + tm->_23/om->_33,
		
		tm->_30/om->_00 + tm->_31/om->_10 + tm->_32/om->_20 + tm->_33/om->_30,
		tm->_30/om->_01 + tm->_31/om->_11 + tm->_32/om->_21 + tm->_33/om->_31,
		tm->_30/om->_02 + tm->_31/om->_12 + tm->_32/om->_22 + tm->_33/om->_32,
		tm->_30/om->_03 + tm->_31/om->_13 + tm->_32/om->_23 + tm->_33/om->_33
	);
}

template <typename T>
Matrix4< T > Matrix4<T>::operator+(const Matrix4< T >& other) const
{
	auto tm = &this->data.asMatrix;
	auto om = &other.data.asMatrix;
	
	return Matrix4(
		tm->_00 + om->_00, tm->_01 + om->_01, tm->_02 + om->_02, tm->_03 + om->_03,
		tm->_10 + om->_10, tm->_11 + om->_11, tm->_12 + om->_12, tm->_13 + om->_13,
		tm->_20 + om->_20, tm->_21 + om->_21, tm->_22 + om->_22, tm->_23 + om->_23,
		tm->_30 + om->_30, tm->_31 + om->_31, tm->_32 + om->_32, tm->_33 + om->_33
	);
}

template <typename T>
Matrix4< T > Matrix4<T>::operator-(const Matrix4< T >& other) const
{
	auto tm = &this->data.asMatrix;
	auto om = &other.data.asMatrix;
	
	return Matrix4(
		tm->_00 - om->_00, tm->_01 - om->_01, tm->_02 - om->_02, tm->_03 - om->_03,
		tm->_10 - om->_10, tm->_11 - om->_11, tm->_12 - om->_12, tm->_13 - om->_13,
		tm->_20 - om->_20, tm->_21 - om->_21, tm->_22 - om->_22, tm->_23 - om->_23,
		tm->_30 - om->_30, tm->_31 - om->_31, tm->_32 - om->_32, tm->_33 - om->_33
	);
}

template <typename T>
Matrix4< T > Matrix4<T>::operator*=(const Matrix4< T >& other)
{
	(*this) = (*this * other);
	return (*this);
}

template <typename T>
Matrix4< T > Matrix4<T>::operator/=(const Matrix4< T >& other)
{
	(*this) = (*this / other);
	return (*this);
}

template <typename T>
Matrix4< T > Matrix4<T>::operator+=(const Matrix4< T >& other)
{ 
	(*this) = (*this + other);
	return (*this);
}

template <typename T>
Matrix4< T > Matrix4<T>::operator-=(const Matrix4< T >& other)
{
	(*this) = (*this - other);
	return (*this);
}

template <typename T>
bool Matrix4<T>::operator==(const Matrix4< T >& other) const
{
	auto tm = &this->data.asMatrix;
	auto om = &other.data.asMatrix;
	
	return (
		(tm->_00 == om->_00 && tm->_01 == om->_01 && tm->_02 == om->_02 && tm->_03 == om->_03) &&
		(tm->_10 == om->_10 && tm->_11 == om->_11 && tm->_12 == om->_12 && tm->_13 == om->_13) &&
		(tm->_20 == om->_20 && tm->_21 == om->_21 && tm->_22 == om->_22 && tm->_23 == om->_23) &&
		(tm->_30 == om->_30 && tm->_31 == om->_31 && tm->_32 == om->_32 && tm->_33 == om->_33)
	);
}

template <typename T>
bool Matrix4<T>::operator!=(const Matrix4< T >& other) const
{
	return !(*this == other);
}

template <typename T>
Vector4< T > Matrix4<T>::operator*(const Vector4< T >& vector) const
{
	auto tm = &this->data.asMatrix;
	
	return Vector4<T>(
			vector.x * tm->_00 + vector.y * tm->_10 + vector.z * tm->_20 + vector.w * tm->_30,
			vector.x * tm->_01 + vector.y * tm->_11 + vector.z * tm->_21 + vector.w * tm->_31,
			vector.x * tm->_02 + vector.y * tm->_12 + vector.z * tm->_22 + vector.w * tm->_32,
			vector.x * tm->_03 + vector.y * tm->_13 + vector.z * tm->_23 + vector.w * tm->_33
	       );
	/*
	return Vector4<T>(
			vector.x * tm->_00 + vector.y * tm->_01 + vector.z * tm->_02 + vector.w * tm->_03,
			vector.x * tm->_10 + vector.y * tm->_11 + vector.z * tm->_12 + vector.w * tm->_13,
			vector.x * tm->_20 + vector.y * tm->_21 + vector.z * tm->_22 + vector.w * tm->_23,
			vector.x * tm->_30 + vector.y * tm->_31 + vector.z * tm->_32 + vector.w * tm->_33
	       );
	       */
}

template <typename T>
void Matrix4<T>::PrintContents()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::printf("%f:", data.asArray2D[i][j]);

		std::printf("\n");
	}
}
