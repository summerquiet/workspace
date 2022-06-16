/*
 * 条款1:理解模板类型推导
 */

#include <array>
#include <iostream>

// 在编译的时候返回数组的长度(数组参数没有名字，
// 因为只关心数组包含的元素的个数)
template<typename T, std::size_t N>
constexpr std::size_t arraySize(T (&)[N]) noexcept
{
    return N; // constexpr和noexcept在随后的条款中介绍
}

int main(int argc, char** argv)
{
    int keyVals[] = { 1, 3, 7, 9, 11, 22, 35 }; // keyVals有七个元素
    std::array<int, arraySize(keyVals)> mappedVals; // mappedVals长度是七

    std::cout << sizeof(mappedVals) << std::endl;

    return 0;
}
