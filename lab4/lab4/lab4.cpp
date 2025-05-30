#include "include/ShapeManager.h"
#include "include/CCanvas.h"
#include <string>
#include <iostream>
#include "include/WindowManager.h"

int main(int argc, char** argv)
{
	try
	{
		ShapeManager manager;

		if (argc > 1)
		{
			manager.ReadShape(argv[1]);
		}
		else
		{
			manager.ReadShape(std::cin);
		}
		manager.PrintMaxAreaShape();
		manager.PrintMinPerimeterShape();
		
		WindowManager window(800, 600, "Geometric shapes");
		window.Run(manager);
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	return 0;
}

