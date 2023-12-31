#ifndef __MODEL_H__
#define __MODEL_H__

#include"Gmath.h"
#include<vector>

class Model
{
private:
	vector<Vector3> verts_;						//顶点个数
	vector<vector<int>> faces_;					//三角形数
	vector<Vector3> norms_;						//法线
public:
	Model(const char*);							//根据文件导入模型
	~Model();	
	int nVerts();								//返回顶点个数
	int nFaces();								//返回三角形数
	Vector3 vert(int i);						//返回第i个顶点
	vector<int> face(int idx);					//返回第i个三角形
};

#endif 
