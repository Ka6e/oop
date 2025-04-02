#define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "../Car/include/Car.h"

// привести тесты в порядок, 
TEST_CASE("Car initial state")
{
	GIVEN("Car is standing")
	{
		Car car;
		WHEN("Engine is off") 
		{
			THEN("Car should stand")
			{
				CHECK_FALSE(car.IsTurnedOn());
				CHECK(car.GetDirection() == CarMovementState::STAY);
				CHECK(car.GetGear() == 0);
				CHECK(car.GetSpeed() == 0);
			}
		}
	}
}

TEST_CASE("Check Engine Method")
{
	GIVEN("A car with an engine")
	{
		Car car;
		WHEN("The engine is turned on")
		{
			CHECK(car.TurnOnEngine());
			THEN("The engine should be running")
			{ 
				CHECK(car.IsTurnedOn());
			}
		}
		WHEN("The engine is turned off after being started")
		{
			car.TurnOnEngine();
			CHECK(car.TurnOffEngine());
			THEN("It should be off")
			{
				CHECK_FALSE(car.IsTurnedOn());
			}
		}
	}
}

TEST_CASE("Engine cannot turn off while moving")
{
	GIVEN("A moving car")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		WHEN("Attempting to turn off the engine while moving")
		{
			THEN("The engine should remain on")
			{
				CHECK_FALSE(car.TurnOffEngine());
				CHECK(car.IsTurnedOn());
			}
		}
		WHEN("Car stops moving but gear is not neutral")
		{
			car.SetSpeed(0);
			THEN("Engine should still be on")
			{
				CHECK_FALSE(car.TurnOffEngine());
				CHECK(car.IsTurnedOn());
			}
		}
		WHEN("Car is in neutral gear and stopped")
		{
			car.SetGear(0);
			car.SetSpeed(0);
			THEN("Engine should be able to turn off")
			{
				CHECK(car.TurnOffEngine());
				CHECK_FALSE(car.IsTurnedOn());
			}
		}
	}
}

TEST_CASE("Check Engine while moving")
{
	GIVEN("A car with the engine turned on")
	{
		Car car;
		REQUIRE(car.TurnOnEngine());

		WHEN("The car is set to first gear and speed is increased to 20")
		{
			REQUIRE(car.SetGear(1));
			REQUIRE(car.SetSpeed(20));

			THEN("The car should be in first gear and moving at 20 speed")
			{
				CHECK(car.GetGear() == 1);
				CHECK(car.GetSpeed() == 20);
				CHECK_FALSE(car.TurnOffEngine());
				CHECK(car.IsTurnedOn());
			}
		}

		WHEN("The car is stopped but still in gear")
		{
			CHECK(car.SetSpeed(0));
			CHECK(car.SetGear(1));
			THEN("The engine should remain on and cannot be turned off")
			{
				CHECK(car.GetSpeed() == 0);
				CHECK_FALSE(car.TurnOffEngine());
				CHECK(car.IsTurnedOn());
				CHECK(car.GetGear() == 1);
			}
		}

		WHEN("The car is set to neutral gear while stationary")
		{
			REQUIRE(car.SetSpeed(0));
			REQUIRE(car.SetGear(0));

			THEN("The engine should be able to turn off")
			{
				CHECK(car.GetGear() == 0);
				CHECK(car.GetSpeed() == 0);
				CHECK(car.TurnOffEngine());
				CHECK_FALSE(car.IsTurnedOn());
			}
		}
	}
}

TEST_CASE("Reverse gear behaviour")
{
	GIVEN("A car with an engine running")
	{
		Car car;
		car.TurnOnEngine();
		WHEN("Setting reverse gear")
		{
			CHECK(car.SetGear(-1));
			THEN("Car should be in reverse gear")
			{
				CHECK(car.GetGear() == -1);
			}
		}
		WHEN("Increasing speed in reverse")
		{
			car.SetGear(-1);
			CHECK(car.SetGear(1));
			CHECK(car.SetSpeed(20));
			THEN("Speed should increase up to the limit")
			{
				CHECK_FALSE(car.SetSpeed(-1));
				CHECK(car.SetSpeed(30));
			}
		}
	}
}

TEST_CASE("Check first gear")
{
	GIVEN("car with turned on engine")
	{
		Car car;
		car.TurnOnEngine();
		WHEN("setting gear 1")
		{
			CHECK(car.SetGear(1));
			THEN("Gear is 1 and speed could be in speed can be within the limits of this transmission")
			{
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
		}
	}
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
	GIVEN("Car with 2 gear")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(2);
		car.SetSpeed(30);
		WHEN("Setting 3 gear")
		{
			CHECK(car.SetGear(3));
			THEN("Gear is 3 and speed could be in speed can be within the limits of this transmission")
			{
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
		}
	}
}

TEST_CASE("Check fourth gear")
{
	GIVEN("car with 3 gear")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(2);
		car.SetSpeed(30);
		car.SetGear(3);
		car.SetSpeed(40);
		WHEN("Setting 4 gear")
		{ 
			CHECK(car.SetGear(4));
			THEN("Gear is 4 and speed could be in speed can be within the limits of this transmission")
			{
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
		}
	}
}

TEST_CASE("Check fifth gear")
{
	GIVEN("Car with 4 gear")
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
		WHEN("Setting the 5 gear")
		{
			CHECK(car.SetGear(5));
			THEN("Gear is 5 and speed could be in speed can be within the limits of this transmission")
			{
				CHECK(car.GetGear() == 5);
				CHECK(car.SetSpeed(115));
				CHECK(car.GetSpeed() == 115);
				CHECK_FALSE(car.SetSpeed(40));
				CHECK(car.SetSpeed(150));
				CHECK(car.GetSpeed() == 150);
				CHECK_FALSE(car.SetSpeed(180));
				CHECK(car.GetSpeed() == 150);
			}
		}
	}
}


TEST_CASE("Check from 5 gear to  -1 gear")
{
	GIVEN("Car with 5 gear and max speed")
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
		WHEN("Trying to set car speed 0")
		{
			CHECK_FALSE(car.SetSpeed(0));
			THEN("Car's speed shoudl be 150")
			{
				CHECK(car.GetSpeed() == 150);
			}
		}
	}
}

TEST_CASE("Check negative speed")
{
	GIVEN("Car with engine running")
	{
		Car car;
		car.TurnOnEngine();
		WHEN("Setting reverse gear and trying a negative speed")
		{
			car.SetGear(-1);
			THEN("Setting a negative speed should fail")
			{
				CHECK_FALSE(car.SetSpeed(-15));
			}
		}
	}
}

TEST_CASE("Chech speed change with neutral gear")
{
	GIVEN("Car wit 1 gear and 15 speed")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(15);
		WHEN("Setting neutral gear")
		{
			car.SetGear(0);
			THEN("Speed should decrease")
			{
				CHECK_FALSE(car.SetSpeed(20));
				CHECK(car.GetSpeed() == 15);
				CHECK(car.SetSpeed(10));
				CHECK(car.GetSpeed() == 10);
			}
		}
	}
}

TEST_CASE("Chech set the speed with the engine off")
{
	GIVEN("Car with engine off")
	{
		Car car;
		WHEN("Setting speed with turned off engine")
		{
			CHECK_FALSE(car.SetSpeed(15));
			CHECK_FALSE(car.SetSpeed(-5));
			THEN("Car cannot move while engine is off")
			{
				CHECK(car.GetSpeed() == 0);
			}
		}
	}

}
