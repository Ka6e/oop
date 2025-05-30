#pragma once
#include "../include/ICanvas.h"
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

class CCanvas : public ICanvas
{
public:
	CCanvas(std::shared_ptr<sf::RenderWindow> window);
	void DrawLine(CPoint from, CPoint to, uint32_t lineColor) override;
	void FillPolygon(std::vector<CPoint> points, uint32_t fillColor) override;
	void DrawCircle(CPoint center, double radius, uint32_t lineColor) override;
	void FillCircle(CPoint center, double radius, uint32_t fillColor) override;
private:
	std::shared_ptr<sf::RenderWindow> m_window;
	sf::Color GetColor(uint32_t color);
};
