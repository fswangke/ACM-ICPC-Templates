namespace Network {
	int S, T, Ncnt, hsize, heap[MAXN], h[MAXN], inq[MAXN], Q[MAXN];
	LL E[MAXN]; edge cur[MAXN];
	inline void pushFlow(int x, int y, edge e) {
		int d = (int)min(E[x], (LL)e->c);
		E[x] -= d; e->c -= d; E[y] += d; e->op->c += d;
	} inline bool heapCmp(int x, int y) { return h[x] < h[y]; }
	inline void hpush(int x) {
		inq[x] = true; heap[++hsize] = x;
		push_heap(heap + 1, heap + hsize + 1, heapCmp);
	} inline void hpop(int x) {
		inq[x] = false; pop_heap(heap + 1, heap + hsize + 1, heapCmp); --hsize;
	} int maxFlow() {
		int head = 0, tail = 0, x, y;
		memset(h, 63, sizeof(int) * (Ncnt + 1));
		memset(E, 0, sizeof(LL) * (Ncnt + 1));
		memset(inq, 0, sizeof(int) * (Ncnt + 1));
		memcpy(cur, fir, sizeof(edge) * (Ncnt + 1));
		for (Q[++tail] = T, h[T] = 0; head < tail; )
			for (edge e(fir[x = Q[++head]]); e; e = e->next) if (e->op->c)
				if (h[y = e->to] >= INF) h[y] = h[x] + 1, Q[++tail] = y;
		if (h[S] >= Ncnt) return 0;
		hsize = 0; E[S] = LL_INF;
		for (edge e(fir[S]); e; e = e->next) if (e->c) {
			pushFlow(S, y = e->to, e);
			if (!inq[y]) hpush(y);
		} while (hsize) {
			bool good = false;
			for (edge &e(cur[x = heap[1]]); e && E[x]; e = e->next) if (e->c)
				if (h[x] == h[y = e->to] + 1) {
					good = true, pushFlow(x, y, e);
					if (E[x] == 0) hpop(x);
					if (inq[y] == false && y != S && y != T) hpush(y);
					break;
				}
			if (!good) { // relabel
				int &minH = h[x] = INF; cur[x] = NULL; hpop(x);
				for (edge e(fir[x]); e; e = e->next) if (e->c)
					if ( cMin(minH, h[e->to] + 1) ) cur[x] = fir[x];
				hpush(x);
			}
		} return E[T];
	}
}
