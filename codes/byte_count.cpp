#include <iostream>
#include <cstdio>

int countByte1(uint8_t input)
{
    int count = 0;
    for (;input != 0; input >>= 1) {
        if (input & 0x1) {
            count++;
        }
    }

    return count;
}

int f(char c)
{
    int sum = 0;
    char a = 1;
    for(int i=0; i<8; i++)
    {
        if(c & a) {
            sum++;
        }
            
        a = a << 1;
    }
    return sum;
}

int main(int argc, char** argv)
{
    uint8_t byte = 0xF0;
    int ret1 = countByte1(byte);
    int ret2 = f(byte);
    std::cout << ret1 << " " << ret2 << "\n";

    return 1;
}
