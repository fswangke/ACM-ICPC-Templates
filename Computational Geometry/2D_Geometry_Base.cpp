
const double EPS = 1e-7;
const double PI = 3.1415926535897932384626;
const int INF = 1000000000;

int sign(const double &a, const double &eps = EPS) {
	return a < -eps ? -1 : int(a > eps);
}

double sqr(const double &x) {
	return x * x;
}

double Sqrt(const double &x) {
	return x < 0 ? 0 : sqrt(x);
}

double arcSin(const double &a) {
	if (a <= -1.0) return -PI / 2;
	if (a >=  1.0) return  PI / 2;
	return asin(a);
}

double arcCos(const double &a) {
	if (a <= -1.0) return PI;
	if (a >=  1.0) return 0;
	return acos(a);
}

struct point {
	double x, y;

	point() : x(0.0), y(0.0) {
	}

	point(const double &x, const double &y) : x(x), y(y) {
	}

	point operator +(const point &rhs) const {
		return point(x + rhs.x, y + rhs.y);
	}

	point operator -(const point &rhs) const {
		return point(x - rhs.x, y - rhs.y);
	}

	point operator *(const double &k) const {
		return point(x * k, y * k);
	}

	point operator /(const double &k) const {
		return point(x / k, y / k);
	}

	double len() const {
		return hypot(x, y);
	}

	double norm() const {
		return x * x + y * y;
	}

	point unit() const {
		double k = len();
		return point(x / k, y / k);
	}

	point rot(const double &a) const { // counter-clockwise
		return point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
	}

	point rot90() const { // counter-clockwise
		return point(-y, x);
	}

	point rot180() const { // counter-clockwise
		return point(-x, -y);
	}

	point rot270() const { // counter-clockwise
		return point(y, -x);
	}

	point project(const point &p1, const point &p2) const {
		const point &q = *this;
		return p1 + (p2 - p1) * (dot(p2 - p1, q - p1) / (p2 - p1).norm());
	}

	friend double dot(const point &a, const point &b) {
		return a.x * b.x + a.y * b.y;
	}

	friend double det(const point &a, const point &b) {
		return a.x * b.y - a.y * b.x;
	}

	bool onSeg(const point &a, const point &b) const { // [a, b] inclusive
		const point &c = *this;
		return sign(dot(a - c, b - c)) <= 0 && sign(det(b - a, c - a)) == 0;
	}

	double distLP(const point &p1, const point &p2) const { // dist from *this to line p1->p2
		const point &q = *this;
		return fabs(det(p2 - p1, q - p1)) / (p2 - p1).len();
	}

	double distSP(const point &p1, const point &p2) const { // dist from *this to segment [p1, p2]
		const point &q = *this;
		if (dot(p2 - p1, q - p1) < EPS) return (q - p1).len();
		if (dot(p1 - p2, q - p2) < EPS) return (q - p2).len();
		return distLP(p1, p2);
	}

};

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
	return e.onSeg(a, b) && e.onSeg(c, d);
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
	if (d1 == 0 && c.onSeg(a, b)) o = c, ++iCnt;
	if (d2 == 0 && d.onSeg(a, b)) o = d, ++iCnt;
	if (d3 == 0 && a.onSeg(c, d)) o = a, ++iCnt;
	if (d4 == 0 && b.onSeg(c, d)) o = b, ++iCnt;
	return iCnt ? 2 : 0;
}

struct circle {
	point o;
	double r, rSqure; // r ^ 2

	circle() :
			o(), r(0.0), rSqure(0.0) {
	}

	circle(const point &o, const double &r) :
			o(o), r(r), rSqure(r * r) {
	}

	bool inside(const point &a) { // not strict
		return (a - o).len() < r + EPS;
	}

	bool contain(const circle &b) const { // not strict
		return sign(b.r + (o - b.o).len() - r) <= 0;
	}

	bool disjunct(const circle &b) const { // not strict
		return sign(b.r + r - (o - b.o).len()) <= 0;
	}

	int isCL(const point &p1, const point &p2, point &a, point &b) const {
		double x = dot(p1 - o, p2 - p1);
		double y = (p2 - p1).norm();
		double d = x * x - y * ((p1 - o).norm() - rSqure);
		if (d < -EPS)
			return 0;
		if (d < 0)
			d = 0;
		point q1 = p1 - (p2 - p1) * (x / y);
		point q2 = (p2 - p1) * (sqrt(d) / y);
		a = q1 - q2;
		b = q1 + q2;
		return q2.len() < EPS ? 1 : 2;
	}

	int tanCP(const point &p, point &a, point &b) const { //Warning: Only Calculate Tangent point
		double x = (p - o).norm();
		double d = x - rSqure;
		if (d < -EPS) return 0;
		if (d < 0) d = 0;
		point q1 = (p - o) * (rSqure / x);
		point q2 = ((p - o) * (-r * sqrt(d) / x)).rot90();
		a = o + (q1 - q2);
		b = o + (q1 + q2);
		return q2.len() < EPS ? 1 : 2;
	}
};

bool checkCrossCS(const circle &cir, const point &p1, const point &p2) { // not strict
	const point &c = cir.o;
	const double &r = cir.r;
	return c.distSP(p1, p2) < r + EPS
			&& (r < (c - p1).len() + EPS || r < (c - p2).len() + EPS);
}

bool checkCrossCC(const circle &cir1, const circle &cir2) { // not strict
	const double &r1 = cir1.r;
	const double &r2 = cir2.r;
	double d = (cir1.o - cir2.o).len();
	return d < r1 + r2 + EPS && fabs(r1 - r2) < d + EPS;
}

int isCC(const circle &cir1, const circle &cir2, point &a, point &b) {
	const point &c1 = cir1.o, &c2 = cir2.o;
	double x = (c1 - c2).norm();
	double y = ((cir1.rSqure - cir2.rSqure) / x + 1) / 2;
	double d = cir1.rSqure / x - y * y;
	if (d < -EPS) return 0;
	if (d < 0) d = 0;
	point q1 = c1 + (c2 - c1) * y;
	point q2 = ((c2 - c1) * sqrt(d)).rot90();
	a = q1 - q2;
	b = q1 + q2;
	return q2.len() < EPS ? 1 : 2;
}

vector<pair<point, point> > tanCC(const circle &cir1, const circle &cir2) { 
//Warning, if there is only 3 tangent line(in other word s1 == 1 && s2 == 1 is true), the program won't calulate correctly, but the tangent point is right
	vector<pair<point, point> > list; list.clear();
	if(cir1.contain(cir2) || cir2.contain(cir1))
		return list;
	const point &c1 = cir1.o, &c2 = cir2.o;
	double r1 = cir1.r, r2 = cir2.r;
	point p, a1, b1, a2, b2; int s1, s2;
	if (sign(r1 - r2) == 0) {
		p = c2 - c1;
		p = (p * (r1 / p.len())).rot90();
		list.push_back(make_pair(c1 + p, c2 + p));
		list.push_back(make_pair(c1 - p, c2 - p));
	} else {
		p = (c2 * r1 - c1 * r2) / (r1 - r2);
		s1 = cir1.tanCP(p, a1, b1);
		s2 = cir2.tanCP(p, a2, b2);
		if (s1 >= 1 && s2 >= 1) {
			list.push_back(make_pair(a1, a2));
			list.push_back(make_pair(b1, b2));
		}
	}
	p = (c1 * r2 + c2 * r1) / (r1 + r2);
	s1 = cir1.tanCP(p, a1, b1);
	s2 = cir2.tanCP(p, a2, b2);
	if (s1 >= 1 && s2 >= 1) {
		list.push_back(make_pair(a1, a2));
		list.push_back(make_pair(b1, b2));
	}
	return list;
}

double areaCT(const circle &cir, point pa, point pb) {
	pa = pa - cir.o;
	pb = pb - cir.o;
	double R = cir.r;
	if (pa.len() < pb.len()) swap(pa, pb);
	if (pb.len() < EPS) return 0;
	point pc = pb - pa;
	double a = pa.len(), b = pb.len(), c = pc.len();
	double cosB = dot(pb, pc) / b / c, B = acos(cosB);
	double cosC = dot(pa, pb) / a / b, C = acos(cosC);
	double S, h, theta;
	if (b > R) {
		S = C * 0.5 * R * R;
		h = b * a * sin(C) / c;
		if (h < R && B < PI * 0.5)
			S -= acos(h / R) * R * R - h * sqrt(R * R - h * h);
	} else if (a > R) {
		theta = PI - B - asin(sin(B) / R * b);
		S = 0.5 * b * R * sin(theta) + (C - theta) * 0.5 * R * R;
	} else {
		S = 0.5 * sin(C) * b * a;
	}
	return S;
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
	Rep(i, 1, N) if(!O.inside(P[i])) {
		O = minCircle(P[1], P[i]);
		Foru(j, 1, i) if(!O.inside(P[j])) {
			O = minCircle(P[i], P[j]);
			Foru(k, 1, j) if(!O.inside(P[k]))
				O = minCircle(P[i], P[j], P[k]);
		}
	}
	return O;
}
