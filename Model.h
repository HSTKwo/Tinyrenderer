#ifndef __MODEL_H__
#define __MODEL_H__

#include"Gmath.h"
#include<vector>

class Model
{
private:
	vector<Vector3> verts_;						//�������
	vector<vector<int>> faces_;					//��������
	vector<Vector3> norms_;						//����
public:
	Model(const char*);							//�����ļ�����ģ��
	~Model();	
	int nVerts();								//���ض������
	int nFaces();								//������������
	Vector3 vert(int i);						//���ص�i������
	vector<int> face(int idx);					//���ص�i��������
};

#endif 
