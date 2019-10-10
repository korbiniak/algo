#include<bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define st first
#define nd second
#define N 100004
using namespace std;
typedef long long LL;

const int MAXK = 21;

int n, anc[MAXK][N], pre[N], post[N], cnt = 0, cnt2 = 0, lvl[N];
vector<int> G[N];

void DFS(int v, int f) {
	lvl[v] = lvl[f] + 1;
	anc[0][v] = f;
	pre[v] = ++cnt;
	for(auto u : G[v]) 
		if(u != f) 
			DFS(u, v);
	post[v] = ++cnt2;
}

bool isAnc(int v, int u) { //czy v jest przodkiem u
	return (pre[u] >= pre[v] && post[u] <= post[v]) ? true : false;
}

void genLCA() {	
	for(int i = 1; i < MAXK; ++i) 
		for(int j = 1; j <= n; ++j)
			anc[i][j] = anc[i - 1][anc[i - 1][j]];
}

int LCA(int v, int u) {
	int k = MAXK;
	while(k > 0) {
		int w = anc[k - 1][v];
		if(!isAnc(w, u) && w != 0) 
			v = w;
		--k;
	}
	if(isAnc(v, u))
		return v;
	return anc[0][v];
}

void init() {
	scanf("%d", &n);
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].pb(v);
		G[v].pb(u);
	}
}

int main() {
	init();
	DFS(1, 0);
	//jesli pamietasz o tej linijce, to nie musisz w 39 dodawać tego && w != 0
	post[0] = ++cnt2;
	genLCA();
}