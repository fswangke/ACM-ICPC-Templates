
struct enode {
	int to;
	enode *next;
} ebase[MAXN * 2], *etop, *fir[MAXN];
typedef enode *edge;

inline void addEdge(int a, int b) {
	etop->to = b;
	etop->next = fir[a];
	fir[a] = etop++;
}

int N;

namespace TreeDecomposition {

	int fa[MAXN], dep[MAXN], Q[MAXN], size[MAXN], own[MAXN];

	void Decomposion() {
		static int path[MAXN];
		int x, y, a, next, head = 0, tail = 0, cnt;
		for (fa[1] = -1, dep[1] = 0, Q[++tail] = 1; head < tail;) {
			x = Q[++head];
			for (edge e(fir[x]); e; e = e->next)
				if ( (y = e->to) != fa[x] ) {
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
				next = -1;
				own[x] = a;
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
