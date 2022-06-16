/*
 * 条款22：当使用Pimpl的时候在实现文件中定义特殊的成员函数
 */

#include "clause_22.h"
#include <string>
#include <vector>
#include <cstdint>
#include <iostream>

struct Widget::Impl
{
    std::string name;           //as before definition of
    std::vector<double> data;   //Widget::Impl
    int32_t g1,g2,g3;
};

Widget::Widget()
: pImpl(std::make_unique<Impl>())
{
    
}

Widget::~Widget() = default;
Widget::Widget(Widget&& rhs) = default;
Widget& Widget::operator=(Widget&& rhs) = default;


int main(int argc, char** argv)
{
    Widget w; //error

    Widget w1;
    auto w2(std::move(w1));     //move-consturct w2
    w1 = std::move(w2);         //move-assign w1

    std::cout << "clause 22 done."
              << '\n';

    return 0;
}

/* EOF */
