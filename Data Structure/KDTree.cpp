struct Rectangle;

struct point {
	int x, y;

	point() : x(0), y(0) {
	}

	point(int x, int y) : x(x), y(y) {
	}

	bool on(const point &, const point &) const;

	bool in(point *, int) const;

	int operator [] (int i) const {
		return i ? y : x;
	}

	int& operator [] (int i) {
		return i ? y : x;
	}

	LL norm() const {
		return (LL)x * x + (LL)y * y;
	}

	LL to(const Rectangle&) const;

	point operator - (const point &b) const {
		return point(x - b.x, y - b.y);
	}
};

inline LL sqr(LL x) {
	return x * x;
}

inline LL dot(const point &a, const point &b) {
	return (LL)a.x * b.x + (LL)a.y * b.y;
}

inline LL det(const point &a, const point &b) {
	return (LL)a.x * b.y - (LL)a.y * b.x;
}

inline bool point::on(const point &a, const point &b) const {
	const point &p = *this;
	return det(a - p, b - p) == 0 && dot(a - p, b - p) <= 0;
}

inline bool point::in(point *polygon, int n) const {
	const point &p = *this;
	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		const point &a = polygon[i], &b = polygon[(i + 1) % n];
		if (p.on(a, b)) return true;
		int d0 = sign(det(b - a, p - a));
		int d1 = a.y - p.y;
		int d2 = b.y - p.y;
		cnt += d0 > 0 && d1 <= 0 && d2 > 0;
		cnt -= d0 < 0 && d2 <= 0 && d1 > 0;
	}
	return cnt != 0;
}

struct Rectangle {
	int min[2], max[2];
	Rectangle() {
		min[0] = min[1] = INT_MAX;
		max[0] = max[1] = INT_MIN;
	}

	void add(const point &p) {
		for (int i = 0; i < 2; ++i) {
			min[i] = std::min(min[i], p[i]);
			max[i] = std::max(max[i], p[i]);
		}
	}
};

LL point::to(const Rectangle &r) const {
	const point &p = *this;
	LL res = 0;
	for (int i = 0; i < 2; ++i)
		res += sqr( min(max(p[i], r.min[i]), r.max[i]) - p[i] );
	return res;
}

const int MAXN = 20033;
int n, pivot, seperator[MAXN * 2 + 1];
vector<int> order;
point points[MAXN], polygon[33];
Rectangle rec[MAXN * 2 + 1];

inline int getId(int l, int r) {
	return (l + r) | (l != r);
}

bool compare(int i, int j) {
	if (points[i][pivot] != points[j][pivot])
		return points[i][pivot] < points[j][pivot];
	return i < j;
}

void build(int l, int r, int type) {
	int id = getId(l, r);
	rec[id] = Rectangle();
	Rep(i, l, r) rec[id].add( points[ order[i] ] );
	if (l < r) {
		int m = (l + r) >> 1;
		pivot = type;
		nth_element(order.begin() + l, order.begin() + m, order.begin() + r + 1, compare);
		seperator[id] = order[m];
		build(l, m, type ^ 1);
		build(m + 1, r, type ^ 1);
	}
}

priority_queue<pair<LL, int> > answer;

void query(int l, int r, int type) {
	const point &p = points[n];
	int id = getId(l, r);
	if (answer.size() == 2 && p.to(rec[id]) > answer.top().first)
		return;
	if (l == r) {
		answer.push( make_pair((p - points[order[l]]).norm(), order[l] ) );
		if (answer.size() > 2) answer.pop();
	}
	else {
		int m = (l + r) >> 1;
		pivot = type;
		int dir = compare(seperator[id], n);
		if (dir)
			query(l, m, type ^ 1);
		query(m + 1, r, type ^ 1);
		if (!dir)
			query(l, m, type ^ 1);
	}
}

void queryTree(int size) {
	answer = priority_queue<pair<LL, int> >();
	scanf("%d %d", &points[n].x, &points[n].y);
	query(0, size - 1, 0);
	vector<pair<LL, int> > buffer;
	while (!answer.empty()) {
		buffer.push_back( answer.top() );
		answer.pop();
	}
	sort(buffer.begin(), buffer.end());
	printf("%d %d\n", buffer[0].second + 1, buffer[1].second + 1);
}

void solve() {
	int R;

	scanf("%d", &n);
	Foru(i, 0, n) scanf("%d %d", &points[i].x, &points[i].y);
	scanf("%d", &R);

	Rep(region, 1, R) {
		printf("Region %d\n", region);

		int B;
		scanf("%d", &B);
		Foru(i, 0, B) scanf("%d %d", &polygon[i].x, &polygon[i].y);

		order.clear();
		Foru(i, 0, n)
			if (points[i].in(polygon, B))
				order.push_back(i);
		int size = order.size();
		build(0, size - 1, 0);
		order.push_back(n);
		int M;
		scanf("%d", &M);
		while (M--)
			queryTree(size);
	}
}

int main() {
	int T;
	scanf("%d", &T);
	Rep(Case, 1, T) {
		printf("Case #%d:\n", Case);
		solve();
	}
	return 0;
}

