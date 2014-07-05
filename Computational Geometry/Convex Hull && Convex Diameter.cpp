
inline bool turnLeft(const point &a, const point &b, const point &c) {
	return sign(det(b - a, c - a)) >= 0;
}

inline bool turnRight(const point &a, const point &b, const point &c) {
	return sign(det(b - a, c - a)) <= 0;
}

inline bool cmpByXY(const point &a, const point &b) {
	int c = sign(a.x - b.x);
	if (c != 0) return c < 0;
	return sign(a.y - b.y) < 0;
}

vector<point> convexHull(vector<point> &a) {
	int n = (int)a.size(), cnt = 0;
	sort(a.begin(), a.end(), cmpByXY);
	vector<point> ret;
	ret.reserve(n * 2);
	for (int i = 0; i < n; ++i) {
		while (cnt > 1 && turnLeft(ret[cnt - 2], a[i], ret[cnt - 1])) {
			--cnt;
			ret.pop_back();
		}
		ret.push_back(a[i]);
		++cnt;
	}
	int fixed = cnt;
	for (int i = n - 2; i >= 0; --i) { // n - 1 must be in stack
		while (cnt > fixed && turnLeft(ret[cnt - 2], a[i], ret[cnt - 1])) {
			--cnt;
			ret.pop_back();
		}
		ret.push_back(a[i]);
		++cnt;
	}
	// the lowest point will occur twice, i.e. ret.front() == ret.back()
	return ret;
}

double convexDiameter(const vector<point> &ps) {
	int n = ps.size();
	if (n < 2) return 0;
	if (n == 2) return (ps[1] - ps[0]).len();
	int nx, ny, y = 1;
	double k;
	double ans = 0;
	for (int x = 0; x < n; ++x) {
		nx = x + 1;
		for ( ; ; y = ny) {
			ny = y == n - 1 ? 0 : y + 1;
			k = det(ps[nx] - ps[x], ps[ny] - ps[y]);
			if (k <= 0) break;
		}
		Up(ans, (ps[x] - ps[y]).len());
		if (sign(k) == 0)
			Up(ans, (ps[x] - ps[ny]).len());
	}
	return ans;
}
