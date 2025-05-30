#define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "../lab4/include/CRectangle.h" 
#include "../lab4/include/CLineSegment.h"
#include "../lab4/include/CCircle.h"
#include "../lab4/include/CTriangle.h"
#include "../lab4/include/ShapeFactory.h"
#include "../lab4/include/ShapeManager.h"
#include <sstream>
#include <numbers>

TEST_CASE("Testing line")
{
	GIVEN("A valid CLineSegment from(0, 0) to(3, 4) with red outline color")
	{
		CPoint startPoint(0.0, 0.0);
		CPoint endPoint(3.0, 4.0);
		uint32_t outlineColor = 0xFF0000;
		CLineSegment line(startPoint, endPoint, outlineColor);
		WHEN("We retrieve the start and end points")
		{
			THEN("They should match the input values")
			{
				CHECK(line.GetStartPoint().x == Approx(0.0));
				CHECK(line.GetStartPoint().y == Approx(0.0));
				CHECK(line.GetEndPoint().x == Approx(3.0));
				CHECK(line.GetEndPoint().y == Approx(4.0));
			}
		}
		WHEN("We retrieve the outline color")
		{
			THEN("It should match the provided outline color")
			{
				CHECK(line.GetOutlineColor() == outlineColor);
			}
		}

		WHEN("We compute the perimeter")
		{
			THEN("It should equal the distance between the points")
			{
				CHECK(line.GetPerimeter() == Approx(5.0));
			}
		}

		WHEN("We compute the area")
		{
			THEN("It should be zero for a line segment")
			{
				CHECK(line.GetArea() == Approx(0.0));
			}
		}
	}
	GIVEN("A degenerate CLineSegment with equal start and end points")
	{
		CPoint point(1.0, 1.0);
		uint32_t outlineColor = 0x00FF00;

		WHEN("The line segment is created with identical start and end points")
		{
			THEN("An exception is thrown")
			{
				CHECK_THROWS_AS(CLineSegment(point, point, outlineColor), std::invalid_argument);
			}
		}
	}
}

TEST_CASE("Testing circle")
{
	GIVEN("A circle with center at (5, 14) and radius 5")
	{
		CPoint center(5.0, 14.0);
		double radius = 5.0;
		uint32_t outlineColor = 0xFF0000;
		uint32_t fillColor = 0x00FF00;

		CCircle circle(center, radius, outlineColor, fillColor);

		WHEN("We retrieve the center and radius")
		{
			THEN("They should match the given values")
			{
				CHECK(circle.GetCenter().x == Approx(center.x));
				CHECK(circle.GetCenter().y == Approx(center.y));
				CHECK(circle.GetRadius() == Approx(radius));
			}
		}

		WHEN("We retrieve the colors")
		{
			THEN("They should match the given outline and fill colors")
			{
				CHECK(circle.GetOutlineColor() == outlineColor);
				CHECK(circle.GetFillColor() == fillColor);
			}
		}

		WHEN("We calculate the area")
		{
			THEN("It should match pi * r^2")
			{
				double expectedArea = std::numbers::pi * radius * radius; // 78.5398...
				CHECK(circle.GetArea() == Approx(expectedArea).epsilon(0.001));
			}
		}

		WHEN("We calculate the perimeter")
		{
			THEN("It should match 2 * pi * r")
			{
				double expectedPerimeter = 2 * std::numbers::pi * radius; // 31.4159...
				CHECK(circle.GetPerimeter() == Approx(expectedPerimeter).epsilon(0.001));
			}
		}
	}

	GIVEN("Invalid circle radius values")
	{
		CPoint center(0.0, 0.0);
		uint32_t outlineColor = 0xFF0000;
		uint32_t fillColor = 0x00FF00;

		WHEN("Radius is zero")
		{
			THEN("An exception should be thrown")
			{
				CHECK_THROWS_AS(CCircle(center, 0.0, outlineColor, fillColor), std::invalid_argument);
			}
		}

		WHEN("Radius is negative")
		{
			THEN("An exception should be thrown")
			{
				CHECK_THROWS_AS(CCircle(center, -1.0, outlineColor, fillColor), std::invalid_argument);
			}
		}
	}
}
TEST_CASE("Testing Triangle")
{
	GIVEN("A triangle with vertices (0,0), (2,0), (1,3)")
	{
		CPoint vertex1(0, 0);
		CPoint vertex2(2, 0);
		CPoint vertex3(1, 3);
		uint32_t outlineColor = 0xFF0000;
		uint32_t fillColor = 0x00FF00;
		CTriangle triangle(vertex1, vertex2, vertex3, outlineColor, fillColor);

		WHEN("We check vertices and colors")
		{
			THEN("They should match the input values")
			{
				CHECK(triangle.GetVertex1().x == Approx(vertex1.x));
				CHECK(triangle.GetVertex1().y == Approx(vertex1.y));
				CHECK(triangle.GetVertex2().x == Approx(vertex2.x));
				CHECK(triangle.GetVertex2().y == Approx(vertex2.y));
				CHECK(triangle.GetVertex3().x == Approx(vertex3.x));
				CHECK(triangle.GetVertex3().y == Approx(vertex3.y));
				CHECK(triangle.GetOutlineColor() == outlineColor);
				CHECK(triangle.GetFillColor() == fillColor);
			}
		}
		WHEN("We calculate the area")
		{
			THEN("It should be approximately 3.0")
			{
				double expectedArea = 3.0;
				CHECK(triangle.GetArea() == Approx(expectedArea).epsilon(0.001));
			}
		}
		WHEN("We calculate the perimeter")
		{
			THEN("It should be approximately 8.3246")
			{
				double expectedPerimeter = 8.3246;
				CHECK(triangle.GetPerimeter() == Approx(expectedPerimeter).epsilon(0.001));
			}
		}
	}
	GIVEN("Invalid triangles")
	{
		WHEN("Points are collinear")
		{
			CPoint vertex1(0, 0);
			CPoint vertex2(2, 0);
			CPoint vertex3(4, 0);
			THEN("Constructor should throw invalid_argument")
			{
				CHECK_THROWS_AS(CTriangle(vertex1, vertex2, vertex3, 0xFF0000, 0x00FF00), std::invalid_argument);
			}
		}
		WHEN("Two vertices coincide")
		{
			CPoint vertex1(0, 0);
			CPoint vertex2(0, 0);
			CPoint vertex3(1, 2);
			THEN("Constructor should throw invalid_argument")
			{
				CHECK_THROWS_AS(CTriangle(vertex1, vertex2, vertex3, 0xFF0000, 0x00FF00), std::invalid_argument);
			}
		}
	}
}

TEST_CASE("Testing rectangle")
{
	GIVEN("Valid top-left and bottom-right points with colors")
	{
		CPoint topLeft(1.0, 1.0);
		CPoint bottomRight(6.0, 5.0);
		uint32_t outlineColor = 0xFF0000;
		uint32_t fillColor = 0x00FF00;
		CRectangle rect(topLeft, bottomRight, outlineColor, fillColor);
		WHEN("Creating rectangle")
		{
			THEN("Coordinates and colors should be correctly assigned")
			{
				CHECK(rect.GetTopLeft().x == Approx(1.0));
				CHECK(rect.GetTopLeft().y == Approx(1.0));
				CHECK(rect.GetBottomRight().x == Approx(6.0));
				CHECK(rect.GetBottomRight().y == Approx(5.0));
				CHECK(rect.GetOutlineColor() == outlineColor);
				CHECK(rect.GetFillColor() == fillColor);
			}
		}
		WHEN("Checking width")
		{
			THEN("Width should be correct")
			{
				CHECK(rect.GetWidth() == Approx(5.0));
			}
		}
		WHEN("Checking height")
		{
			THEN("Height should be correct")
			{
				CHECK(rect.GetHeight() == Approx(4.0));
			}
		}
		WHEN("Checking area")
		{
			THEN("Area should be correct")
			{
				CHECK(rect.GetArea() == Approx(20.0));
			}
		}
		WHEN("Checking perimeter")
		{
			THEN("Perimeter should be correct")
			{
				CHECK(rect.GetPerimeter() == Approx(18.0));
			}
		}
	}
	GIVEN("Invalid rectangle coordinates")
	{
		uint32_t outlineColor = 0xFF0000;
		uint32_t fillColor = 0x00FF00;

		WHEN("topLeft is below and right of bottomRight")
		{
			CPoint topLeft(6.0, 5.0);
			CPoint bottomRight(1.0, 1.0);

			THEN("Constructor should throw invalid_argument")
			{
				CHECK_THROWS_AS(CRectangle(topLeft, bottomRight, outlineColor, fillColor), std::invalid_argument);
			}
		}
		WHEN("topLeft equals bottomRight")
		{
			CPoint samePoint(5.0, 5.0);

			THEN("Constructor should throw invalid_argument")
			{
				CHECK_THROWS_AS(CRectangle(samePoint, samePoint, outlineColor, fillColor), std::invalid_argument);
			}
		}
		WHEN("topLeft.x equals bottomRight.x")
		{
			CPoint topLeft(5.0, 1.0);
			CPoint bottomRight(5.0, 4.0);

			THEN("Constructor should throw invalid_argument")
			{
				CHECK_THROWS_AS(CRectangle(topLeft, bottomRight, outlineColor, fillColor), std::invalid_argument);
			}
		}
		WHEN("topLeft.y equals bottomRight.y")
		{
			CPoint topLeft(1.0, 4.0);
			CPoint bottomRight(6.0, 4.0);

			THEN("Constructor should throw invalid_argument")
			{
				CHECK_THROWS_AS(CRectangle(topLeft, bottomRight, outlineColor, fillColor), std::invalid_argument);
			}
		}
	}
}

TEST_CASE("ShapeFactory testing")
{
	SECTION("Circle")
	{
		SECTION("Valid data")
		{
			std::string str = "circle 360 320 50 0x000000 0x228B22";
			CHECK_NOTHROW(ShapeFactory::CreateShape(str));
		}
		SECTION("Invalid data")
		{
			std::string str = "circle 360 320 50 0x000000";
			CHECK_THROWS(ShapeFactory::CreateShape(str));
		}
	}
	SECTION("Triangle")
	{
		SECTION("Valid data")
		{
			std::string str1 = "triangle 100 300 300 300 200 200 0x000000 0xA52A2A";
			std::string str2 = "triangle 0 0 4 0 0 3 0xFF0000 0x00FF00";
			std::string str3 = "triangle -1 -1 2 3 4 -2 0x123456 0x654321";
			std::string str4 = "triangle 0 0 1 2 2 0 0xABCDEF 0xFEDCBA";
			std::string str5 = "triangle 10 20 30 40 50 10 0xFFFFFF 0x000000";
			CHECK_NOTHROW(ShapeFactory::CreateShape(str1));
			CHECK_NOTHROW(ShapeFactory::CreateShape(str2));
			CHECK_NOTHROW(ShapeFactory::CreateShape(str3));
			CHECK_NOTHROW(ShapeFactory::CreateShape(str4));
			CHECK_NOTHROW(ShapeFactory::CreateShape(str5));
		}
		SECTION("Invalid data")
		{
			std::string str1 = "triangle 100 100 100 100 200 200 0x000000 0xFFFFFF";
			std::string str2 = "triangle 0 0 0 0 0 0 0x000000 0xFFFFFF";
			std::string str3 = "triangle 0 0 1 1 2 2 0x123456 0x654321";
			std::string str4 = "triangle 0 0 2 0 4 0 0x000000 0x111111";
			std::string str5 = "triangle 1 1 2 2 3 3 0x111111 0x222222";
			CHECK_THROWS(ShapeFactory::CreateShape(str1));
			CHECK_THROWS(ShapeFactory::CreateShape(str2));
			CHECK_THROWS(ShapeFactory::CreateShape(str3));
			CHECK_THROWS(ShapeFactory::CreateShape(str4));
			CHECK_THROWS(ShapeFactory::CreateShape(str5));
		}
	}
	SECTION("Rectangle")
	{
		SECTION("Valid data")
		{
			std::string str1 = "rectangle 100 100 200 200 0x000000 0xFFFFFF";
			std::string str2 = "rectangle 0 0 10 10 0x123456 0x654321";
			std::string str3 = "rectangle -50 -50 0 0 0xABCDEF 0x000000";
			std::string str4 = "rectangle 10 10 100 100 0xFFFFFF 0x000000";
			std::string str5 = "rectangle 5 5 10 15 0xFF0000 0x00FF00";
			CHECK_NOTHROW(ShapeFactory::CreateShape(str1));
			CHECK_NOTHROW(ShapeFactory::CreateShape(str2));
			CHECK_NOTHROW(ShapeFactory::CreateShape(str3));
			CHECK_NOTHROW(ShapeFactory::CreateShape(str4));
			CHECK_NOTHROW(ShapeFactory::CreateShape(str5));
		}
		SECTION("Invalid data")
		{
			std::string str1 = "rectangle 100 100 50 50 0x000000 0xFFFFFF";
			std::string str2 = "rectangle 10 10 10 20 0x123456 0x654321";
			std::string str3 = "rectangle 10 20 30 20 0xABCDEF 0x000000";
			std::string str4 = "rectangle 30 30 10 10 0xFF0000 0x00FF00";
			std::string str5 = "rectangle 0 0 100 100 0xZZZZZZ 0xFFFFFF";
			std::string str6 = "rectangle 10 10 20 20 0x000000";
			std::string str7 = "rectangle 10 10 20 20";
			CHECK_THROWS(ShapeFactory::CreateShape(str1));
			CHECK_THROWS(ShapeFactory::CreateShape(str2));
			CHECK_THROWS(ShapeFactory::CreateShape(str3));
			CHECK_THROWS(ShapeFactory::CreateShape(str4));
			CHECK_THROWS(ShapeFactory::CreateShape(str5));
			CHECK_THROWS(ShapeFactory::CreateShape(str6));
			CHECK_THROWS(ShapeFactory::CreateShape(str7));
		}
	}
	SECTION("Line")
	{
		SECTION("Valid data")
		{
			std::string str1 = "line 0 0 10 10 0x000000";
			std::string str2 = "line 5 5 100 100 0xFF00FF";
			std::string str3 = "line -50 -50 0 0 0x00FF00";
			std::string str4 = "line 1 2 3 4 0xFFFFFF";
			std::string str5 = "line 100 100 200 50 0x123456";
			CHECK_NOTHROW(ShapeFactory::CreateShape(str1));
			CHECK_NOTHROW(ShapeFactory::CreateShape(str2));
			CHECK_NOTHROW(ShapeFactory::CreateShape(str3));
			CHECK_NOTHROW(ShapeFactory::CreateShape(str4));
			CHECK_NOTHROW(ShapeFactory::CreateShape(str5));
		}
		SECTION("Invalid data")
		{
			std::string str1 = "line 0 0 0 0 0x000000";
			std::string str2 = "line 10 10 10 10 0xFFFFFF";
			std::string str3 = "line 0 0 10 10";
			std::string str4 = "line 0 0 10 10 0xGGGGGG";
			std::string str5 = "line 10 10 20";
			CHECK_THROWS(ShapeFactory::CreateShape(str1));
			CHECK_THROWS(ShapeFactory::CreateShape(str2));
			CHECK_THROWS(ShapeFactory::CreateShape(str3));
			CHECK_THROWS(ShapeFactory::CreateShape(str4));
			CHECK_THROWS(ShapeFactory::CreateShape(str5));
		}
	}
}


std::shared_ptr<IShape> FindMaxAreaFunc(const std::vector<std::shared_ptr<IShape>>& shapes)
{
	auto maxShape = shapes[0];
	double maxArea = maxShape->GetArea();

	for (const auto& shape : shapes)
	{
		if (shape->GetArea() > maxArea)
		{
			maxArea = shape->GetArea();
			maxShape = shape;
		}
	}
	return maxShape;
}

std::shared_ptr<IShape> FindMinPerimeterFunc(const std::vector<std::shared_ptr<IShape>>& shapes)
{
	auto minShape = shapes[0];
	double minPerimeter = minShape->GetPerimeter();

	for (const auto& shape : shapes)
	{
		if (shape->GetPerimeter() < minPerimeter)
		{
			minPerimeter = shape->GetPerimeter();
			minShape = shape;
		}
	}

	return minShape;
}

TEST_CASE("ShapeManager testing")
{
	SECTION("Read valid shapes from stream")
	{
		std::stringstream input;
		input << "triangle 0 0 3 0 0 4 FF0000 00FF00\n"
			<< "triangle 0 0 6 0 0 8 0000FF FFFF00\n";

		ShapeManager manager;
		manager.ReadShape(input);

		auto shapes = manager.GetShapes();
		CHECK(shapes.size() == 2);
		CHECK(shapes[0]->GetArea() == Approx(6)); 
		CHECK(shapes[1]->GetArea() == Approx(24));
		CHECK(shapes[0]->GetPerimeter() == Approx(12));
		CHECK(shapes[1]->GetPerimeter() == Approx(24));
	}
	SECTION("Read invalid shapes from stream")
	{
		std::stringstream input;
		input << "invalid shape\n"
			<< "triangle 0 0 3 0 0 4 FF0000 00FF00\n"
			<< "invalid shape\n";

		std::stringstream output;
		std::streambuf* oldCerr = std::cerr.rdbuf(output.rdbuf());

		ShapeManager manager;
		manager.ReadShape(input);

		std::cerr.rdbuf(oldCerr);

		auto shapes = manager.GetShapes();
		CHECK(shapes.size() == 3); 
		CHECK(shapes[1]->GetArea() == Approx(6));
	}
	SECTION("Read shapes from file")
	{
		std::string filename = "test_shapes.txt";
		std::ofstream file(filename);
		file << "triangle 0 0 3 0 0 4 FF0000 00FF00\n"
			<< "triangle 0 0 6 0 0 8 0000FF FFFF00\n";
		file.close();

		ShapeManager manager;
		CHECK_NOTHROW(manager.ReadShape(filename));

		auto shapes = manager.GetShapes();
		CHECK(shapes.size() == 2);
		CHECK(shapes[0]->GetArea() == Approx(6));
		CHECK(shapes[1]->GetArea() == Approx(24));
	}
	SECTION("Handle empty shapes")
	{
		ShapeManager manager;
		std::stringstream output;
		std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
		manager.PrintMaxAreaShape();
		manager.PrintMinPerimeterShape();
		std::cout.rdbuf(oldCout);
		CHECK(output.str() == "No Shapes\nNo shapes\n");
	}
	SECTION("FindMaxArea and FindMinPerimeter")
	{
		std::vector<std::shared_ptr<IShape>> shapes;
		shapes.push_back(std::make_shared<CTriangle>(CPoint(0, 0), CPoint(3, 0), CPoint(0, 4), 0xFF0000, 0x00FF00)); 
		shapes.push_back(std::make_shared<CTriangle>(CPoint(0, 0), CPoint(6, 0), CPoint(0, 8), 0x0000FF, 0xFFFF00));

		auto maxShape = FindMaxAreaFunc(shapes);
		CHECK(maxShape->GetArea() == Approx(24));

		auto minShape = FindMinPerimeterFunc(shapes);
		CHECK(minShape->GetPerimeter() == Approx(12));
	}
}
