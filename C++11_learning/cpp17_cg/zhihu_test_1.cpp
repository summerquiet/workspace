#include <iostream>

struct A
{
    ~A()
    {
        std::cout << "A delete" << std::endl;
    }

    void Print()
    {
       std::cout << m_data << std::endl;
    }

    int m_data = 20;
};

int main()
{
    auto ptr = std::unique_ptr<A>(new A);
    // auto tptr = std::make_unique<A>(); // error, c++11还不行，需要c++14
    std::unique_ptr<A> tem = std::move(ptr); // error, unique_ptr不允许移动，编译失败

    if (ptr) {
        ptr->Print();
    }

    if (tem) {
        tem->Print();
    }

    return 0;
}
