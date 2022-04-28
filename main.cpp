#include "Vector.h"
#include <iostream>
#include <utility>
int main()
{
    Vector test;
    double array[] = {2, 3, 4, 5, 6};
    double one[] = {0., 9};
    test.reserve(100);
    test.insert(array, 5, 0);
    test.insert(7.0, 0);
    for (int i = 0; i < test.size(); i++)
    {
        std::cout << test[i] << std::endl;
        //std::cout << test.capacity() << test.size();
    }
    
    //test.reserve(100);

   //test.insert(one, 2, 2);

    for (int i = 0; i < test.size(); i++)
    {
        //std::cout << test[i] << std::endl;
    }

    //Vector test1;

    //test1.insert(test1, 0); 
    return 0;
}
