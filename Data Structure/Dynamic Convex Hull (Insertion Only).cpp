
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <map>

#define x first
#define y second

using namespace std;

typedef long long LL;
typedef map<int, int> mii;
typedef map<int, int>::iterator mit;

inline int sign(LL x) {
	return x < 0 ? -1 : int(x > 0);
}

struct point {
	int x, y;

	point(): x(0), y(0) {
	}

	point(const int &x, const int &y) : x(x), y(y) {
	}

	point(const mit &p): x(p->first), y(p->second) {
	}

	friend inline point operator - (const point &a, const point &b) {
		return point(a.x - b.x, a.y - b.y);
	}

	friend inline LL det(const point &a, const point &b) {
		return (LL)a.x * b.y - (LL)a.y * b.x;
	}
};

inline bool checkInside(mii &a, const point &p) { // border inclusive
	int x = p.x, y = p.y;
	mit p1 = a.lower_bound(x);
	if (p1 == a.end()) return false;
	if (p1->x == x)	return y <= p1->y;
	if (p1 == a.begin()) return false;
	mit p2(p1--);
	return sign(det(p - point(p1), point(p2) - p)) >= 0;
}

inline void addPoint(mii &a, const point &p) { // no collinear points
	int x = p.x, y = p.y;
//	assert(!checkInside(a, p));

	mit pnt = a.insert(make_pair(x, y)).first, p1, p2;
	pnt->y = y;

	for ( ; ; a.erase(p2)){
		p1 = pnt;
		if (++p1 == a.end()) break;
		p2 = p1;
		if (++p1 == a.end()) break;
		if (det(point(p2) - p, point(p1) - p) < 0) break;
	}
	for ( ; ; a.erase(p2)){
		p1 = pnt;
		if (p1 == a.begin()) break;
		--p1;
		if (p1 == a.begin()) break;
		p2 = p1--;
		if (det(point(p2) - p, point(p1) - p) > 0) break;
	}
}

int main() {
	int N, t, x, y;
	mii upperHull, lowerHull;

	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%d %d %d", &t, &x, &y);
		if (t == 1) {
			if (!checkInside(upperHull, point(x,  y))) addPoint(upperHull, point(x,  y));
			if (!checkInside(lowerHull, point(x, -y))) addPoint(lowerHull, point(x, -y));
		}
		else {
			if (checkInside(upperHull, point(x, y)) && checkInside(lowerHull, point(x, -y)))
				puts("YES");
			else
				puts("NO");
		}
	}
	return 0;
}
