#include "../include/CCanvas.h"
#include <SFML/Graphics.hpp>

CCanvas::CCanvas(std::shared_ptr<sf::RenderWindow> window)
	: m_window(window)
{
}

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor)
{
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(from.x, from.y), GetColor(lineColor)),
		sf::Vertex(sf::Vector2f(to.x, to.y), GetColor(lineColor))
	};
	m_window->draw(line, 2, sf::Lines);
}

void CCanvas::FillPolygon(std::vector<CPoint> points, uint32_t fillColor)
{
	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());
	for (size_t i = 0; i < points.size(); ++i)
	{
		polygon.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
	}
	polygon.setFillColor(GetColor(fillColor));
	m_window->draw(polygon);
}

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor)
{
	sf::CircleShape circle(radius);
	circle.setPosition(center.x - radius, center.y - radius);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(GetColor(lineColor));
	circle.setOutlineThickness(1);
	m_window->draw(circle);
}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor)
{
	sf::CircleShape circle(radius);
	circle.setPosition(center.x - radius, center.y - radius);
	circle.setFillColor(GetColor(fillColor));
	m_window->draw(circle);
}

sf::Color CCanvas::GetColor(uint32_t color)
{
	return sf::Color(
		(color >> 16) & 0xFF,
		(color >> 8) & 0xFF,
		color & 0xFF,
		255
	);
}
