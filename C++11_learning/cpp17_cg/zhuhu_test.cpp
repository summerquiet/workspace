#include <iostream>
#include <functional>

class Filter
{
public:
    Filter(int divisorVal):
        divisor{divisorVal}
    {}

    std::function<bool(int)> getFilter() 
    {
        return [=](int value) {return value % divisor == 0; };
    }

private:
    int divisor;
};

int main(int argc, char** argv)
{
    std::function<bool(int, int)> wrapper = [](int x, int y) { return x < y; };

    auto ret = wrapper(1, 2);

    std::cout << "hello world!\n"
        << ret
        << std::endl;

    return 0;
}
