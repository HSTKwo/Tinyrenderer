#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#pragma warning(disable:4996)
#include<iostream>
#include<algorithm>
#include <windows.h>
#include <vector>
#include<assert.h>
using namespace std;

#define white RGB(255,255,255)
#define black RGB(0,0,0)
#define red RGB(255,0,0)
#define yellow RGB(255,255,0)
#define green RGB(0,255,128)
#define blue RGB(0,255,255)
#define Width 600		//��Ļ���
#define Height 600		//��Ļ�߶�
#define depth 255		//���

//��ά����
class Vector2
{
public:
	float x, y;
	Vector2() :x(0), y(0) {};
	Vector2(float a, float b)
	{
		x = a;
		y = b;
	}
	Vector2 operator=(const Vector2& v1)
	{
		this->x = v1.x;
		this->y = v1.y;
		return *this;
	}
	float operator[](const int idx)
	{
		if (idx <= 0)
			return x;
		else
			return y;
	}
	Vector2 operator +(const Vector2&);
	Vector2 operator -(const Vector2&);
	Vector2 operator *(float);
};

//��ά����
class Vector3
{
public:
	float x, y, z;
	Vector3(float a, float b, float c)
	{
		x = a;
		y = b;
		z = c;
	}
	Vector3()
	{
		x = y = z = 0;
	}
	Vector3 operator=(const Vector3& v1)
	{
		this->x = v1.x;
		this->y = v1.y;
		this->z = v1.z;
		return *this;
	}
	float operator[](const int idx)
	{
		if (idx <= 0)
			return x;
		else if (idx == 1)
			return y;
		else
			return z;
	}
	float operator*(const Vector3&);			//���
	Vector3 operator^(const Vector3&);			//���
	Vector3 operator+(const Vector3&);			//�ӷ�
	Vector3 operator-(const Vector3&);			//����
	Vector3 operator*(float);					//��������				
	Vector3 operator/(float);					//����
	bool operator==(const  Vector3&);			//�ж������Ƿ����
	bool operator!=(const  Vector3&);
	Vector3 Lerp(const Vector3&, const  Vector3&, float);	//���Բ�ֵ
	float normal();											//ģ��
	Vector3 normalize();												//��λ��
	//friend Vector3* MultplyMatrix(float TT[4][4], Vector3& v3, int v3number);
};

//��ά����
class Vector4
{
public:
	float x, y, z, w;
	Vector4(float a, float b, float c,float d)
	{
		x = a;
		y = b;
		z = c;
		w = d;
	}
	Vector4()
	{
		x = y = z = w = 0;
	}
	Vector4 operator=(const Vector4& v1)
	{
		this->x = v1.x;
		this->y = v1.y;
		this->z = v1.z;
		this->w = v1.w;
		return *this;
	}
	float operator[](const int idx)
	{
		if (idx <= 0)
			return x;
		else if (idx == 1)
			return y;
		else if (idx == 2)
			return z;
		else
			return w;
	}
	Vector4 operator+(const Vector4&);			//�ӷ�
	Vector4 operator-(const Vector4&);			//����
	float operator*(const Vector4&);			//���
	Vector4 operator*(float);					//����				
	float normal();								//ģ��
	Vector4 normalize();						//��λ��
};

//����
class Matrix
{
private:
	vector<vector<float>> m;
	int rows, cols;
public:
	Matrix(int, int);
	int nrows();
	int ncols();
	static Matrix identity(int);							//���ص�λ����
	vector<float>& operator[](const int);					//���ʵ�i��
	Matrix operator*(const Matrix&); 						//����˷�
	Matrix transpose();										//ת��
};



#endif 