/*
 * This is test cpp for learning STL
 * [侯捷]C++ STL 体系结构与内核分析--从平地到万丈高楼 in bilibili.com
 */

#include <iostream>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>

using namespace std;

int main(int argc, char** argv)
{
    array<int, 5> a = {1, 2, 3, 4, 5};

    sort(a.begin(), a.end(), greater<int>());

    for (array<int, 5>::iterator it = a.begin(); it != a.end(); ++it) {
        cout << *it;
    }

    cout << endl;

    return 0;
}
