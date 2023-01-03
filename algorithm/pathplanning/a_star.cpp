// https://blog.csdn.net/dujuancao11/article/details/109749219

#include <cstdio>
#include <vector>

using namespace std;

/*
Map:
   0  1  2  3  4  5  6  7  8
  |-------------------------|
0 |0, 0, 0, 0, 0, 0, 0, 0, 0|
1 |0, 0, 0, 0, 1, 0, 0, 0, 0|
2 |0, 0, S, 0, 1, 0, E, 0, 0|
3 |0, 0, 0, 0, 1, 0, 0, 0, 0|
4 |0, 0, 0, 0, 0, 0, 0, 0, 0|
5 |0, 0, 0, 0, 0, 0, 0, 0, 0|
  |-------------------------|

From: S
To: E
1: means block
*/

static const int MAP_M = 6;
static const int MAP_N = 9;
static const int MAP[MAP_M][MAP_N] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 2, 0, 1, 0, 3, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}
};

bool a_star(vector<vector<int>>& map, vector<int>& start, vector<int>& end)
{
    return false;
}

int main(int argc, char** argv)
{
    vector<vector<int>> map;
    for (int i = 0; i < MAP_M; i++) {
        vector<int> tmp;
        for (int j = 0; j < MAP_N; j++) {
            tmp.push_back(MAP[i][j]);
        }
        map.push_back(tmp);
    }

    vector<int> start = vector<int>({2, 2});
    vector<int> end = vector<int>({2, 6});

    if (!a_star(map, start, end)) {
        printf("A* cannot find a route\n");
        return -1;
    }

    printf("A* can find a route\n");
    return 0;
}
