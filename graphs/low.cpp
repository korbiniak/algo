#include<bits/stdc++.h>
#define N 100004
using namespace std;
typedef long long LL;

int n, m, pre[N], low[N], ile[N], cnt = 0;
bool art[N], vis[N];
vector<int> G[N];
int sub[N];

//low wierzcholka v to minimum z jego preorderu, low jego synow w drzewie DFS
//i preorderow juz odwiedzonych wierzcholkow

//punktem artykulacji jest sie wtedy gdy:
//a) jestem rootem drzewa DFS i mam wiecej niz 1 syna
//b) moj preorder jest wiekszy rowny od low ktoregos z moich synow

//krawedz v-u jest mostem, o ile w drzewie DFS v jest ojcem u oraz low[u] > pre[v]

void DFS(int v, int f) {
	vis[v] = true;
	pre[v] = ++cnt;
	low[v] = pre[v];
	sub[v] = 1;
	for(auto u : G[v]) {
		if(!vis[u]) {
			DFS(u, v);
			ile[v]++;
			sub[v] += sub[u];
			low[v] = min(low[v], low[u]);
			if(low[u] >= pre[v]) art[v] = true;
		}else if(u != f)
			low[v] = min(low[v], pre[u]);
	}
}