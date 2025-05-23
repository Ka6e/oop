#define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "../vector/include/VectorOperations.h"

TEST_CASE("ReadNumbers ��������� ������ ����", "[ReadNumbers]")
{
    SECTION("Correct input") 
    {
        std::istringstream input("1.5 2.5 -3.0\n");
        std::cin.rdbuf(input.rdbuf());
        DoubleVector expected = { 1.5, 2.5, -3.0 };
        CHECK(ReadNumbers() == expected);

        std::istringstream input1("4 16 -30 10\n");
        std::cin.rdbuf(input1.rdbuf());
        DoubleVector expected1 = { 4,  16, -30, 10 };
        CHECK(ReadNumbers() == expected1);
    }

    SECTION("Incorrect input")
    {
        std::istringstream input("- 2 3\n");
        std::cin.rdbuf(input.rdbuf());
        CHECK_THROWS(ReadNumbers());

        std::istringstream input1("1 2 a\n");
        std::cin.rdbuf(input1.rdbuf());
        CHECK_THROWS(ReadNumbers());

        std::istringstream input2();
        std::cin.rdbuf(input.rdbuf());
        DoubleVector expeted2{};
        CHECK_THROWS(ReadNumbers());
    }
}


TEST_CASE("ProcessNumbers ��������� ��������� ������� ������������� �����", "[ProcessNumbers]")
{
    SECTION("Correct input")
    {
        DoubleVector vec1 = { 1.0, 2, 3.659512 };
        DoubleVector expected1 = { 3.220, 4.220, 5.879 };

        DoubleVector vec2 = { 4,  16, -30, 10 };
        DoubleVector expected2 = { 14.000, 26.000, -20.000, 20.000 };

        DoubleVector vec3 = { 0.0, 5.0, 10.0, 15.0 };
        DoubleVector expected3 = { 10.0, 15.0, 20.0, 25.0 };

        double epsilon = 0.001;

        ProcessNumbers(vec1);
        ProcessNumbers(vec2);
        ProcessNumbers(vec3);

        for (size_t i = 0; i < vec1.size(); i++)
        {
            CHECK(Approx(vec1[i]).epsilon(epsilon) == expected1[i]);
        }

        for (size_t i = 0; i < vec2.size(); i++)
        {
            CHECK(Approx(vec2[i]).epsilon(epsilon) == expected2[i]);
        }

        for (size_t i = 0; i < vec3.size(); i++)
        {
            CHECK(Approx(vec3[i]).epsilon(epsilon) == expected3[i]);
        }
    }
}

TEST_CASE("Sort ��������� ��������� �����", "[Sort]")
{
    SECTION("Correct input")
    {
        DoubleVector vec1 = { 3.0, 1.0, 2.0 };
        DoubleVector expected1 = { 1.0, 2.0, 3.0 };

        DoubleVector vec2 = { -1.0, -3.0, -2.0, 0.0 };
        DoubleVector expected2 = { -3.0, -2.0, -1.0, 0.0 };

        DoubleVector vec3 = { 5.0 };
        DoubleVector expected3 = { 5.0 };

        DoubleVector vec4 = { 14.000, 26.000, -20.000, 20.000 };
        DoubleVector expected4 = { -20.000, 14.000, 20.000, 26.000 };

        DoubleVector vec5 = { 1.0, 2.0, 3.0, 4.0, 5.0 };
        DoubleVector expected5 = { 1.0, 2.0, 3.0, 4.0, 5.0 };

        Sort(vec1);
        Sort(vec2);
        Sort(vec3);
        Sort(vec4);
        Sort(vec5);

        CHECK(vec1 == expected1);
        CHECK(vec2 == expected2);
        CHECK(vec3 == expected3);
        CHECK(vec4 == expected4);
        CHECK(vec5 == expected5);
    }
}
