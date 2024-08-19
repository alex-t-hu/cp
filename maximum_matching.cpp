// hopcroft-karp algorithm
// bfs to find shortest non-overlapping augmenting paths
// dfs to adjust matching via these paths

#include <bits/stdc++.h>
using namespace std;

#define MAXV 100010

// N = number of nodes on left-half of bitartite graph, M = number of edges
int matching[MAXV], dist[MAXV], N, M;
vector<int> adj[MAXV];

bool dfs(int x) {
    for (int y: adj[x]) {
        if (matching[y] == -1 || (dist[matching[y]] == dist[x] + 1 && dfs(matching[y]))) {
            matching[y] = x;
            matching[x] = y;
            return true;
        }
    }
    return false;
}

bool bfs() {
    queue<int> q;
    memset(dist, -1, sizeof(dist));

    for (int i = 0; i < N; i++) {
        if (matching[i] == -1) {
            q.push(i);
            dist[i] = 0;
        }
    }
    bool exist_augmenting_path = false;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int y: adj[x]) {
            if (matching[y] == -1) {
                exist_augmenting_path = true;
            } else if (dist[matching[y]] == -1) {
                dist[matching[y]] = dist[x] + 1;
                q.push(matching[y]);
            }
        }
    }
    return exist_augmenting_path;
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v + N);
        adj[v + N].push_back(u);
    }
    int ans = 0;
    memset(matching, -1, sizeof(matching));
    while (bfs()) {
        for (int i = 0; i < N; i++) {
            if (matching[i] == -1) {
                dfs(i);
                ans ++;
            }
        }
    }
    cout << ans << "\n";
}