#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
const int inf = 1e9 + 10;

int n, m, s, t, dist[N];
bool vis[N];
vector<int> G[N], Sh[N];

void bfs() {
    fill(dist, dist + n+1, inf);
    dist[s] = 0;
    vis[s] = true;

    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (auto u : G[v]) {
            if (!vis[u]) {
                vis[u] = true;
                q.push(u);
                dist[u] = dist[v] + 1;
            }
        }
    }
}

void tworz(int v) {
    if (!dist[v]) return;
    vis[v] = true;
    for (auto u : G[v]) {
        if (!vis[u] && dist[u] == dist[v] - 1) {
            Sh[u].push_back(v);
            tworz(u);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
        
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        G[v].push_back(v);
        G[u].push_back(u);
    }

    bfs();
    
    fill(vis, vis + n+1, false);
    tworz(t);
} 
