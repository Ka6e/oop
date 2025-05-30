#include <iostream>
#include <list>
int main()
{
    std::list<int> a{ 1,2,3,4,5 };
    std::cout << *--a.end();
}
