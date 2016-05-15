#include <hugeint.h>
#include <iostream>
#include <limits>

using namespace hugeint;

int
main( )
{
    std::cout << 1001_huge << ' ' << 123456789123456789_huge << ' '
              << "18423048239480239840298340846744073709551615"_huge << std::endl;
    std::cout << 999999_huge + 1_huge << ' ' << 1001_huge + 1001_huge << ' '
              << "999999999999999999999999"_huge + 1 << std::endl;
    std::cout << ( 9998_huge < 9999_huge ) << ' ' << ( 9999_huge < 9998_huge ) << ' '
              << ( 9998_huge < 9998_huge ) << std::endl;
    std::cout << ( 9998_huge == 9999_huge ) << ' ' << ( 9999_huge != 9998_huge ) << ' '
              << ( 9998_huge == 9998_huge ) << std::endl;
    return 0;
}
