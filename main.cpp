#include "Vector.h"
#include <iostream>
#include <utility>
int main()
{
    Vector test;
    test.pushBack(1);
    test.pushBack(2);
    Vector test2;
    double array[2] = {2., 3.};
    Vector test3;
    test3.pushBack(1);
    test3.insert(2, 0);
    Vector::Iterator p = test3.begin();
    ++p;
    test3.reserve(10);
   test3.shrinkToFit(); 

    std::cout << test3.capacity() << std::endl << test3[0] << std::endl << test3.size();
    return 0;
}
