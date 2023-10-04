#ifndef __MODEL_H__
#define __MODEL_H__

#include"Gmath.h"
#include"tgaimage.h"
#include<vector>

class Model
{
private:
	vector<Vector3> verts_;						//�������
	vector<vector<int>> faces_;					//��������
	vector<Vector3> norms_;						//����
	//vector<Vector2> uv_;						//������
	//TGAImage diffuseMap_;						//������ͼ
	//void loadTexture(string filename, const char* suffix, TGAImage& image);		//��������

public:
	Model(const char*);							//�����ļ�����ģ��
	~Model();	
	int nVerts();								//���ض������
	int nFaces();								//������������
	Vector3 vert(int i);						//���ص�i������
	vector<int> face(int idx);					//���ص�i��������
	//Vector2 uv(int iface, int nvert);			
	//TGAColor diffuse(Vector2 uv);
};

#endif 
