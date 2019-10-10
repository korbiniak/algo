#include<bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define st first
#define nd second
#define N 100003
using namespace std;

//inSCC to numery SCC do którego należy wierzchołek i
//deg to stopien wejsciowy SCC o indeksie i
//size to rozmai i-tego scc
//ans to odpowiedz dla i-tego scc
int n, m, cnt = 0, inSCC[N], deg[N], size[N], ans[N];

//graf o normalnych i odwroconych krawedziach
vector<int> G[N], Rev[N];

//graf SCC - scc o numerze i ma krawedz z wierzcholka v (first) do wiercholka u (second)
vector<pair<int,int>> SCC[N];

stack<int> S;
queue<int> q;
bool vis[N];

void DFS(int v) {
	vis[v] = true;
	for(auto u : G[v]) {
		if(!vis[u])
			DFS(u);
	}
	S.push(v);
}

void rDFS(int v) {
	inSCC[v] = cnt;
	size[cnt]++;
	for(auto u : Rev[v]) {
		if(!inSCC[u])
			rDFS(u);
	}
}

void sDFS(int v) {
	vis[v] = true;
	for(auto u : G[v]) {
		if(inSCC[v] != inSCC[u]) {
			SCC[inSCC[v]].pb(mp(v, u));
			deg[inSCC[u]]++;
		}
		if(!vis[u])
			sDFS(u);
	}
}

void genSCC() {
	for(int i = 1; i <= n; ++i)
		if(!vis[i])
			DFS(i);
	while(!S.empty()) {
		int v = S.top();
		S.pop();
		if(!inSCC[v]) {
			++cnt;
			rDFS(v);
		}
	}
	fill(vis, vis + n + 1, false);
	for(int i = 1; i <= n; ++i) {
		if(!vis[i])
			sDFS(i);
	}
}

void init() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].pb(v);
		Rev[v].pb(u);
	}
}

int main() {
	init();
	genSCC();
	topo();
}