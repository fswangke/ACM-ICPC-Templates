/*
 * 1.cpp
 *
 *  Created on:
 *      Author:
 */

#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <climits>
#include <cassert>

#include <iostream>
#include <sstream>

#include <string>
#include <vector>
#include <list>
#include <deque>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <bitset>

#include <utility>
#include <numeric>
#include <functional>
#include <algorithm>

#define INF 1000000000
#define LL_INF 4000000000000000000ll

#define Lowbit(x) ((x) & (-(x)))
#define Lc(x) ((x) << 1)
#define Rc(x) (Lc(x) + 1)
#define Pow2(x) (1 << (x))
#define Contain(a, x) (((a) >> (x)) & 1)

#define Rep(i, a, b) for(int i = (a); i <= (b); ++i)
#define Til(i, a, b) for(int i = (a); i >= (b); --i)
#define Foru(i, a, b) for(int i = (a); i < (b); ++i)
#define Ford(i, a, b) for(int i = (a); i > (b); --i)

#define It iterator
#define For(i, x) for(__typeof(x.begin()) i = x.begin(); i != x.end(); ++i)

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef pair<int, int> pii;
typedef vector<int> VI;
typedef vector<string> VS;

//inline int rand(int a, int b) { return rand() % (b - a + 1) + a; }

template <class T> inline bool Up(T &a, const T &b) { if(a < b) {a = b; return true;} return false; }
template <class T> inline bool Down(T &a, const T &b) { if(a > b) {a = b; return true;} return false; }

inline int getus() { int tmp, c; while(tmp = fgetc(stdin), tmp < '0' || tmp > '9'); tmp -= '0'; while(c = fgetc(stdin), '0' <= c && c <= '9') tmp = tmp * 10 + c - '0'; return tmp; }
inline int getint() { int tmp, c, flag; while(flag = fgetc(stdin), flag != '-' && (flag < '0' || flag > '9')); if(flag == '-') tmp = 0; else tmp = flag - '0'; while(c = fgetc(stdin), '0' <= c && c <= '9') tmp = tmp * 10 + c - '0'; return flag == '-' ? -tmp : tmp; }

#define EPS 1e-7
#define PI 3.1415926535897932384626

inline int sign(const double &a, const double &eps = EPS) {
	return a < -eps ? -1 : int(a > eps);
}

inline double sqr(double x) {
	return x * x;
}

inline double Sqrt(double x) {
	return x < 0 ? 0 : sqrt(x);
}

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
	point(double x, double y): x(x), y(y) {}
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

bool segIntersect(const point &a, const point &b, const point &c, const point &d, point &e) { // A simpler version
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

struct circle {
	point o;
	double r, r2; // r ^ 2

	circle(): o(), r(0.0), r2(0.0) {
	}

	circle(const point &o, const double &r): o(o), r(r), r2(r * r) {
	}

	bool inside(const point &a) {
		return sign((a - o).norm() - r2) <= 0;
	}

	void set(const point &a, const point &b, const point &c) { // a, b, c not on the same line
		double a1 = 2 * (a.x - b.x), b1 = 2 * (a.y - b.y);
		double a2 = 2 * (a.x - c.x), b2 = 2 * (a.y - c.y);
		double c1 = sqr(a.x) - sqr(b.x) + sqr(a.y) - sqr(b.y);
		double c2 = sqr(a.x) - sqr(c.x) + sqr(a.y) - sqr(c.y);
		o.x = (c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1);
		o.y = (c1 * a2 - c2 * a1) / (a2 * b1 - a1 * b2);
		r = hypot(a.x - o.x, a.y - o.y);
		r2 = sqr(a.x - o.x) + sqr(a.y - o.y);
	}

	bool intersectWithLine(const point &S, const point &T, point &A, point &B) const { // guarantee det(OA, OB) >= 0
		if (sign(det(o - S, T - S)) > 0)
			return intersectWithLine(T, S, A, B);
		double h = dist(S, T, o);
		if (sign(h - r) > 0) return false;
		double l = Sqrt(r2 - sqr(h));
		point mm = (T - S).unit().rot(-PI / 2) * h + o;
		point vv = (T - S).unit() * l;
		A = mm - vv;
		B = mm + vv;
		return true;
	}
	bool contain(const circle &b) const { return sign(b.r + (o - b.o).len() - r) < 0; }
	bool disjunct(const circle &b) const { return sign(b.r + r - (o - b.o).len()) < 0; }
};

bool twoCircleIntersect(const circle &a, const circle &b, point &A, point &B) { // a, b should not be the same
	if (a.contain(b) || b.contain(a) || a.disjunct(b)) return 0;
	double s1 = (a.o - b.o).len();
	double s2 = (a.r2 - b.r2) / s1;
	double aa = (s1 + s2) / 2;
	double bb = (s1 - s2) / 2;
	double h = Sqrt(a.r2 - sqr(aa));
	point mm = (b.o - a.o) * (aa / (aa + bb)) + a.o;
	point vv = (b.o - a.o).unit().rot(PI / 2) * h; // rot(x, y) => (y, -x)
	A = mm + vv;
	B = mm - vv;
	return 1;
}

double twoCircleIntersectArea(const circle &a, const circle &b) {
	if (a.r < b.r) return twoCircleIntersectArea(b, a);
	double ans = 0;
	double d = (a.o - b.o).len();
    if (d + EPS > a.r + b.r) return 0;
    if (d < a.r - b.r + EPS) return PI * b.r2;
    double a1 = arcCos((a.r2 + sqr(d) - b.r2) * 0.5 / a.r / d);
    double a2 = arcCos((b.r2 + sqr(d) - a.r2) * 0.5 / b.r / d);
    ans -= d * a.r * sin(a1);
    ans += a1 * a.r2 + a2 * b.r2;
    return ans;
}

circle minCircle(const point &a, const point &b) {
	return circle((a + b) * 0.5, (b - a).len() * 0.5);
}

circle minCircle(const point &a, const point &b, const point &c) { // WARNING: Obtuse triangle is not considered
	double A = 2 * a.x - 2 * b.x;
	double B = 2 * a.y - 2 * b.y;
	double C = a.x * a.x + a.y * a.y - b.x * b.x - b.y * b.y;
	double D = 2 * a.x - 2 * c.x;
	double E = 2 * a.y - 2 * c.y;
	double F = a.x * a.x + a.y * a.y - c.x * c.x - c.y * c.y;
	point p((C * E - B * F) / (A * E - B * D), (A * F - C * D) / (A * E - B * D));
	return circle(p, (p - a).len());
}

circle minCircle(point P[], int N) {
	if (N == 1) return circle(P[1], 0.0);
	random_shuffle(P + 1, P + N + 1);
	circle O = minCircle(P[1], P[2]);
	Rep(i, 3, N) if(!O.inside(P[i])) {
		O = minCircle(P[1], P[i]);
		Foru(j, 2, i) if(!O.inside(P[j])) {
			O = minCircle(P[i], P[j]);
			Foru(k, 1, j) if(!O.inside(P[k]))
				O = minCircle(P[i], P[j], P[k]);
		}
	}
	return O;
}

struct Polygon { // stored in [0, n)
	int n;
	point list[1033];

	Polygon cut(const point &a, const point &b) {
		static Polygon res;
		static point o;
		res.n = 0;
		for (int i = 0; i < n; ++i) {
			int s1 = sign(det(list[i] - a, b - a));
			int s2 = sign(det(list[(i + 1) % n] - a, b - a));
			if (s1 <= 0) res.list[res.n++] = list[i];
			if (s1 * s2 < 0) {
				lineIntersect(a, b, list[i], list[(i + 1) % n], o);
				res.list[res.n++] = o;
			}
		}
		return res;
	}

	bool contain(const point &p) const { // 1 if on border or inner, 0 if outter
		static point A, B;
		int res = 0;
		for (int i = 0; i < n; ++i) {
			A = list[i];
			B = list[(i + 1) % n];
			if (onSeg(A, B, p)) return 1;
			if (sign(A.y - B.y) <= 0) swap(A, B);
			if (sign(p.y - A.y) > 0) continue;
			if (sign(p.y - B.y) <= 0) continue;
			res += (int)(sign(det(B - p, A - p)) > 0);
		}
		return res & 1;
	}
};

int main() {
	static point p[1033];
	int X, Y, N;
	while (scanf("%d %d %d", &X, &Y, &N) == 3) {
		Rep(i, 1, N) scanf("%lf%lf", &p[i].x, &p[i].y);
		circle ans = minCircle(p, N);
		printf("(%.1f,%.1f).\n%.1f\n", ans.o.x, ans.o.y, ans.r);
	}
	return 0;
}