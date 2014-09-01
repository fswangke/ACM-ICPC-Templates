struct Polygon { // stored in [0, n)
	int n; point list[MAXN];
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
			if (p.onSeg(A, B)) return 1;
			if (sign(A.y - B.y) <= 0) swap(A, B);
			if (sign(p.y - A.y) > 0) continue;
			if (sign(p.y - B.y) <= 0) continue;
			res += (int)(sign(det(B - p, A - p)) > 0);
		}
		return res & 1;
	}
	bool convexContain(const point &p) const { // sort by polar angle
		for (int i = 1; i < n; ++i) list[i] = list[i] - list[0];
		point q = p - list[0];
		if (sign(det(list[1], q)) < 0 || sign(det(list[n - 1], q)) > 0) return false;
		int l = 2, r = n - 1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			double d1 = sign(det(list[mid], q));
			double d2 = sign(det(list[mid - 1], q));
			if (d1 <= 0) {
				if (d2 <= 0) {
					if (sign(det(q - list[mid - 1], list[mid] - list[mid - 1]) <= 0) <= 0)
						return true;
				} else 
					r = mid - 1;
			} else l = mid + 1;
		}
		return false;
	}
	double isPLAtan2(const point &a, const point &b) {
		double k = (b - a).alpha();
		if (k < 0) k += 2 * PI;
		return k;
	}
	point isPL_Get(const point &a, const point &b, const point &s1, const point &s2) {
		double k1 = det(b - a, s1 - a);
		double k2 = det(b - a, s2 - a);
		if (sign(k1) == 0) return s1;
		if (sign(k2) == 0) return s2;
		return (s1 * k2 - s2 * k1) / (k2 - k1);
	}
	int isPL_Dic(const point &a, const point &b, int l, int r) {
		int s = (det(b - a, list[l] - a) < 0) ? -1 : 1;
		while (l <= r) {
			int mid = (l + r) / 2;
			if (det(b - a, list[mid] - a) * s <= 0) r = mid - 1;
			else l = mid + 1;
		}
		return r + 1;
	}
	int isPL_Find(double k, double w[]) {
		if (k <= w[0] || k > w[n - 1]) return 0;
		int l = 0, r = n - 1, mid;
		while (l <= r) {
			mid = (l + r) / 2;
			if (w[mid] >= k) r = mid - 1;
			else l = mid + 1;
		}
		return r + 1;
	}
	bool isPL(const point &a, const point &b, point &cp1, point &cp2) {  // O (log N)
		static double w[MAXN * 2];
		// pay attention to the array size
		for (int i = 0; i <= n; ++i) list[i + n] = list[i];
		for (int i = 0; i < n; ++i) w[i] = w[i + n] = isPLAtan2(list[i], list[i + 1]);
		int i = isPL_Find(isPLAtan2(a, b), w);
		int j = isPL_Find(isPLAtan2(b, a), w);
		double k1 = det(b - a, list[i] - a);
		double k2 = det(b - a, list[j] - a);
		if (sign(k1) * sign(k2) > 0) return false; // no intersection
		if (sign(k1) == 0 || sign(k2) == 0) { // intersect with a point or a line in the convex
			if (sign(k1) == 0) {
				if (sign(det(b - a, list[i + 1] - a)) == 0) {
					cp1 = list[i];
					cp2 = list[i + 1];
				} else
					cp1 = cp2 = list[i];
				return true;
			}
			if (sign(k2) == 0) {
				if (sign(det(b - a, list[j + 1] - a)) == 0) {
					cp1 = list[j];
					cp2 = list[j + 1];
				} else
					cp1 = cp2 = list[j];
			}
			return true;
		}
		if (i > j) swap(i, j);
		int x = isPL_Dic(a, b, i, j);
		int y = isPL_Dic(a, b, j, i + n);
		cp1 = isPL_Get(a, b, list[x - 1], list[x]);
		cp2 = isPL_Get(a, b, list[y - 1], list[y]);
		return true;
	}
};