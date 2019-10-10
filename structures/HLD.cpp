struct HLD {
	static const int N = 1e5 + 10, K = 18, M = (1<<19);
	int pre[N], post[N], anc[K][N], jump[N], sub[N], cnt, n, tree[M * 2 + 3];
	vi G[N]; 

	HLD(int _n = 0) : n(_n) {
		cnt = 0;
		memset(tree, 0, sizeof(tree));
	}

	int dfs1(int v, int f) {
		anc[0][v] = f;
		sub[v] = 1;
		for(auto u : G[v])
			if(u != f)
				sub[v] += dfs1(u,v);
		return sub[v];
	}

	void dfs2(int v, int f) {
		pre[v] = ++cnt;
		jump[v] = v;
		if(pre[v] == pre[f] + 1) jump[v] = jump[f];
		if(sz(G[v]) == 1 && f != v) {
			post[v] = cnt;
			return;
		}
		int g = 0;
		for(auto u : G[v])
			if(u != f)
				g = (sub[u] > sub[g]) ? u : g;
		dfs2(g,v);
		for(auto u : G[v]) 
			if(u != f && u != g)
				dfs2(u,v);
		post[v] = cnt;
	}

	vii decomp(int u, int v) {
		vii res;
		while(true) {
			if(u == v) return res;
			if(pre[jump[u]] <= pre[v]) {
				res.pb({pre[u], pre[v] + 1});
				return res;
			}
			res.pb({pre[u], pre[jump[u]]});
			u = anc[0][jump[u]];
		}
	}

	void genLCA() {
		FOR(k, 1, K) 
			REP(i, 1, n)
				anc[k][i] = anc[k-1][anc[k-1][i]];
	}

	bool isAnc(int u, int v) {
		return (pre[v] >= pre[u] && post[v] <= post[u]); 
	}

	int LCA(int u, int v) {
		int k = K;	
		while(k-- > 0) {
			int m = anc[k][u];
			if(!isAnc(m, v)) 
				u = m;
		}
		if(isAnc(u,v)) return u;
		return anc[0][u];
	}

	void update(int l, int r, int val) {
		l += M;
		r += M;
		tree[l] += val;
		if(l != r) tree[r] += val;
		while(l/2 != r/2) {
			if(l % 2 == 0) tree[l + 1] += val;
			if(r % 2 == 1) tree[r - 1] += val;
			r /= 2, l /= 2; 
		}
	}

	int query(int w) {
		w += M;
		int res = 0;
		while(w > 0) {
			res += tree[w];
			w /= 2;
		}
		return res;
	}

	void init() {
		dfs1(1, 1);
		dfs2(1, 1);
		genLCA();
	}

	void addEdge(int u, int v) {
		G[u].pb(v);
		G[v].pb(u);
	}

	void upd(int u, int v) {
		int w = LCA(u,v);
		auto q1 = decomp(u,w), q2 = decomp(v, w);
		for(auto p : q1) 
			update(p.nd, p.st, 1);
		for(auto p : q2)
			update(p.nd, p.st, 1); 
	}

	int zap(int u, int v) {
		if(pre[u] <= pre[v]) swap(u, v);
		return query(pre[u]);
	}
};