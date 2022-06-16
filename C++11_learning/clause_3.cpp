/*
 * 条款3:理解decltype
 */

#include <array>
#include <deque>
#include <vector>
#include <iostream>
#include "type_name.hpp"

template<typename T, std::size_t size>
class Container
{
public:
    Container()
    {
        member_ = {0};
    }

    template<typename type>
    Container(type list)
    {
        int i = 0;
        for (auto it = list.begin(); it != list.end(); ++it, i++) {
            member_[i] = *it;
        }

        std::cout << type_name<decltype(list)>() << std::endl;
    }

    T& operator[](std::size_t i)
    {
        return member_[i];
    }

private:
    std::array<T, size> member_;
};

void authenticateUser(void)
{
    // Nothing
}

// final C++14 version
template<typename Container, typename Index>
decltype(auto) authAndAccess(Container&& c, Index i)
{
    authenticateUser();
    return std::forward<Container>(c)[i];
}

int main(int vargc, char** argv)
{
    // std::deque<int> d = {0, 0, 0, 0, 0, 0};
    // std::vector<int> d = {0, 0, 0, 0, 0, 0};
    auto x = {0, 0, 0, 0, 0, 0, 0};
    Container<int, 8> d = x;

    authAndAccess(d, 5) = 10;

    std::cout << d[5] << std::endl;

    return 0;
}
