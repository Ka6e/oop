#include "include/FindMaxEx.h"
int main()
{
	std::vector<Person> persons = {
		{"Mike Tyson", 100, 186.0},
		{"Keanu Reeves", 76.8, 170.6},
		{"Tyler Durden", 75.8, 168.4}
	};

	PrintMaxHeight(persons);
	PrintMaxWeight(persons);
	return 0;
}
