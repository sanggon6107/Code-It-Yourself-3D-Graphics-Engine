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

// 다양한 행렬 연산을 위해 4x4 매트릭스 구조체를 만든다.
struct Mat4x4
{
	float m_[4][4]{ 0 };
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
		mesh_cube_.tris_ = 
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


		// Projection Matrix
		float f_near = 0.1f;
		float f_far = 1000.0f;
		float f_fov = 90.0f;
		float f_aspect_ratio = static_cast<float>(ScreenHeight()) / static_cast<float>(ScreenWidth()); // 스크린의 (h/w) 를 x좌표에 곱하여 x, y 스케일을 맞춰준다.
		float f_fov_rad = 1.0f / tanf(f_fov * 0.5f / 180.0f * 3.14159f);  // fov에 따라 x, y의 화면상 스케일을 조절해야한다. 즉, fov가 넓어질 수록 화면상 물체는 작게 표현된다.

		mat_proj_.m_[0][0] = f_aspect_ratio * f_fov_rad;
		mat_proj_.m_[1][1] = f_fov_rad;
		mat_proj_.m_[2][2] = f_far / (f_far / f_near);
		mat_proj_.m_[3][2] = (-f_far * f_near) / (f_far - f_near);
		mat_proj_.m_[2][3] = 1.0f;
		mat_proj_.m_[3][3] = 0.0f;
		
		

		return true;
	}

	bool OnUserUpdate(float elapsed_time) override
	{

		// clear the screen.
		Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

		// draw Triangles.
		// The optical center (0, 0) is the center of the screen.
		for (auto tri : mesh_cube_.tris_)
		{
			Triangle tri_projected;
			
			Triangle tri_translated{ tri };
			tri_translated.p_[0].z_ = tri.p_[0].z_ + 3.0f;
			tri_translated.p_[1].z_ = tri.p_[1].z_ + 3.0f;
			tri_translated.p_[2].z_ = tri.p_[2].z_ + 3.0f;


			MultiplyMatrixVector(tri_translated.p_[0], tri_projected.p_[0], mat_proj_);
			MultiplyMatrixVector(tri_translated.p_[1], tri_projected.p_[1], mat_proj_);
			MultiplyMatrixVector(tri_translated.p_[2], tri_projected.p_[2], mat_proj_);
			
			// Scale into view
			tri_projected.p_[0].x_ += 1.0f; tri_projected.p_[0].y_ += 1.0f;
			tri_projected.p_[1].x_ += 1.0f; tri_projected.p_[1].y_ += 1.0f;
			tri_projected.p_[2].x_ += 1.0f; tri_projected.p_[2].y_ += 1.0f;

			
			tri_projected.p_[0].x_ *= 0.5f * (float)ScreenWidth();
			tri_projected.p_[1].x_ *= 0.5f * (float)ScreenWidth();
			tri_projected.p_[2].x_ *= 0.5f * (float)ScreenWidth();

			tri_projected.p_[0].y_ *= 0.5f * (float)ScreenHeight();
			tri_projected.p_[1].y_ *= 0.5f * (float)ScreenHeight();
			tri_projected.p_[2].y_ *= 0.5f * (float)ScreenHeight();


			// Draw a triangle( using olcConsoleGameEngine )
			DrawTriangle(tri_projected.p_[0].x_, tri_projected.p_[0].y_,
				tri_projected.p_[1].x_, tri_projected.p_[1].y_,
				tri_projected.p_[2].x_, tri_projected.p_[2].y_,
				PIXEL_SOLID, FG_WHITE);

		}

		return true;
	}

private :
	Mesh mesh_cube_;
	Mat4x4 mat_proj_;


	void MultiplyMatrixVector(Vec3d& i, Vec3d& o, Mat4x4& m)
	{
		o.x_ = i.x_ * m.m_[0][0] + i.y_ * m.m_[1][0] + i.z_ * m.m_[2][0] + m.m_[3][0];
		o.y_ = i.x_ * m.m_[0][1] + i.y_ * m.m_[1][1] + i.z_ * m.m_[2][1] + m.m_[3][1];
		o.z_ = i.x_ * m.m_[0][2] + i.y_ * m.m_[1][2] + i.z_ * m.m_[2][2] + m.m_[3][2];
		float w = i.x_ * m.m_[0][3] + i.y_ * m.m_[1][3] + i.z_ * m.m_[2][3] + m.m_[3][3];
		
		if (w != 0.0f)
		{
			o.x_ /= w;   o.y_ /= w;   o.z_ /= w;
		}
	}
};



int main()
{

	olcEngine3D demo;
	if (demo.ConstructConsole(256, 215, 4, 4))
	{
		demo.Start();
	}

}