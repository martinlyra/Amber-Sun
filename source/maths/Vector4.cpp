#include <math.h>

#include "Vector4.h"

#include "meta.h"

TEMPLATE_IMPLEMENT_MATHEMATICAL_TYPES( Vector4 );

template<typename T>
Vector4<T>::Vector4()
	: x( 0 ), y( 0 ), z( 0 ), w( 0 )
{
}

template<typename T>
Vector4<T>::Vector4( T x, T y, T z, T w )
	: x( x ), y( y ), z( z ), w( w )
{
}

template<typename T>
Vector4<T>::~Vector4()
{
}

template<typename T>
Vector4< T > Vector4<T>::Cross(Vector4< T >& other) const
{
	return Vector4<T>(
		(this->y * other.z) - (this->z * other.y),
		(this->z * other.x) - (this->x * other.z),
		(this->x * other.y) - (this->y * other.x),
		0
	);
}

template <typename T>
double Vector4<T>::Dot(Vector4< T >& other) const
{
	return ( this-> x * other.x + this->y * other.y + this->z * other.z);
}

template <typename T>
double Vector4<T>::LengthSquared() const
{
	return ( pow(x,2) + pow(y,2) + pow(z,2) );
}

template <typename T>
double Vector4<T>::Length() const
{
	return sqrt(LengthSquared());
}

template <typename T>
void Vector4<T>::Normalize()
{
	const double factor = 1.0f / Length();
	
	this->x *= factor;
	this->y *= factor;
	this->z *= factor;
}

template <typename T>
Vector4< T > Vector4<T>::Normalized() const
{
	auto v = (*this);
	v.Normalize();
	return v;
}

template<typename T>
bool Vector4<T>::IsPosition() const
{
	return w == 1;
}

template<typename T>
bool Vector4<T>::IsDirection() const
{
	return !IsPosition();
}

/*
template <typename T>
Vector4< T > Vector4<T>::operator*(const Matrix4< T >& matrix) const
{
	//auto tm = &matrix.data.asMatrix;
	return matrix * (*this);
}*/

template <typename T>
Vector4< T > Vector4<T>::operator-(const Vector4< T >& other) const
{
	return Vector4<T>(
		this->x - other.x,
		this->y - other.y,
		this->z - other.z,
		this->w
	);
}
