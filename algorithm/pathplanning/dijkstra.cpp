// https://www.bilibili.com/video/BV1zz4y1m7Nq/?spm_id_from=333.788.recommend_more_video.0&vd_source=0f664d4ed901ea333a9711b8273fbfa3
// 视频介绍单源最短路径算法—Dijkstra算法

#include <cstdio>
#include <vector>

static const int N = 10000;
static const int CNT_MAX = 9;
static char NODE[CNT_MAX] = { '0', '1', '2', '3', '4', '5', '6', '7', '8' };
static int WEIGHT[CNT_MAX * CNT_MAX] = {
        /*0*//*1*//*2*//*3*//*4*//*5*//*6*//*7*//*8*/
    /*0*/ 0,   4,   N,   N,   N,   N,   N,   8,   N,
    /*1*/ 4,   0,   8,   N,   N,   N,   N,   11,  N,
    /*2*/ N,   8,   0,   7,   N,   4,   N,   N,   2,
    /*3*/ N,   N,   7,   0,   9,   14,  N,   N,   N,
    /*4*/ N,   N,   N,   9,   0,   10,  N,   N,   N,
    /*5*/ N,   N,   4,   14,  10,  0,   2,   N,   N,
    /*6*/ N,   N,   N,   N,   N,   2,   0,   1,   6,
    /*7*/ 8,   11,  N,   N,   N,   N,   1,   0,   7,
    /*8*/ N,   N,   2,   N,   N,   N,   6,   7,   0
};

template<typename T>
bool exist(std::vector<T> S, T item)
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
 * @param nodes     顶点集合
 * @param weight    邻接矩阵
 * @return none
 */
void dijkstraAlg(int source, char* node, int* weight)
{
    int dist[CNT_MAX] = {0};
    char pre[CNT_MAX] = {0};
    std::vector<char> close;

    // 初始化
    for (int i = 0; i < CNT_MAX; i++) {
        dist[i] = weight[source * CNT_MAX + i];
        pre[i] = node[source];
    }
    close.push_back(node[source]);

    // 查找所有的节点
    while (close.size() != CNT_MAX) {
        int min = N;
        int index = -1;

        // 添加node到close中
        for (int i = 0; i < CNT_MAX; i++) {
            if (!exist(close, node[i])
                && dist[i] < min) {
                min = dist[i];
                index = i;
            }
        }
        close.push_back(node[index]);

        // 更新dist
        for (int i = 0; i < CNT_MAX; i++) {
            if (!exist(close, node[i])
                && dist[index] + weight[index * CNT_MAX + i] < dist[i]) {
                dist[i] = dist[index] + weight[index * CNT_MAX + i];
                pre[i] = node[index];
            }
        }
    }

    // Output
    for (int i = 0; i < CNT_MAX; i++) {
        printf("%c -> %c = %d pre[%c]\n", node[source], node[i], dist[i], pre[i]);
    }
}

int main(int argc, char** argv)
{
    int source = 4;
    dijkstraAlg(source, NODE, WEIGHT);

    return 0;
}
