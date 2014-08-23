/*
	test on bzoj 2648 and bzoj 2716
	`曼哈顿最短路，改成欧几里得只需把sqr改为 x*x 正常即可`
	`支持插入，查询`
	`如果要用long long，把LL改为long long即可`
*/
struct Point { int x, y; };
inline LL sqr(int x) { return abs(x); }
inline LL dist(const Point &a, const Point &b) { return sqr(a.x - b.x) + sqr(a.y - b.y); }

struct Rectangle {
	int lx , rx , ly , ry;
	void set(const Point &p) {
		lx = rx = p.x;
		ly = ry = p.y;
	}
	void merge(const Point &o) {
		lx = min(lx, o.x);
		rx = max(rx, o.x);
		ly = min(ly, o.y);
		ry = max(ry, o.y);
	}
	void merge(const Rectangle &o) {
		lx = min(lx , o.lx);
		rx = max(rx , o.rx);
		ly = min(ly , o.ly);
		ry = max(ry , o.ry);
	}
	LL dist(const Point &p) {
		LL res = 0;
		if (p.x < lx) res += sqr(lx - p.x);
		else if (p.x > rx) res += sqr(p.x - rx);

		if (p.y < ly) res += sqr(ly - p.y);
		else if (p.y > ry) res += sqr(p.y - ry);
		return res;
	}
};

struct Node {
	int child[2];
	Point p;
	Rectangle rect;
};

const int MAX_N = 1111111;
const LL INF = 100000000;
int n, m, tot, root;
Point a[MAX_N];
Node tree[MAX_N];
Point p;
LL result;

bool cmpX(const Point &a, const Point &b) {
	if (a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

bool cmpY(const Point &a, const Point &b) {
	if (a.y != b.y) return a.y < b.y;
	return a.x < b.x;
}

int build(int s, int t, bool d) {
	int k = ++tot;
	int mid = (s + t) >> 1;
	nth_element(a + s, a + mid , a + t, d ? cmpX : cmpY);
	tree[k].p = a[mid];
	tree[k].rect.set(a[mid]);
	tree[k].child[0] = tree[k].child[1] = 0;
	if (s < mid) {
		tree[k].child[0] = build(s, mid , d ^ 1);
		tree[k].rect.merge(tree[tree[k].child[0]].rect);
	}
	if (mid + 1 < t) {
		tree[k].child[1] = build(mid + 1, t, d ^ 1);
		tree[k].rect.merge(tree[tree[k].child[1]].rect);
	}
	return k;
}

int insert(int root, bool d) {
	if (root == 0) {
		++tot;
		tree[tot].p = p;
		tree[tot].rect.set(p);
		tree[tot].child[0] = tree[tot].child[1] = 0;
		return tot;
	}
	tree[root].rect.merge(p);
	if ((d && cmpX(p, tree[root].p)) || (!d && cmpY(p, tree[root].p))) {
		tree[root].child[0] = insert(tree[root].child[0], d ^ 1);
	} else {
		tree[root].child[1] = insert(tree[root].child[1], d ^ 1);
	}
	return root;
}

void query(int k, bool d) {
	if (tree[k].rect.dist(p) >= result)
		return;
	int temp = dist(tree[k].p, p);
	if (temp < result)
		result = temp;
	if ((d && cmpX(p, tree[k].p)) || (!d && cmpY(p, tree[k].p))) {
		if (tree[k].child[0])
			query(tree[k].child[0], d ^ 1);
		if (tree[k].child[1])
			query(tree[k].child[1], d ^ 1);
	} else {
		if (tree[k].child[1])
			query(tree[k].child[1], d ^ 1);
		if (tree[k].child[0])
			query(tree[k].child[0], d ^ 1);
	}
}

int main() {
	for (int tests = 1; tests --; ) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; ++i) {
			scanf("%d%d", &a[i].x, &a[i].y);
		}
		root = tot = 0;
		root = build(0, n, 0);
		for (int i = 0; i < m; ++i) {
			int type, px, py;
			scanf("%d %d %d", &type, &px, &py);
			p.x = px; p.y = py;
			if (type == 1) {
				root = insert(root, 0);
			} else {
				result = INF;
				query(root, 0);
				printf("%d\n", result);	
			}
		}
	}
}
