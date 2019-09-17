#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 7;
const int K = 1e6 + 7;

int n, k;
int pod[N];	//rozmiary poddrzew
bool block[N];	//blokowanie wierzcholkow
vector <pair <int, int> > G[N];

int tab[K];
int res = N;

int dfs(int u, int p){
	pod[u] = 1;
	for(auto v: G[u]){
		if(!block[v.first] && v.first != p)
			pod[u] += dfs(v.first, u);
	}

	return pod[u];
}

int Find(int u){
	int p = u;
	bool ok = true;
	int half = dfs(u, u) / 2;

	while(ok){
		ok = false;
		for(auto v: G[u])
			if(!block[v.first] && v.first != p && pod[v.first] > half){
				p = u;
				u = v.first;
				ok = true;
				break;
			}
	}

	return u;
}

void checkResult(int u, int p, int weight, int length){
	if(weight > k)
		return;

	res = min(res, length + tab[k - weight]);
	for(auto v: G[u])
		if(!block[v.first] && v.first != p)
			checkResult(v.first, u, weight + v.second, length + 1);
}

void add(int u, int p, int weight, int length){
	if(weight > k)
		return;

	tab[weight] = min(tab[weight], length);
	for(auto v: G[u])
		if(!block[v.first] && v.first != p)
			add(v.first, u, weight + v.second, length + 1);
}

void clear(int u, int p, int weight){
	if(weight > k)
		return;

	if(weight > 0)
		tab[weight] = N;

	for(auto v: G[u])
		if(!block[v.first] && v.first != p)
			clear(v.first, u, weight + v.second);
}

void Rozbicie(int u){
	u = Find(u);
	for(auto v: G[u])
		if(!block[v.first]){
			checkResult(v.first, u, v.second, 1);
			add(v.first, u, v.second, 1);
		}

	clear(u, u, 0);
	block[u] = true;

	for(auto v: G[u])
		if(!block[v.first])
			Rozbicie(v.first);
}

int main(){
	scanf("%d %d", &n, &k);
	for(int i = 1; i < n; ++i){
		int u, v, c;
		scanf("%d %d %d", &u, &v, &c);

		G[u].push_back({v, c});
		G[v].push_back({u, c});
	}

	for(int i = 1; i <= k; ++i)
		tab[i] = N;
	Rozbicie(1);

	if(res == N)
		puts("-1");
	else
		printf("%d\n", res);
	return 0;
}