/*
 *  条款4:知道如何查看类型推导
 */

#include <vector>
#include <iostream>
#include <boost/type_index.hpp>

template<typename T>    // 声明TD
class TD;               // TD == "Type Displayer"

template<typename T>    // template function to be called
void f(const T& param)
{
    using std::cout;
#if 0
    // Using typid to output type
    cout << "T = " << typeid(T).name() << '\n'; // 展示T
    cout << "param = " << typeid(param).name() << '\n'; // 展示param的类型
#endif
    // Using boost to output type
    using boost::typeindex::type_id_with_cvr;
    // show T
    cout << "T = "
         << type_id_with_cvr<T>().pretty_name()
         << '\n';
    // show param's type
    cout << "param = "
         << type_id_with_cvr<decltype(param)>().pretty_name()
         << '\n';
}

class Widget
{

};

std::vector<Widget> createVec()
{
    std::vector<Widget> vec;
    vec.push_back(Widget());
    return vec;
}

int main(int argc, char** argv)
{
    const int theAnswer = 42;
    auto x = theAnswer;
    auto y = &theAnswer;
#if 0
    TD<decltype(x)> xType; // 引起的错误
    TD<decltype(y)> yType; // 包含了x和y的类型
#endif

    std::vector<Widget> createVec();
    const auto vw = createVec();
    if (!vw.empty()) {
        f(&vw[0]);
    }

    return 0;
}

/* EOF */
