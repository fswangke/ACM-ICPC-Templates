
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
	if (a <= -1.0)
		return -PI / 2;
	if (a >= 1.0)
		return PI / 2;
	return asin(a);
}

double arcCos(const double &a) {
	if (a <= -1.0)
		return PI;
	if (a >= 1.0)
		return 0;
	return acos(a);
}

struct point {
	double x, y, z;

	point() : x(0.0), y(0.0), z(0.0) {
	}

	point(double x, double y, double z) : x(x), y(y), z(z) {
	}

	point operator + (const point &rhs) const {
		return point(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	point operator - (const point &rhs) const {
		return point(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	point operator * (const double &k) const {
		return point(x * k, y * k, z * k);
	}

	point operator / (const double &k) const {
		return point(x / k, y / k, z / k);
	}

	double len() const {
		return sqrt(x * x + y * y + z * z);
	}

	double norm() const {
		return x * x + y * y + z * z;
	}

	point unit() const {
		double len = sqrt(x * x + y * y + z * z);
		return point(x / len, y / len, z / len);
	}

	friend double dot(const point &a, const point &b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	friend point det(const point &a, const point &b) {
		return point(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x);
	}

	friend double mix(const point &a, const point &b, const point &c) {
		return a.x * b.y * c.z + a.y * b.z * c.x + a.z * b.x * c.y
				- a.z * b.y * c.x - a.x * b.z * c.y - a.y * b.x * c.z;
	}

	double distLP(const point &p1, const point &p2) const {
		return det(p2 - p1, *this - p1).len() / (p2 - p1).len();
	}

	double distFP(const point &p1, const point &p2, const point &p3) const {
		point n = det(p2 - p1, p3 - p1);
		return fabs( dot(n, *this - p1) / n.len() );
	}

};

double distLL(const point &p1, const point &p2, const point &q1, const point &q2) {
	point p = q1 - p1;
	point u = p2 - p1;
	point v = q2 - q1;
	double d = u.norm() * v.norm() - dot(u, v) * dot(u, v);
	if (sign(d) == 0)
		return p1.distLP(q1, q2);
	double s = (dot(p, u) * v.norm() - dot(p, v) * dot(u, v)) / d;
	return (p1 + u * s).distLP(q1, q2);
}

double distSS(const point &p1, const point &p2, const point &q1, const point &q2) {
	point p = q1 - p1;
	point u = p2 - p1;
	point v = q2 - q1;
	double d = u.norm() * v.norm() - dot(u, v) * dot(u, v);
	if (sign(d) == 0) {
		return min(
			min((p1 - q1).len(),
				(p1 - q2).len()
			),
			min((p2 - q1).len(),
				(p2 - q2).len()
			));
	}
	double s1 = (dot(p, u) * v.norm() - dot(p, v) * dot(u, v)) / d;
	double s2 = (dot(p, v) * u.norm() - dot(p, u) * dot(u, v)) / d;
	if (s1 < 0.0) s1 = 0.0;
	if (s1 > 1.0) s1 = 1.0;
	if (s2 < 0.0) s2 = 0.0;
	if (s2 > 1.0) s2 = 1.0;
	point r1 = p1 + u * s1;
	point r2 = q1 + v * s2;
	return (r1 - r2).len();
}

bool isFL(const point &p, const point &o, const point &q1, const point &q2, point &res) {
	double a = dot(o, q2 - p);
	double b = dot(o, q1 - p);
	double d = a - b;
	if (sign(d) == 0)
		return false;
	res = (q1 * a - q2 * b) / d;
	return true;
}

bool isFF(const point &p1, const point &o1, const point &p2, const point &o2, point &a, point &b) {
	point e = det(o1, o2);
	point v = det(o1, e);
	double d = dot(o2, v);
	if (sign(d) == 0)
		return false;
	point q = p1 + v * (dot(o2, p2 - p1) / d);
	a = q;
	b = q + e;
	return true;
}
