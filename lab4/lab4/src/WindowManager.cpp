#include "../include/WindowManager.h"
#include "../include/CCanvas.h"
#include <SFML/Graphics.hpp>

WindowManager::WindowManager(int width, int height, const std::string& title)
{
	m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title);
	m_canvas = std::make_shared<CCanvas>(m_window);
}

void WindowManager::Run(ShapeManager& shapeManager)
{
	auto shapes = shapeManager.GetShapes();
	while (m_window->isOpen())
	{
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window->close();
			}
		}

		m_window->clear(sf::Color::White);
		for (const auto& shape : shapes)
		{
			shape->Draw(m_canvas);
		}
		m_window->display();
	}
}


