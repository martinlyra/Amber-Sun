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
bool Vector4<T>::IsPosition()
{
	return w == 1;
}

template<typename T>
bool Vector4<T>::IsDirection()
{
	return !IsPosition();
}
