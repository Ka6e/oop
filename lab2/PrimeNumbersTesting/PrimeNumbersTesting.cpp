#define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "../PrimeNumbers/include/PrimeNumbersOperations.h"

TEST_CASE("PrimeNumbers", "[GeneratePrimeNumbersSet]")
{
    CHECK_THROWS_AS(GeneratePrimeNumbersSet(1), std::invalid_argument);
    CHECK_THROWS_AS(GeneratePrimeNumbersSet(100000001), std::invalid_argument);

    auto prime = GeneratePrimeNumbersSet(30);
    CHECK(prime.size() == 10);

    auto prime1 = GeneratePrimeNumbersSet(100000000);
    CHECK(prime1.size() == 5761455);

    CHECK_THROWS_AS(GeneratePrimeNumbersSet(-1), std::invalid_argument);

    auto prime2 = GeneratePrimeNumbersSet(2);
    CHECK(prime2.size() == 1);
}