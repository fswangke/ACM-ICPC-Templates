namespace KM {
	int n, m, ans; // `left` && `right`
	int L[MAX_LEFT], R[MAX_RIGHT], v[MAX_RIGHT];
	bool bx[MAX_LEFT], by[MAX_RIGHT];
	bool find(int x) {
		bx[x] = true; for (edge e(fir[x]); e; e = e->next) {
			int y = e->to, c = e->c;
			if (!by[y] && L[x] + R[y] == c) {
				by[y] = true;
				if (!v[y] || find(v[y])) { v[y] = x; return true; }
			}
		} return false;
	}
	int km() {
		memset(L, 0, sizeof(L)); memset(R, 0, sizeof(R)); memset(v, 0, sizeof(v));
		for (int x = 1; x <= n; ++x) for (edge e(fir[x]); e; e = e->next)
			L[x] = max(L[x], e->c);
		ans = 0;
		for (int i = 1; i <= min(n, m); ++i) for ( ; ; ) {
			memset(bx, 0, sizeof(bx)); memset(by, 0, sizeof(by));
			if (find(i)) break; int Min = INF;
			for (int x = 1; x <= n; ++x) if (bx[x])
				for (edge e(fir[x]); e; e = e->next) {
					if (!by[e->to]) Min = min(Min, L[x] + R[e->to] - e->c);
				}
				for (int x = 1; x <= n; ++x) if (bx[x]) L[x] -= Min;
				for (int y = 1; y <= m; ++y) if (by[y]) R[y] += Min;
			}
		for (int x = 1; x <= n; ++x) for (edge e(fir[x]); e; e = e->next)
			if (v[e->to] == x) ans += e->c;
		return ans;
	}
}