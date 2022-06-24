#include "olcConsoleGameEngine.h"
#include <iostream>




class olcEngine3D : public olcConsoleGameEngine
{
public :
	olcEngine3D()
	{
		m_sAppName = L"3D Demo"; // enable Unicode.
	}

	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float elapsed_time) override
	{
		return true;
	}
};



int main()
{


	olcEngine3D demo;
	if (demo.ConstructConsole(256, 240, 4, 4))
	{
		demo.Start();
	}
}