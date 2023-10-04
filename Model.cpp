#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Model.h"

//构造函数，输入参数是.obj文件路径
Model::Model(const char* filename) : verts_(), faces_() 
{
    std::ifstream in;
    in.open(filename, std::ifstream::in);           //打开.obj文件
    if (in.fail()) return;
    string line;
    while (!in.eof())                               //没有到文件末尾的话
    {
        getline(in, line);                          //读入一行
        istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v "))              //顶点坐标
        {
            iss >> trash;
            Vector3 v;                              
            iss >> v.x >> v.y >> v.z;
            verts_.push_back(v);                   
        }
        //else if (!line.compare(0, 3, "vt "))        //纹理坐标
        //{
        //    iss >> trash >> trash;
        //    Vector2 uv;
        //    iss >> uv.x >> uv.y;
        //    uv_.push_back(uv);
        //}
        //else if (!line.compare(0, 3, "vn "))        //法线
        //{
        //    iss >> trash >> trash;
        //    Vector3 normal;
        //    iss >> normal.x >> normal.y >> normal.z;
        //    norms_.push_back(normal);
        //}
        else if (!line.compare(0, 2, "f "))         //三角形面片数据
        {
            vector<int> f;
            int itrash, idx;                        //idx是顶点索引，itrash用来读我们暂时用不到的纹理坐标和法线向量
            iss >> trash;
            while (iss >> idx >> trash >> itrash >> trash >> itrash) //读取x/x/x格式
            {
                idx--;                              // in wavefront obj all indices start at 1, not zero
                f.push_back(idx);                   //加入该三角形面片的顶点集
            }
            faces_.push_back(f);                    //把该面片加入模型的三角形面片集
        }
    }
    std::cerr << "# v# " << verts_.size() << " f# " << faces_.size() << std::endl;//输出顶点与面片数量
    //loadTexture(filename, "_diffuse.tga", diffuseMap_);
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


//void Model::loadTexture(string filename, const char* suffix, TGAImage& image)
//{
//    string texfile(filename);
//    size_t dot = texfile.find_last_of(".");
//    if (dot != string::npos) {
//        texfile = texfile.substr(0, dot) + string(suffix);
//        cerr << "texture file " << texfile << " loading " << (image.read_tga_file(texfile.c_str()) ? "ok" : "failed") << std::endl;
//        image.flip_vertically();
//    }
//}
//Vector2 Model::uv(int iface, int nvert)
//{
//    int idx = faces_[iface][nvert]; 
//    return Vector2(uv_[idx].x * diffuseMap_.width(), uv_[idx].y * diffuseMap_.height());
//}
//TGAColor Model::diffuse(Vector2 uv)
//{
//    return diffuseMap_.get(uv.x, uv.y);
//}