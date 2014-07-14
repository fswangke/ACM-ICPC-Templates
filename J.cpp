#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

#define MAXN 300033
#define Foru(i, a, b) for(int i = (a); i < (b); ++i)

#define EPS 1e-7
#define PI 3.1415926535897932384626

inline int sign(const double &a, const double &eps = EPS) { return a < -eps ? -1 : int(a > eps); }
inline double sqr(const double &x) { return x * x; }
inline double Sqrt(const double &x) { return x < 0 ? 0 : sqrt(x); }

inline double arcSin(const double &a) {
	if (sign(a + 1) <= 0) return -PI / 2;
	if (sign(a - 1) >= 0) return PI / 2;
	return asin(a);
}

inline double arcCos(const double &a) {
	if (sign(a + 1) <= 0) return PI;
	if (sign(a - 1) >= 0) return 0;
	return acos(a);
}

struct point {
	double x, y;
	point(): x(0.0), y(0.0) {}
	point(const double &x, const double &y): x(x), y(y) {}
	point operator + (const point &rhs) const { return point(x + rhs.x, y + rhs.y); }
	point operator - (const point &rhs) const { return point(x - rhs.x, y - rhs.y); }
	point operator * (const double &k) const { return point(x * k, y * k); }
	point operator / (const double &k) const { return point(x / k, y / k); }
	double len() const { return hypot(x, y); }
	double norm() const { return x * x + y * y; }
	point unit() const { double k = len(); return point(x / k, y / k); }
	point rot(const double &a) const { return point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
	friend double dot(const point &a, const point &b) { return a.x * b.x + a.y * b.y; }
	friend double det(const point &a, const point &b) { return a.x * b.y - a.y * b.x; }
	friend double dist(const point &a, const point &b, const point &c) { // dist from C to AB
		return fabs(det(a - c, b - c) / (a - b).len());
	}
	friend double angle(const point &a, const point &b) { // angle between a and b
		return arcCos(dot(a, b) / a.len() / b.len());
	}
};

bool onSeg(const point &a, const point &b, const point &c) { // C is not strict on AB
	return sign(dot(a - c, b - c)) <= 0 && sign(det(b - a, c - a)) == 0;
}

bool lineIntersect(const point &a, const point &b, const point &c, const point &d, point &e) {
	double s1 = det(c - a, d - a);
	double s2 = det(d - b, c - b);
	if (!sign(s1 + s2)) return 0;
	e = (b - a) * (s1 / (s1 + s2)) + a;
	return 1;
}

bool segIntersect(const point &a, const point &b, const point &c, const point &d, point &e) {
	double s1 = det(c - a, d - a), s2 = det(d - b, c - b);
	if (!sign(s1 + s2)) return 0;
	e = (b - a) * (s1 / (s1 + s2)) + a;
	return onSeg(a, b, e) && onSeg(c, d, e);
}

// returns 0 if not intersect, 1 if proper intersect, 2 if improper intersect
int iCnt;
int segIntersectCheck(const point &a, const point &b, const point &c, const point &d, point &o) {
	static double s1, s2, s3, s4;
	int d1 = sign(s1 = det(b - a, c - a)), d2 = sign(s2 = det(b - a, d - a));
	int d3 = sign(s3 = det(d - c, a - c)), d4 = sign(s4 = det(d - c, b - c));
	if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2) {
		o = (c * s2 - d * s1) / (s2 - s1);
		return 1;
	}
	iCnt = 0;
	if (d1 == 0 && onSeg(c, a, b)) o = c, ++iCnt;
	if (d2 == 0 && onSeg(d, a, b)) o = d, ++iCnt;
	if (d3 == 0 && onSeg(a, c, d)) o = a, ++iCnt;
	if (d4 == 0 && onSeg(b, c, d)) o = b, ++iCnt;
	return iCnt ? 2 : 0;
}

struct Border {
	point p1, p2; double alpha;
	Border() : p1(), p2(), alpha(0.0) {}
	Border(const point &a, const point &b):
		p1(a), p2(b), alpha( atan2(p2.y - p1.y, p2.x - p1.x) ) {}
	bool operator == (const Border &b) const {
		return sign(alpha - b.alpha) == 0;
	}
	bool operator < (const Border &b) const {
		int c = sign(alpha - b.alpha);
		if (c != 0) return c == 1;
		return sign(det(b.p2 - b.p1, p1 - b.p1)) >= 0;
	}
};

point isBorder(const Border &a, const Border &b) {
	point res;
	lineIntersect(a.p1, a.p2, b.p1, b.p2, res);
	return res;
}

inline bool checkBorder(const Border &a, const Border &b, const Border &me) {
	point is;
	lineIntersect(a.p1, a.p2, b.p1, b.p2, is);
	return sign(det(me.p2 - me.p1, is - me.p1)) > 0;
}

double HPI(int N) {
	static Border border[MAXN];

	// init
	Foru(i, 0, N) border[i] = Border( borders1[i], borders2[i] );

	// do intersection
	static Border que[MAXN];
	int head = 0, tail = 0; // [head, tail)
	sort(border, border + N);
	N = unique(border, border + N) - border;
	for (int i = 0; i < N; ++i) {
		Border cur = border[i];
		while (head + 1 < tail && !checkBorder(que[tail - 2], que[tail - 1], cur)) --tail;
		while (head + 1 < tail && !checkBorder(que[head], que[head + 1], cur)) ++head;
		que[tail++] = cur;
	}
	while (head + 1 < tail && !checkBorder(que[tail - 2], que[tail - 1], que[head])) --tail;
	while (head + 1 < tail && !checkBorder(que[head], que[head + 1], que[tail - 1])) ++head;

	// calc intersection points
	static point ps[MAXN];
	int cnt = 0;
	if (tail - head <= 2)
		return 0.0;
	Foru(i, head, tail)
		ps[cnt++] = isBorder(que[i], que[(i + 1 == tail) ? (head) : (i + 1)]);

	// calc area
	double area = 0;
	Foru(i, 0, cnt) area += det(ps[i], ps[(i + 1) % cnt]);
	return -area * 0.5;
}

int n;
int build(int ans)
{
	int cnt = 0;
	for(int i = 0; i < n; ++i)
	{
		borders1[cnt] = ch[(i + 1) % n];
		borders2[cnt++] = ch[i];
	}
	for(int i = 0; i < n; ++i)
	{
		borders1[cnt] = ch[(i + ans + 1) % n];
		borders2[cnt++] = ch[i];
	}
	return cnt;
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%lf%lf", &ch[i].x, &ch[i].y);
		if(n == 3)
		{
			printf("1\n");
			continue;
		}
		double area = HPI(build(3));
		printf("%d %f\n", 3, area);
/*		int l = 1, r = n - 2,ans;
		while(l <= r)
		{
			int mid = (l + r) >> 1;
			double area = HPI(build(mid));
			printf("%d %f\n",mid, area);
			if(sign(area) != 0) {
				ans = mid;
				l = mid + 1;
			} else r = mid - 1;
		}
		printf("%d\n", ans);*/
	}
	return 0;
}

