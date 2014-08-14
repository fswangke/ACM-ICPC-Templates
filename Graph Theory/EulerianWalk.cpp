
struct enode {
	int to;
	enode *next;
} ebase[MAXM], *etop, *fir[MAXN];
typedef enode *edge;

inline void addEdge(int a, int b) {
	etop->to = b;
	etop->next = fir[a];
	fir[a] = etop++;
}

vector<int> eulerianWalk(int N, int S) {
	static int res[MAXM];
	static int stack[MAXN];
	static edge cur[MAXN];

	int rcnt = 0, top = 0;
	for (int i = 1; i <= N; ++i) cur[i] = fir[i];

	for (stack[top++] = S; top; ) {
		int x = stack[--top];
		for ( ; ; ) {
			edge &e = cur[x];
			if (e == NULL) break;
			stack[top++] = x;
			x = e->to;
			e = e->next; // reverse edge must be banned if this is a bidirectional graph
		}
		res[rcnt++] = x;
	}
	return vector<int>(res, res + rcnt);
}

