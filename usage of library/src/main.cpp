#include <iostream>
#include <add_int.hpp>

int main() {
    int a = 5;
    int b = 7;
    int sum = MyLibrary::add_int(a, b);

    std::cout << "The sum of " << a << " and " << b << " is " << sum;

    return 0;
}