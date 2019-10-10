#include<bits/stdc++.h>
#define pb push_back
#define N 100002
using namespace std;

int n1, n2, m, match[N*2], dis[N];
vector<int> G[N];
queue<int> q;
bool vis[N];

void init() {
	scanf("%d%d%d", &n1, &n2, &m);
	for(int i = 0 ; i < m ; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].pb(v + n1);
	}
}

void bfs() {
	memset(vis, 0, sizeof(vis));
	for(int i = 1 ; i <= n1 ; ++i) {
		if(match[i] == 0) {
			q.push(i);
			dis[i] = 0;
		}
	}
	while(!q.empty()) {
		int v = q.front();
		q.pop();
		vis[v] = true;
		for(auto u : G[v]) {
			int w = match[u];
			if(w && !vis[w]) {
				q.push(w);
				dis[w] = dis[v] + 1;
			}
		}
	}
}

bool dfs(int v) {
	vis[v] = true;	
	for(auto u : G[v]) {
		int w = match[u];
		if(w == 0) {
			match[u] = v;
			match[v] = u;
			return true;
		}if(!vis[w] && dis[w] == dis[v] + 1 && dfs(w)) {
			match[u] = v;
			match[v] = u;
			return true;
		}
	}
	return false;
}

bool Find() {
	bfs();
	bool ret = false;
	memset(vis, 0, sizeof(vis));
	for(int i = 1 ; i <= n1 ; ++i) {
		if(!vis[i] && !match[i] && dfs(i))
			ret = true;
	}
	return ret;
}

void solve() {
	init();
	while(Find());
}