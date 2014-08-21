
#define MAXN 1033
struct Polygon { // stored in [0, n)
	int n;
	point list[MAXN];

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
	
	bool convex_contain(const point &p) const { // sort by polar angle
		for (int i = 1; i < n; ++ i) list[i] = list[i] - list[0];
		static point q = p - list[0];
		
		if (sign(det(list[1], q)) < 0 || sign(det(list[n - 1], q)) > 0)
			return false;
		int l = 2, r = n - 1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			double d1 = sign(det(list[mid], q));
			double d2 = sign(det(list[mid - 1], q));
			if (d1 <= 0) {
				if (d2 <= 0) {
					if (sign(det(q - list[mid - 1], list[mid] - list[mid - 1]) <= 0) <= 0)
						return true;
					break;
				} else 
					r = mid - 1;
			} else l = mid + 1;
		}
		return false;
	}
};

