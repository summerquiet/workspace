#include <cstdio>
#include <vector>

static const int INF = 100000;
static const int VER_CNT = 7;
                                     /*  0    1    2    3    4    5    6*/
static const char VERTEXTES[VER_CNT] = {'s', 'a', 'b', 'c', 'd', 'e', 'f' };
static const int EDG_CNT = 12;
static const int EDGES[EDG_CNT][3] = {
    {0, 1, 3},
    {0, 5, 4},
    {1, 2, 12},
    {1, 5, 7},
    {2, 4, 1},
    {2, 6, 2},
    {3, 0, 6},
    {3, 5, 8},
    {4, 3, 10},
    {4, 6, 3},
    {5, 2, 5},
    {5, 4, -2}
};

bool bellman_ford(const char* vertexes, int ver_cnt, const int edges[][3], int edg_cnt, int source, std::vector<int>& dist, std::vector<int>& parent)
{
    // Initiaize
    dist = std::vector<int>(VER_CNT, INF);
    dist[source] = 0;
    parent = std::vector<int>(VER_CNT, -1);

    // Find all other vertex (V-1)
    for (int i = 0; i < ver_cnt - 1; i++) {
        // Find all edges
        for (int j = 0; j < edg_cnt; j++) {
            int u = edges[j][0];
            int v = edges[j][1];
            int w = edges[j][2];
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }
    
    // Check cycle exist
    for (int j = 0; j < edg_cnt; j++) {
        int u = edges[j][0];
        int v = edges[j][1];
        int w = edges[j][2];
        if (dist[v] > dist[u] + w) {
            return false;
        }
    }

    return true;
}

int main(int acgc, char** argv)
{
    std::vector<int> dist;
    std::vector<int> parent;
    int source = 0;

    bool ret = bellman_ford(VERTEXTES, VER_CNT, EDGES, EDG_CNT, source, dist, parent);
    if (!ret) {
        printf("negtive cycle exist\n");
        return -1;
    }
    
    for (int i = 0; i < VER_CNT; i++) {
        printf("%c -> %c dist = %d\n", VERTEXTES[source], VERTEXTES[i], dist[i]);
    }

    return 0;
}
