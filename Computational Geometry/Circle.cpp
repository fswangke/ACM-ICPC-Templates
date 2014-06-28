
struct circle {
	point o;
	double r2; // r ^ 2

	bool inside(const point &a);
	void set(const point &a, const point &b);
	void set(const point &a, const point &b, const point &c) { // a, b, c not on the same line
		double a1 = 2 * (a.x - b.x), b1 = 2 * (a.y - b.y);
		double a2 = 2 * (a.x - c.x), b2 = 2 * (a.y - c.y);
		double c1 = sqr(a.x) - sqr(b.x) + sqr(a.y) - sqr(b.y);
		double c2 = sqr(a.x) - sqr(c.x) + sqr(a.y) - sqr(c.y);
		o.x = (c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1);
		o.y = (c1 * a2 - c2 * a1) / (a2 * b1 - a1 * b2);
		r2 = sqr(a.x - o.x) + sqr(a.y - o.y);
	}

	bool intersectWithLine(const point &S, const point &T, point &A, point &B) const { // guarantee det(OA, OB) >= 0
		if (sign(det(o - S, T - S)) > 0)
			return intersectWithLine(T, S, A, B);
		double r = Sqrt(r2), h = dist(S, T, o);
		if (sign(h - r) > 0) return false;
		double l = Sqrt(sqr(r) - sqr(h));
		point mm = (T - S).unit().rot(-PI / 2) * h + o;
		point vv = (T - S).unit() * l;
		A = mm - vv;
		B = mm + vv;
		return true;
	}
	bool contain(const circle &a) const { return sign(Sqrt(a.r2) + (o - a.o).len() - Sqrt(r2)) < 0; }
	bool disjunct(const circle &a) const { return sign(Sqrt(a.r2) + Sqrt(r2) - (o - a.o).len()) < 0; }
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
