/*
 * 条款23：理解std::move和std::forward
 */

#include <iostream>

// 一个类似std::move的函数模版
#if 0   // C++11
template<typename T>
typename std::remove_reference<T>::type&& move(T&& param)
{
    //alias declaration
    using ReturnType = typename std::remove_reference<T>::type&&;    //see Item 9
    return static_cast<ReturnType>(param);
}
#else
template<typename T>            //C++14; still in
decltype(auto) move(T && param) //namespace std
{
    using ReturnType = std::remove_reference_t<T>&&;
    return static_cast<ReturnType>(param);
}
#endif

class Widget
{

};

//process lvalues
void process(const Widget& lvalArg)
{
    std::cout << "process lvalues"
              << '\n';
}

//process rvalues
void process(Widget&& rvalArg)
{
    std::cout << "process rvalues"
              << '\n';
}

template<typename T>
void print(const T& t)
{
    std::cout << t << " ";
}

template<typename First, typename... Rest>
void makeLogEntry(const First& first, const Rest&... rests)
{
    std::cout << first << " ";
    print(rests...);
    std::cout << '\n';
}

template<typename T>
void logAndProcess(T&& param) //template that passes
                              //param to process
{
    auto now = std::chrono::system_clock::now(); // get current time
    auto time = std::chrono::system_clock::to_time_t(now);
    makeLogEntry("Calling 'process'", time);
    process(std::forward<T>(param));
}

int main(int argc, char** argv)
{
    Widget w;
    logAndProcess(w);               //call with lvalue
    logAndProcess(std::move(w));    //call with rvalue

    std::cout << "clause 22 done."
              << '\n';

    return 0;
}

/* EOF */
