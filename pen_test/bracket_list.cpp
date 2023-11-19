// 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

#include <iostream>
#include <string>
#include <deque>

void create(int n, std::deque<std::string>& output)
{
    output.push_back("()");

    for (int i = 1; i < n; i++) {
        while (output.begin()->size() == i * 2) {
            std::string bracket_list = output.front();
            output.pop_front();

            bool find_left = false;
            for (int j = bracket_list.size() - 1; j >= 0; j--) {
                if (find_left) {
                    break;
                }

                if (bracket_list[j] == ')') {
                    std::string tmp = bracket_list;
                    tmp.insert(j + 1, "()");
                    output.push_back(tmp);

                    std::cout << tmp << std::endl;
                }
                else {
                    if (!find_left) {
                        std::string tmp = bracket_list;
                        tmp.insert(j + 1, "()");
                        output.push_back(tmp);
                        find_left = true;

                        std::cout << tmp << std::endl;
                    }
                }
            }
        }
    }
}

int main(int argc, char** argv)
{
    int n = 4;
    std::deque<std::string> output_list;

    create(n, output_list);

    // print
    std::cout << "[ ";

    for (auto it = output_list.begin(); it != output_list.end(); ++it) {
        std::cout << *it << " ";
    }

    std::cout << "]" << std::endl;

    return 0;
}
