#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Model.h"

//���캯�������������.obj�ļ�·��
Model::Model(const char* filename) : verts_(), faces_() 
{
    std::ifstream in;
    in.open(filename, std::ifstream::in);           //��.obj�ļ�
    if (in.fail()) return;
    string line;
    while (!in.eof())                               //û�е��ļ�ĩβ�Ļ�
    {
        getline(in, line);                          //����һ��
        istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v "))              //��������
        {
            iss >> trash;
            Vector3 v;                              
            iss >> v.x >> v.y >> v.z;
            verts_.push_back(v);                   
        }
        else if (!line.compare(0, 2, "f "))         //��������Ƭ����
        {
            vector<int> f;
            int itrash, idx;                        //idx�Ƕ���������itrash������������ʱ�ò�������������ͷ�������
            iss >> trash;
            while (iss >> idx >> trash >> itrash >> trash >> itrash) //��ȡx/x/x��ʽ
            {
                idx--;                              // in wavefront obj all indices start at 1, not zero
                f.push_back(idx);                   //�������������Ƭ�Ķ��㼯
            }
            faces_.push_back(f);                    //�Ѹ���Ƭ����ģ�͵���������Ƭ��
        }
    }
    std::cerr << "# v# " << verts_.size() << " f# " << faces_.size() << std::endl;//�����������Ƭ����
}
Model::~Model() 
{
}
int Model::nVerts() 
{
    return (int)verts_.size();
}
int Model::nFaces() 
{
    return (int)faces_.size();
}
vector<int> Model::face(int idx) 
{
    return faces_[idx];
}
Vector3 Model::vert(int i) 
{
    return verts_[i];
}

