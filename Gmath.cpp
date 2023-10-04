#include"Gmath.h"	


Vector4 Vector4::operator+(const Vector4& v)
{
	return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
}
Vector4 Vector4::operator-(const Vector4& v)
{
	return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
}
float Vector4::operator*(const Vector4& v)
{
	return x * v.x + y * v.y + z * v.z + w * v.w;
}
Vector4 Vector4::operator*(float a)
{
	return Vector4(a * x, a * y, a * z, a * w);
}
float Vector4::normal()
{
	return sqrt(x * x + y * y + z * z + w * w);
}
Vector4 Vector4::normalize()
{
	float length = normal();
	return Vector4(x /= length, y /= length, z /= length, w / length);
}

Vector3 Vector3::operator+(const Vector3& v)		//加法
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}
Vector3 Vector3::operator-(const Vector3& v)		//减法
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}
float Vector3::operator*(const Vector3& v)		//两个向量乘法
{
	return x * v.x + y * v.y + z * v.z;
}
Vector3 Vector3::operator^(const Vector3& v)
{
	return Vector3((y * v.z - z * v.y), (z * v.x - x * v.z), (x * v.y - y * v.x));
}
Vector3 Vector3::operator*(float a)
{
	return Vector3(a * x, a * y, a * z);
}
Vector3 Vector3::operator/(float a)		//除法
{
	return Vector3(x / a, y / a, z / a);

}
bool Vector3::operator==(const  Vector3& v)		//判断向量是否相等
{
	return ((x == v.x) && (y == v.y) && (z == v.z));
}
bool Vector3::operator!=(const Vector3& v)
{
	return ((x != v.x) || (y != v.y) || (z != v.z));
}
Vector3 Lerp(const Vector3& from, const Vector3& to, float t)
{
	return Vector3((to.x-from.x)*t+from.x, (to.y - from.y) * t + from.y,
		(to.z - from.z) * t + from.z);
}
float Vector3::normal()
{
	return sqrt(x * x + y * y + z * z);
}
Vector3 Vector3::normalize()
{
    float length = normal();
	return Vector3(x /= length, y /= length, z /= length);
}
//Vector3* MultplyMatrix(float TT[4][4], Vector3& v3, int v3number)
//{
//	
//}

Vector2 Vector2::operator+(const Vector2& v)
{
	return Vector2(x + v.x, y + v.y);
}
Vector2 Vector2::operator-(const Vector2& v)
{
	return Vector2(x - v.x, y - v.y);
}
Vector2 Vector2::operator*(float n) 
{
	return Vector2(x * n, y * n);
}

int Matrix::nrows()
{
	return rows;
}
int Matrix::ncols()
{
	return cols;
}
Matrix::Matrix(int r, int c) : rows(r), cols(c) 
{
	m = vector<vector<float>>(r, vector<float>(c, 0.0f));		//r行c列
}
Matrix Matrix::identity(int dimensions)							//dimensions维度
{
	Matrix E(dimensions, dimensions);
	for (int i = 0; i < dimensions; i++)
		for (int j = 0; j < dimensions; j++)
			E[i][j] = (i == j ? 1.0f : 0.0f);
	return E;
}
vector<float>& Matrix::operator[](const int i)
{
	assert(i >= 0 && i < rows);
	return m[i];
}
Matrix Matrix::operator*(const Matrix& a)
{
	assert(cols == a.rows);			//左列=右行
	Matrix ans(rows, a.cols);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < a.cols; j++)
			for (int k = 0; k < cols; k++)
				ans[i][j] += m[i][k] * a.m[k][j];
	return ans;
}
Matrix Matrix::transpose()
{
	Matrix ans(cols, rows);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			ans[i][j] = m[j][i];
	return ans;
}
//Matrix Matrix::inverse()
//{
//
//}
//ostream& operator<<(std::ostream& s, Matrix& m)
//{
//
//}







