#include"Gmath.h"
#include"Model.h"

Vector3 light_dir(0., 0., -1.f);									//垂直光源
Vector3 cameraPos(0, 0, 3);											//相机位置
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void Triangle(HDC, Vector3*, COLORREF); 							//三角形
void TriangleFace(HDC hdc, float*, Vector3* a, COLORREF color);		//三角形面
Vector3 baryCentric(Vector3*, Vector3);								//三角形重心
Vector3 world2screen(Vector3);										//世界坐标转换屏幕坐标
Matrix local2homo(Vector3);											//坐标转换为齐次坐标
Matrix modelMatrix();												//模型变换矩阵
Matrix viewMatrix();												//视图变换矩阵
Matrix projectionMatrix();											//投影变换矩阵
Matrix projectionDivision(Matrix);									//透视除法
Matrix viewportMatrix(int, int, int, int);							//视口变换矩阵
Vector3 homo2vertices(Matrix m);									//齐次坐标恢复三维坐标

int WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance,LPSTR lpCmdline, int nCmdShow)
{
	static TCHAR szAppName[] = TEXT("HSTK");
	HWND hwnd;				//窗口句柄
	MSG msg;				//消息结构
	WNDCLASS wndclass;		//窗口类

	//窗口类初始化
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = NULL;
	wndclass.hCursor = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	//注册窗口
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This progrma requires Windows NOT !"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	// 创建窗口并获取窗口句柄
	hwnd = CreateWindow(szAppName,		// window class name
		TEXT("Graphic"),				// window caption(标题)
		WS_OVERLAPPEDWINDOW,			// window style
		CW_USEDEFAULT,					// initial x position
		CW_USEDEFAULT,					// initial y position
		Width,							// initial x size
		Height,							// initial y size
		NULL,							// parent window handle
		NULL,							// window menu handle
		hInstance,						// program instance handle
		NULL);							// crea
	//显示窗口并更新
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	//消息处理
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		//Vector3 a[3] = { Vector3(10, 70, 0),   Vector3(50, 160,0),   Vector3(70, 80,  0) };
		//Vector3 b[3] = { Vector3(180, 50, 0),  Vector3(150, 10,0),   Vector3(70, 180, 0) };
		//Vector3 c[3] = { Vector3(180, 150, 0), Vector3(120, 160,0),  Vector3(130,180, 0) };
		//Triangle(hdc, a, white);
		//Triangle(hdc, b, red);
		//Triangle(hdc, c, green);

		float* zBuffer = new float[Width * Height];
		for (int i = 0; i < Width * Height; i++)
			zBuffer[i] = -9999;

		Matrix model_ = modelMatrix();
		Matrix view_ = viewMatrix();
		Matrix projection_ = projectionMatrix();
		Matrix viewport_ = viewportMatrix(Width / 8, Height / 8, Width * 3 / 4, Height * 3 / 4);

		Model* model = new Model("D:\\C-CODE\\Visual Studio 2022\\C Graphics\\C Graphics\\obj\\african_head\\african_head.obj");
		for (int i = 0; i < model->nFaces(); i++)
		{
			vector<int> face = model->face(i);				//获取模型的第i个面片
			Vector3 screenCoords[3];						//屏幕坐标
			Vector3 worldCoords[3];							//世界坐标
			for (int j = 0; j < 3; j++)
			{
				worldCoords[j] = model->vert(face[j]);		
				screenCoords[j] = homo2vertices(viewport_ * projectionDivision(projection_ * view_ * model_ * local2homo(worldCoords[j])));
			}
			//法线
			Vector3 normal = (worldCoords[0] - worldCoords[1]) ^ (worldCoords[2] - worldCoords[1]);
			normal.normalize();
			float intensity = normal * light_dir;
			//Triangle(hdc,  screenCoords, white);
			if (intensity > 0)
				TriangleFace(hdc, zBuffer, screenCoords, RGB(255 * intensity, 255 * intensity, 255 * intensity));

			//RGB(rand() % 256, rand() % 256, rand() % 256)
		}

		EndPaint(hwnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

Vector3 baryCentric(Vector3* pts, Vector3 p)
{
	float xa = pts[0].x;
	float ya = pts[0].y;	
	float xb = pts[1].x;	
	float yb = pts[1].y;	
	float xc = pts[2].x;	
	float yc = pts[2].y;	
	float x = p.x;			
	float y = p.y;			
	float gamma = (float)((ya - yb) * x + (xb - xa) * y + xa * yb - xb * ya) / (float)((ya - yb) * xc + (xb - xa) * yc + xa * yb - xb * ya);
	float beta = (float)((ya - yc) * x + (xc - xa) * y + xa * yc - xc * ya) / (float)((ya - yc) * xb + (xc - xa) * yb + xa * yc - xc * ya);
	float alpha = 1 - gamma - beta;	
	return Vector3(alpha, beta, gamma);
}
void drawLineDDA(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	float xIncre = (float)dx / (float)steps;
	float yIncre = (float)dy / (float)steps;
	float x = x1, y = y1;
	for (int i = 0; i <= steps; i++)
	{
		SetPixel(hdc, round(x), round(y), color);
		x += xIncre;
		y += yIncre;
	}
}
void Triangle(HDC hdc, Vector3* a, COLORREF color)
{
	if (a[0].y > a[1].y)
		swap(a[0], a[1]);
	if (a[0].y > a[2].y)
		swap(a[0], a[2]);
	if (a[1].y > a[2].y)
		swap(a[1], a[2]);

	//上下对称反转
	//float centerY = (a[0].y + a[1].y + a[2].y) / 3;
	//a[0].y = 2 * centerY - a[0].y;
	//a[1].y = 2 * centerY - a[1].y;
	//a[2].y = 2 * centerY - a[2].y;

	a[0].y = 600 - a[0].y;
	a[1].y = 600 - a[1].y;
	a[2].y = 600 - a[2].y;

	drawLineDDA(hdc, a[0].x, a[0].y, a[1].x, a[1].y, color);
	drawLineDDA(hdc, a[1].x, a[1].y, a[2].x, a[2].y, color);
	drawLineDDA(hdc, a[2].x, a[2].y, a[0].x, a[0].y, color);
	
	//填充
	//int total_height = a[2].y - a[0].y;
	//for (int i = a[0].y; i <= a[1].y; i++)		//上半部分
	//{
	//	int seg_height = a[1].y - a[0].y + 1;
	//	float k1 = (float)(i - a[0].y) / total_height;
	//	float k2 = (float)(i - a[0].y) / seg_height;
	//	Vector2 v1 = a[0] + (a[2] - a[0]) * k1;
	//	Vector2 v2 = a[0] + (a[1] - a[0]) * k2;
	//	if (v1.x > v2.x)swap(v1, v2);
	//	for (int j = v1.x; j <= v2.x; j++)
	//		SetPixel(hdc, j, i, color);
	//}
	//for (int i = a[1].y; i <= a[2].y; i++)		//下半部分
	//{
	//	int seg_height = a[2].y - a[1].y + 1;
	//	float k1 = (float)(i - a[0].y) / total_height;
	//	float k2 = (float)(i - a[1].y) / seg_height;
	//	Vector2 v1 = a[0] + (a[2] - a[0]) * k1;
	//	Vector2 v2 = a[1] + (a[2] - a[1]) * k2;
	//	if (v1.x > v2.x)swap(v1, v2);
	//	for (int j = v1.x; j <= v2.x; j++)
	//		SetPixel(hdc, j, i, color);
	//}
}
void TriangleFace(HDC hdc, float* zBuffer, Vector3* a, COLORREF color)
{
	a[0].y = Height - a[0].y;
	a[1].y = Height - a[1].y;
	a[2].y = Height - a[2].y;
	Vector2 bboxmin(Width, Height), bboxmax(0, 0);
	bboxmin.x = min(bboxmin.x, min(a[0].x, min(a[1].x, a[2].x)));
	bboxmin.y = min(bboxmin.y, min(a[0].y, min(a[1].y, a[2].y)));
	bboxmax.x = max(bboxmax.x, max(a[0].x, max(a[1].x, a[2].x)));
	bboxmax.y = max(bboxmax.y, max(a[0].y, max(a[1].y, a[2].y)));

	int min_x = (int)floor(bboxmin.x);		//向下取整
	int min_y = (int)floor(bboxmin.y);
	int max_x = (int)ceil(bboxmax.x);		//向上取整
	int max_y = (int)ceil(bboxmax.y);
							
	for (int i = min_x; i <= max_x; i++)
	{
		for (int j = min_y; j <= max_y; j++)
		{	
			Vector3 p(i, j, 0);
			Vector3 barycoord = baryCentric(a, p);
			if (barycoord.x < -0.01 || barycoord.y < -0.01 || barycoord.z < -0.01)	//不在三角形内
				continue;
			float z_interpolation = barycoord.x * a[0].z + barycoord.y * a[1].z + barycoord.z * a[2].z;
			//该像素点的z值
			if (z_interpolation > zBuffer[i + j * Width])
			{
				zBuffer[i + j * Width] = z_interpolation;
				SetPixel(hdc, i, j, color);
			}
		}
	}
}
Vector3 world2screen(Vector3 v)
{
	return Vector3(int((v.x + 1.) * Width / 2. + .5), int((v.y + 1.) * Height / 2. + .5), v.z);
}
Matrix local2homo(Vector3 v)
{
	Matrix m(4, 1);
	m[0][0] = v.x;
	m[1][0] = v.y;
	m[2][0] = v.z;
	m[3][0] = 1.0f;
	return m;
}
Matrix modelMatrix()
{
	return Matrix::identity(4);
}
Matrix viewMatrix()
{
	return Matrix::identity(4);
}
Matrix projectionMatrix()
{
	Matrix projection = Matrix::identity(4);
	projection[3][2] = -1.f / cameraPos.z;
	return Matrix::identity(4);
}
Matrix projectionDivision(Matrix m)
{
	m[0][0] = m[0][0] / m[3][0];
	m[1][0] = m[1][0] / m[3][0];
	m[2][0] = m[2][0] / m[3][0];
	m[3][0] = 1.0f;
	return m;
}
Matrix viewportMatrix(int x,int y,int w,int h)
{
	Matrix m = Matrix::identity(4);
	m[0][3] = x + w / 2.f;
	m[1][3] = y + h / 2.f;
	m[2][3] = depth / 2.f;
	m[0][0] = w / 2.f;
	m[1][1] = h / 2.f;
	m[2][2] = depth / 2.f;
	return m;
}
Vector3 homo2vertices(Matrix m)
{
	return Vector3(m[0][0], m[1][0], m[2][0]);
}



