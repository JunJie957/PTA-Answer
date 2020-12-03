#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAXV = 510;
const int INF = 1000000000;

int n, m, Cmax, Sp, numPath = 0;
int minNeed = INF;      // ����Я����Ŀ
int minRemain = INF;    // ���ٴ�����Ŀ
int weight[MAXV];       // ��Ȩ
int d[MAXV];  // ��¼��̾���
int G[MAXV][MAXV]; // �ڽӾ���
bool vis[MAXV] = { false };  // ��¼�����Ƿ񱻷���
vector<int> path;  // ����·��
vector<int> tempPath;  // ��ʱ·��
vector<int> pre[MAXV]; // ǰ��

void Dijkstra(int s) {
    fill(d, d + MAXV, INF);
    d[s] = 0;
    for (int i = 0; i <= n; ++i) {
        int u = -1, MIN = INF;
        for (int j = 0; j <= n; ++j) {
            if (vis[j] == false && d[j] < MIN) {
                u = j;
                MIN = d[j];
            }
        }
        if (u == -1) return;
        vis[u] = true;
        for (int v = 0; v <= n; ++v) {
            if (vis[v] == false && G[u][v] != INF) {
                if (d[u] + G[u][v] < d[v]) {
                    d[v] = d[u] + G[u][v];
                    pre[v].clear();
                    pre[v].emplace_back(u);
                } else if (d[u] + G[u][v] == d[v]) {
                    pre[v].emplace_back(u);
                }
            }
        }
    }
}

void DFS(int v) {
    if (v == 0) {
        tempPath.emplace_back(v);
        int need = 0, remain = 0;
        for (int i = tempPath.size() - 1; i >= 0; --i) {
            int id = tempPath[i];
            if (weight[id] > 0) {
                remain += weight[id];
            } else {
                if (remain > abs(weight[id])) {
                    remain -= abs(weight[id]);
                } else {
                    need += abs(weight[id]) - remain;
                    remain = 0;
                }
            }
        }
        if (need < minNeed) {
            minNeed = need;
            minRemain = remain;
            path = tempPath;
        } else if (need == minNeed && remain < minRemain) {
            minRemain = remain;
            path = tempPath;
        }
        tempPath.pop_back();
        return;
    }
    tempPath.emplace_back(v);
    for (int i = 0; i < pre[v].size(); ++i) {
        DFS(pre[v][i]);
    }
    tempPath.pop_back();
}
int main() {
    fill(G[0], G[0] + MAXV * MAXV, INF);
    scanf("%d%d%d%d", &Cmax, &n, &Sp, &m);
    int u, v;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &weight[i]);
        weight[i] -= Cmax / 2;
    }
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &u, &v);
        scanf("%d", &G[u][v]);
        G[v][u] = G[u][v];
    }
    Dijkstra(0);
    DFS(Sp);
    printf("%d ", minNeed);
    for (int i = path.size() - 1; i >= 0; --i) {
        printf("%d", path[i]);
        if (i > 0) printf("->");
    }
    printf(" %d", minRemain);
    return 0;
}