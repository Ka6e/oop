#pragma once
#include "../include/ShapeManager.h"
#include <SFML/Graphics/RenderWindow.hpp>

class WindowManager
{
public:
	WindowManager(int width, int height, const std::string& title);
	void Run(ShapeManager& shapeManager);
private:
	std::shared_ptr<sf::RenderWindow> m_window;
	std::shared_ptr<ICanvas> m_canvas;
};