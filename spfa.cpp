#include <bits/stdc++.h>
using namespace std;

#define MAXV 100010
int N, M;
vector<pair<int, long long>> adj[MAXV];
long long dist[MAXV];
int cnt[MAXV], pred[MAXV];

bool spfa() {
    queue<int> q;
    q.push(0);
    memset(dist, INT64_MAX, N * sizeof(long long));
    dist[0] = 0;

    vector<bool> inq(N, false);
    inq[0] = true;

    while (!q.empty()) {
        int x = q.front(); q.pop();
        inq[x] = false;
        for (auto& [y, w]: adj[x]) {
            if (dist[y] == INT64_MAX || dist[y] > dist[x] + w) {
                dist[y] = dist[x] + w;
                pred[y] = x;
                if (!inq[y]) {
                    cnt[y]++;
                    if (cnt[y] > N) {
                        return false;
                    }
                    inq[y] = true;
                    q.push(y);
                }
            }
        }
    }
}

void get_negative_cycle() {
    int x = 0;
    for (int i = 0; i < N; i++) {
        if (cnt[i] > N) {
            x = i;
        }
    }

    vector<int> cycle;
    for (int i = 0; i < N; i++) {
        x = pred[x];
    }
    
    for (int y = x; ; y = pred[y]) {
        cycle.push_back(y);
        if (y == x && cycle.size() > 1) break;
    }
    reverse(cycle.begin(), cycle.end());
    for (int i = 0; i < cycle.size(); i++) {
        cout << cycle[i] << " ";
    }
    cout << "\n";
}