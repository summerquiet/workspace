#include <string>
#include <iostream>

struct MyStruct
{
    int i = 0;
    std::string s;
    double x = 0.0;
};

int main(int argc, char** argv)
{
    MyStruct ms{42, "hello", 12.0};
    auto [u, v, w] = ms;
    ms.i = 77;
    std::cout << u << "\n";    // prints 42
    u = 99;
    std::cout << ms.i << "\n"; // prints 77

    std::cout << v << "\n";
    std::cout << w << "\n";
}
