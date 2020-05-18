#include <iostream>
#include <lcm/lcm-cpp.hpp>
#include "exlcm/Example.hpp"

int main(int argc, char ** argv)
{
    lcm::LCM lcm("udpm://239.255.76.67:7667?ttl=1");

    if(!lcm.good())
        return 1;

    exlcm::Example my_data;
    my_data.a = 1;
    my_data.b = 2.0;

    lcm.publish("EXAMPLE", &my_data);
    std::cout << "发送成功!" << std::endl;

    return 0;
}
