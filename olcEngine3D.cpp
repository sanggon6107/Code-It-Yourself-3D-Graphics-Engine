#include "olcConsoleGameEngine.h"
#include <iostream>
// #include <vector>

using namespace std;

struct Vec3d
{
	float x_, y_, z_;
};

// 삼각형은 3개의 벡터로 이루어져 있다.
struct Triangle
{
	Vec3d p_[3];
};

struct Mesh
{
	// 삼각형은 3D 이미지를 표현하기 가장 적합한 도형이기 때문에 3D 이미지는 삼각형들이 이어진 Mesh 형태로 구현된다.
	vector<Triangle> tris_;
};


class olcEngine3D : public olcConsoleGameEngine
{
public :
	olcEngine3D()
	{
		m_sAppName = L"3D Demo"; // enable Unicode.
	}

	bool OnUserCreate() override
	{
		// Unit Cube를 생성한다.
		MeshCube_.tris_ = 
		{
			// x방향은 화면상 오른쪽, y방향은 화면상 위쪽, z방향은 화면상 안쪽이다.
			// south
			{ 0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f },

			// east
			{ 1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f, 1.0f },
			{ 1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, 1.0f },

			// north
			{ 1.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 1.0f },
			{ 1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 1.0f,   0.0f, 0.0f, 1.0f },

			// west
			{ 0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f, 0.0f },

			// top
			{ 0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 1.0f,   1.0f, 1.0f, 1.0f }, 
			{ 0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, 0.0f },

			// bottom
			{1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f },
			{1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f }
		
		};

		return true;
	}

	bool OnUserUpdate(float elapsed_time) override
	{

		// clear the screen.
		Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

		// draw Triangles.
		for (auto tri : MeshCube_.tris_)
		{

		}

		return true;
	}

private :
	Mesh MeshCube_;

};



int main()
{


	olcEngine3D demo;
	if (demo.ConstructConsole(256, 240, 4, 4))
	{
		demo.Start();
	}
}