/*
 * 条款22：当使用Pimpl的时候在实现文件中定义特殊的成员函数
 */

#include <memory>

class Widget
{
public:
    Widget();
    ~Widget();

    Widget(Widget&& rhs);
    Widget& operator=(Widget&& rhs);

private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};

/* EOF */
