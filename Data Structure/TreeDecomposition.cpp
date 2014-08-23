namespace TreeDecomposition {
	int N, fa[MAXN], dep[MAXN], Q[MAXN], size[MAXN], own[MAXN];
	int LCA(int x, int y) {
		if (x == y) return x;
		for ( ; ; ) {
			if (dep[x] < dep[y]) swap(x, y);
			if (own[x] == own[y]) return y;
			if (dep[own[x]] < dep[own[y]]) swap(x, y);
			x = fa[own[x]];
		}
		return -1;
	}
	void Decomposion() {
		static int path[MAXN];
		int x, y, a, next, head = 0, tail = 0, cnt;
		for (fa[1] = -1, dep[1] = 0, Q[++tail] = 1; head < tail; ) {
			x = Q[++head];
			for (edge e(fir[x]); e; e = e->next) if ( (y = e->to) != fa[x] ) 
				dep[y] = dep[x] + 1;
				fa[y] = x;
				Q[++tail] = y;
			}
		}
		for (int i = N; i >= 1; --i) {
			int &res = size[x = Q[i]] = 1;
			for (edge e(fir[x]); e; e = e->next) if ( (y = e->to) != fa[x] )
				res += size[y];
		}
		for (int i = 1; i <= N; ++i) own[i] = -1;
		for (int i = 1; i <= N; ++i) if (own[a = Q[i]] == -1)
			for (x = a, cnt = 0; ; x = next) {
				next = -1; own[x] = a;
				path[++cnt] = x; // heavy path
				for (edge e(fir[x]); e; e = e->next) if ( (y = e->to) != fa[x] )
					if (next == -1 || size[y] > size[next])
						next = y;
				if (next == -1) {
					tree[a].init(cnt, path); // init the segment tree
					break;
				}
			}
	}
}