vector<int> eulerianWalk(int N, int S) {
	static int res[MAXM], stack[MAXN];
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
			e = e->next; // the opposite edge must be banned if this is a bidirectional graph
		}
		res[rcnt++] = x;
	}
	reverse(res, res + rcnt);
	return vector<int>(res, res + rcnt);
}
