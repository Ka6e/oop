#define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "../Car/include/Car.h"


TEST_CASE("Car initial state")
{
	Car car;
	CHECK_FALSE(car.IsTurnedOn());
	CHECK(car.GetDirection() == CarMovementState::STAY);
	CHECK(car.GetGear() == 0);
	CHECK(car.GetSpeed() == 0);
}

TEST_CASE("Check Engine Method")
{
	Car car;
	CHECK(car.TurnOnEngine());
	CHECK(car.IsTurnedOn());
	CHECK(car.TurnOffEngine());
	CHECK_FALSE(car.IsTurnedOn());
}

TEST_CASE("Check Engine while mooving")
{
	Car car;
	CHECK(car.TurnOnEngine());
	CHECK(car.SetGear(1));
	CHECK(car.SetSpeed(20));
	CHECK(car.GetGear() == 1);
	CHECK(car.GetSpeed() == 20);
	CHECK_FALSE(car.TurnOffEngine());
	CHECK(car.IsTurnedOn());
	
	CHECK(car.SetSpeed(0));
	CHECK(car.GetSpeed() == 0);
	CHECK_FALSE(car.TurnOffEngine());
	CHECK(car.IsTurnedOn());

	CHECK(car.GetGear() == 1);
	CHECK_FALSE(car.TurnOffEngine());
	CHECK(car.IsTurnedOn());

	CHECK(car.SetGear(0));
	CHECK(car.GetGear() == 0);
	CHECK(car.GetSpeed() == 0);
	CHECK(car.TurnOffEngine());
	CHECK_FALSE(car.IsTurnedOn());
} 

TEST_CASE("Check reverse gear")
{
	Car car;
	car.TurnOnEngine();

	CHECK(car.SetGear(-1));
	CHECK(car.GetGear() == -1);
	CHECK(car.SetSpeed(0));
	CHECK(car.GetSpeed() == 0);
	CHECK(car.SetSpeed(5));
	CHECK(car.GetSpeed() == 5);
	CHECK_FALSE(car.SetSpeed(-1));
	CHECK(car.GetSpeed() == 5);
	CHECK(car.SetSpeed(20));
	CHECK(car.GetSpeed() == 20);
	CHECK_FALSE(car.SetSpeed(21));
	CHECK(car.GetSpeed() == 20);
}

TEST_CASE("Check first gear")
{
	Car car;
	car.TurnOnEngine();

	CHECK(car.SetGear(1));
	CHECK(car.GetGear() == 1);
	CHECK(car.SetSpeed(0));
	CHECK(car.GetSpeed() == 0);
	CHECK_FALSE(car.SetSpeed(-1));
	CHECK(car.SetSpeed(20));
	CHECK(car.GetSpeed() == 20);
	CHECK(car.SetSpeed(30));
	CHECK(car.GetSpeed() == 30);
	CHECK_FALSE(car.SetSpeed(31));	
	CHECK(car.GetSpeed() == 30);
}

TEST_CASE("Check second gear")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);

	CHECK(car.SetGear(2));
	CHECK(car.GetGear() == 2);
	CHECK(car.SetSpeed(36));
	CHECK(car.GetSpeed() == 36);
	CHECK_FALSE(car.SetSpeed(19));
	CHECK(car.GetSpeed() == 36);
	CHECK(car.SetSpeed(50));
	CHECK(car.GetSpeed() == 50);
	CHECK_FALSE(car.SetSpeed(51));
	CHECK(car.GetSpeed() == 50);
}


TEST_CASE("Check third gear")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	car.SetGear(2);
	car.SetSpeed(30);

	CHECK(car.SetGear(3));
	CHECK(car.GetGear() == 3);
	CHECK(car.SetSpeed(56));
	CHECK(car.GetSpeed() == 56);
	CHECK_FALSE(car.SetSpeed(22));
	CHECK(car.GetSpeed() == 56);
	CHECK(car.SetSpeed(60));
	CHECK(car.GetSpeed() == 60);
	CHECK_FALSE(car.SetSpeed(66));
	CHECK(car.GetSpeed() == 60);
}

TEST_CASE("Check fourth gear")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	car.SetGear(2);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(40);

	CHECK(car.SetGear(4));
	CHECK(car.GetGear() == 4);
	CHECK(car.SetSpeed(80));
	CHECK(car.GetSpeed() == 80);
	CHECK_FALSE(car.SetSpeed(35));
	CHECK(car.GetSpeed() == 80);
	CHECK(car.SetSpeed(90));
	CHECK(car.GetSpeed() == 90);
	CHECK_FALSE(car.SetSpeed(100));
	CHECK(car.GetSpeed() == 90);
}

TEST_CASE("Check fifth gear")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	car.SetGear(2);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(40);
	car.SetGear(4);
	car.SetSpeed(50);

	CHECK(car.SetGear(5));
	CHECK(car.GetGear() == 5);
	CHECK(car.SetSpeed(115));
	CHECK(car.GetSpeed() == 115);
	CHECK_FALSE(car.SetSpeed(40));
	CHECK(car.SetSpeed(150));
	CHECK(car.GetSpeed() == 150);
	CHECK_FALSE(car.SetSpeed(180));
	CHECK(car.GetSpeed() == 150);
}


TEST_CASE("Check from 5 gear to  -1 gear")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	car.SetGear(2);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(50);
	car.SetGear(4);
	car.SetSpeed(80);
	car.SetGear(5);
	car.SetSpeed(150);
	CHECK_FALSE(car.SetSpeed(0));
	CHECK(car.SetSpeed(80));
	CHECK(car.GetSpeed() == 80);
	CHECK(car.SetGear(4));
	CHECK(car.GetGear() == 4);
	CHECK(car.SetSpeed(50));
	CHECK(car.GetSpeed() == 50);
	CHECK(car.SetGear(3));
	CHECK(car.GetGear() == 3);
	CHECK(car.SetSpeed(30));
	CHECK(car.GetSpeed() == 30);
	CHECK(car.SetGear(2));
	CHECK(car.GetGear() == 2);
	CHECK(car.SetSpeed(20));
	CHECK(car.GetSpeed() == 20);
	CHECK(car.SetGear(1));
	CHECK(car.GetGear() == 1);
	CHECK(car.SetSpeed(15));
	CHECK(car.GetSpeed() == 15);
	CHECK_FALSE(car.SetGear(-1));
	CHECK(car.GetGear() == 1);
	CHECK(car.SetSpeed(0));
	CHECK(car.GetSpeed() == 0);
	CHECK(car.SetGear(-1));
	CHECK(car.SetSpeed(15));
	CHECK(car.GetSpeed() == 15);
	CHECK(car.SetSpeed(20));
	CHECK(car.GetSpeed() == 20);
	CHECK_FALSE(car.SetSpeed(-1));
}

TEST_CASE("Check negative speed")
{
	Car car;
	car.TurnOnEngine();

	CHECK(car.SetGear(-1));
	CHECK_FALSE(car.SetSpeed(-15));
}

TEST_CASE("Chech speed change with neutral gear")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(15);
	car.SetGear(0);

	CHECK_FALSE(car.SetSpeed(20));
	CHECK(car.GetSpeed() == 15);
	CHECK(car.SetSpeed(10));
	CHECK(car.GetSpeed() == 10);
}

TEST_CASE("Chech set the speed with the engine off")
{
	Car car;

	CHECK_FALSE(car.SetSpeed(15));
	CHECK_FALSE(car.SetSpeed(-5));
}

TEST_CASE("Check SetGear")
{
	Car car;
	car.TurnOnEngine();

	CHECK_FALSE(car.SetGear(-2));
	CHECK_FALSE(car.SetGear(6));

	CHECK(car.SetGear(-1));
	CHECK(car.GetGear() == -1);
	CHECK(car.SetSpeed(5));
	CHECK(car.GetSpeed() == 5);
	CHECK(car.SetSpeed(0));
	CHECK(car.GetSpeed() == 0);
	CHECK(car.SetGear(1));
	CHECK(car.GetGear() == 1);

	CHECK_FALSE(car.SetGear(3));

	CHECK(car.SetGear(0));
	CHECK(car.TurnOffEngine());
	CHECK_FALSE(car.SetGear(5));


	CHECK(car.TurnOnEngine());
	CHECK(car.SetGear(1));
	CHECK(car.SetSpeed(10));
	CHECK_FALSE(car.SetGear(-1));
}


TEST_CASE("general testing")
{
	SECTION("the ideal option")
	{
		Car car;
		car.TurnOnEngine();

		CHECK(car.SetGear(-1));
		CHECK(car.SetSpeed(14));
		CHECK(car.SetSpeed(0));
		CHECK(car.SetGear(1));
		CHECK(car.SetSpeed(20));
		CHECK(car.SetGear(2));
		CHECK(car.SetSpeed(40));
		CHECK(car.SetGear(3));
		CHECK(car.SetSpeed(50));
		CHECK(car.SetGear(4));
		CHECK(car.SetSpeed(70));
		CHECK(car.SetGear(5));
		CHECK(car.SetSpeed(100));
		CHECK(car.SetGear(0));
		CHECK(car.SetSpeed(70));
		CHECK(car.SetSpeed(40));
		CHECK(car.SetSpeed(20));
		CHECK(car.SetSpeed(5));
		CHECK(car.SetSpeed(0));
	}
}