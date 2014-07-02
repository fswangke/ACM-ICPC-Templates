
int N;
point P[MAXN], Stack[MAXN];

#define goRight(o, s, e) (det(s - o, e - o) <= 0)
int Graham() {
	int len, top = 1;
	sort(P, P + N);
	Stack[0] = P[0];
	Stack[1] = P[1];
	if (N <= 2) return N;

	for (int i = 2; i < N; i++) {
		while (top && goRight(Stack[top - 1], Stack[top], P[i]))
			--top;
		Stack[++top] = P[i];
	}
	len = top;
	Stack[++top] = P[N - 2];
	for (int i = N - 3; i >= 0; i--) {
		while (top > len && goRight(Stack[top - 1], Stack[top], P[i]))
			--top;
		Stack[++top] = P[i];
	}
	return top;
}

int RC() {
	if (N == 2) return (Stack[1] - Stack[0]).norm();
	int nx, y = 1, ny, k, ans = 0;
	P[N] = P[0];
	Foru(x, 0, N) {
		nx = x + 1;
		for ( ; ; y = ny) {
			ny = (y + 1) % N;
			k = (P[nx] - P[x]) * (P[ny] - P[y]);
			if(k <= 0) break;
		}
		Up(ans, (P[x] - P[y]).norm());
		if (k == 0)
			Up(ans, (P[x] - P[ny]).norm());
	}
	return ans;
}

void Work() {
	N = Graham();
	Foru(i, 0, N) P[i] = Stack[i];
	int ans = RC();
	printf("%d\n", ans);
}
