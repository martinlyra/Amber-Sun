#ifndef MATRIX4_H
#define MATRIX4_H

#include "Vector4.h"

template <typename T>
class Vector4;

template <typename T>
class Matrix4
{
private:
	friend Vector4<T>;
	
	union MatrixData {
		/*
		 * o ---> Y
		 * |
		 * |
		 * v
		 * X
		 */
		struct MatrixDataStruct {
			T _00, _01, _02, _03;
			T _10, _11, _12, _13;
			T _20, _21, _22, _23;
			T _30, _31, _32, _33;
		} asMatrix;
		T asArray[4*4]; // 16
		T asArray2D[4][4];
	} data;
	
public:
	Matrix4() {};
	
	Matrix4(T _00, T _01, T _02, T _03,
		T _10, T _11, T _12, T _13,
		T _20, T _21, T _22, T _23,
		T _30, T _31, T _32, T _33
	);
	
	static Matrix4<T> LookAlong(Vector4<T> eyePosition, Vector4<T> direction, Vector4<T> up);
	static Matrix4<T> LookAt(const Vector4<T> eyePosition, const Vector4<T> targetPosition, const Vector4<T> up);
	static Matrix4<T> Perspective(const T fov, const T ratio, const T zNear, const T zFar); 
	
	void Concatenate(const Matrix4<T>& other);
	
	void SetAsIdentity();
	void SetAsZero();
	void SetScaling(double x, double y, double z);
	
	void PrintContents();
	
	const T operator()(int x, int y) const;
	const T* operator[](int index) const;
	
	Matrix4<T> operator*(const Matrix4<T>& other) const;
	Matrix4<T> operator/(const Matrix4<T>& other) const;
	Matrix4<T> operator+(const Matrix4<T>& other) const;
	Matrix4<T> operator-(const Matrix4<T>& other) const;
	
	Matrix4<T> operator*=(const Matrix4<T>& other);
	Matrix4<T> operator/=(const Matrix4<T>& other);
	Matrix4<T> operator+=(const Matrix4<T>& other);
	Matrix4<T> operator-=(const Matrix4<T>& other);
	
	bool operator==(const Matrix4<T>& other) const;
	bool operator!=(const Matrix4<T>& other) const;
	
	Vector4<T> operator*(const Vector4<T>& vector) const;
};

#endif // MATRIX4_H
