#include<bits/stdc++.h>
#define N 1004
using namespace std;

int n, m, s, t, dis[N], ans = 0, M[N][N];
vector<int> G[N];
bool vis[N];

void init() {
	scanf("%d%d", &n, &m);
	for(int i = 0 ; i < m ; ++i) {
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		G[u].push_back(v);
		G[v].push_back(u);
		M[u][v] = c;
	}
	scanf("%d%d", &s, &t);
}

void bfs(int v) {
	vis[v] = true;
	dis[v] = 0;
	queue<int> q;
	q.push(v);
	while(!q.empty()) {
		v = q.front();
		q.pop();
		for(auto u : G[v]) {
			if(!vis[u] && M[v][u] > 0) {
				vis[u] = true;
				dis[u] = dis[v] + 1;
				q.push(u);
			}
		}
	}
}

int dfs(int v, int flow) {
	if(v == t) {
		ans += flow;
		return flow;
	}
	int res = 0;
	for(auto u : G[v]) {
		if(dis[v] + 1 == dis[u] && M[v][u] > 0) {
			int e = dfs(u, min(flow, M[v][u]));
			flow -= e;
			M[v][u] -= e;
			M[u][v] += e;
			res += e;
		}
		if(flow == 0)
			break;
	}
	return res;
}

bool Find() {
	memset(vis, false, sizeof(vis));
	bfs(s);
	memset(vis, false, sizeof(vis));
	return dfs(s, 1e9);
}