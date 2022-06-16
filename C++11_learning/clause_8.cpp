/*
 *  条款8:优先使用nullptr而不是0或者NULL
 */

#include <mutex>
#include <memory>

using MuxGuard = std::lock_guard<std::mutex>;

class Widget
{

};

int f1(std::shared_ptr<Widget> spw) // 只有对应的
{
    return 0;
}

double f2(std::unique_ptr<Widget> upw) // 互斥量被锁定
{
    return 0.0;
}

bool f3(Widget* pw) // 才会调用这些函数
{
    return false;
}

template<typename FuncType,
         typename MuxType,
         typename PtrType>
#if 1
decltype(auto) lockAndCall(FuncType func, // C++14
                            MuxType& mutex,
                            PtrType ptr)
#else
auto lockAndCall(FuncType func, // C++11
                MuxType& mutex,
                PtrType ptr) -> decltype(func(ptr))
#endif
{
    MuxGuard g(mutex);
    return func(ptr);
}

int main(int argc, char** argv)
{
    std::mutex f1m, f2m, f3m; // 对应于f1, f2和f3的互斥量

    // auto result1 = lockAndCall(f1, f1m, 0); // 错误

    // auto result2 = lockAndCall(f2, f2m, NULL); // 错误

    auto result3 = lockAndCall(f3, f2m, nullptr); // 正确

    return 0;
}

/* EOF */
