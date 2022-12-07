#include <cstdio>
#include <vector>

static const int N = 10000; // 约定 10000 代表距离无穷大
static const int V_MAX = 7;
static char vertexes[V_MAX] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };    // 顶点
#if 0
static int weight[V_MAX][V_MAX] = { // 图的邻接矩阵
        /*A*//*B*//*C*//*D*//*E*//*F*//*G*/
    /*A*/{0,   5,   7,   N,   N,   N,   2},
    /*B*/{5,   0,   N,   9,   N,   N,   3},
    /*C*/{7,   N,   0,   N,   8,   N,   N},
    /*D*/{N,   9,   N,   0,   N,   4,   N},
    /*E*/{N,   N,   8,   N,   0,   5,   4},
    /*F*/{N,   N,   N,   4,   5,   0,   6},
    /*G*/{2,   3,   N,   N,   4,   6,   0}
};
#else
static int weight[V_MAX][V_MAX] = { // 图的邻接矩阵
        /*A*//*B*//*C*//*D*//*E*//*F*//*G*/
    /*A*/{0,   4,   2,   N,   N,   N,   N},
    /*B*/{4,   0,   1,   5,   N,   N,   N},
    /*C*/{2,   1,   0,   8,   10,  N,   N},
    /*D*/{N,   5,   8,   0,   2,   6,   N},
    /*E*/{N,   N,   10,  2,   0,   5,   N},
    /*F*/{N,   N,   N,   6,   5,   0,   N},
    /*G*/{N,   N,   N,   N,   N,   N,   0}
};
#endif

bool exist(std::vector<char> S, char item)
{
    for (auto it = S.begin(); it != S.end(); ++it) {
        if (*it == item) {
            return true;
        }
    }

    return false;
}

/**
 * 迪杰斯特拉算法求解最短路径问题
 * @param source    源点下标
 * @param vertexes  顶点集合
 * @param weight    邻接矩阵
 * @return int[]    源点到各顶点最短路径距离
 */
void dijkstraAlg(int source, int* dist, std::vector<char> &S)
{

    // 初始化
    for (int i = 0; i < V_MAX; i++) {
        dist[i] = weight[source][i];
    }
    S.push_back(vertexes[source]);

    // 循环找到所有的节点
    while (S.size() != V_MAX) {
        int min = N;
        int index = -1;

        for (int i = 0; i < V_MAX; i++) {
            if (!exist(S, vertexes[i])
                && dist[i] < min) {
                min = weight[source][i];
                index = i;
            }
        }
        if (dist[index] > min) {
            dist[index] = min;
        }
        S.push_back(vertexes[index]);

        for (int i = 0; i < V_MAX; i++) {
            if (!exist(S, vertexes[i])
                && dist[index] + weight[index][i] < dist[i]) {
                dist[i] = dist[index] + weight[index][i];
            }
        }
    }
}

int main(int argc, char** argv)
{
    int source = 0;
    int dist[V_MAX] = {0};
    std::vector<char> S;

    dijkstraAlg(source, dist, S);

    // 输出最短路径长度
    for (int i = 0; i < V_MAX; i++) {
        printf("%c -> %c = %d\n", vertexes[source], vertexes[i], dist[i]);
    }

    return 0;
}
