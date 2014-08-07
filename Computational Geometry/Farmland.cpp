
struct node {
	int begin[MAXN], *end;
} a[MAXN];

int n, m, S;
bool visit[MAXN][MAXN];
point p[MAXN];

inline bool cmp(const int &a, const int &b) {
	return sign(atan2(p[a].y - p[S].y, p[a].x - p[S].x)
			  - atan2(p[b].y - p[S].y, p[b].x - p[S].x)) < 0;
}

void init() {
	scanf("%d", &n);
	Rep(i, 1, n) Rep(j, 1, n) visit[i][j] = 0;
	Rep(i, 1, n) a[i].end = a[i].begin;
	Rep(i, 1, n) {
		int d;
		scanf("%d", &d);
		scanf("%lf%lf", &p[i].x, &p[i].y);
		scanf("%d", &d);
		Rep(j, 1, d) scanf("%d", a[i].end++);
	}
	scanf("%d", &m);
	for (S = 1; S <= n; ++S) sort(a[S].begin, a[S].end, cmp);
}

bool check(int b1, int b2) {
	static pii l[MAXN * 2 + 1];
	static bool valid[MAXN];
	double area = 0;
	int tp = 0, *k;
	l[0] = pii(b1, b2);
	for ( ; ; ) {
		int p1 = l[tp].first, p2 = l[tp].second;
		visit[p1][p2] = true;
		area += det(p[p1], p[p2]);
		for (k = a[p2].begin; k != a[p2].end; ++k) if (*k == p1) break;
		k = (k == a[p2].begin) ? (a[p2].end - 1) : (k - 1);
		l[++tp] = pii(p2, *k);
		if (l[tp] == l[0]) break;
	}
	if (sign(area) < 0 || tp < 3 || tp != m) return 0;
	Rep(i, 1, n) valid[i] = false;
	for (int i = 0; i < tp; i++) {
		int p = l[i].first;
		if (valid[p]) return 0;
		valid[p] = 1;
	}
	return 1;    
}

void work() {
	int ans = 0;
	Rep(x, 1, n) {
		for (int *itr = a[x].begin; itr != a[x].end; ++itr) {
			int y = *itr;
			if (visit[x][y]) continue;
			if (check(x, y)) ++ans;
		}
	}
	printf("%d\n", ans);      
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		init();
		work();
	}
	return 0;
}

