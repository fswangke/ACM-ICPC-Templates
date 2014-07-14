
//BEGIN
//POINT CLASS

typedef complex<double> Tpoint;
const double eps = 1e-8;
const double sqrt3 = sqrt(3.0);

istream& operator >>(istream& cin, Tpoint &p) {
	double x, y;
	cin >> x >> y;
	p = Tpoint(x, y);
	return cin;
}

ostream& operator <<(ostream& cout, const Tpoint &p) {
	cout << "(" << p.real() << ", " << p.imag() << ")";
	return cout;
}

int Sign(double x) {
	return fabs(x) < eps ? 0 : x > 0 ? 1 : -1;
}

bool operator ==(const Tpoint &a, const Tpoint &b) {
	return !Sign(a.real() - b.real()) && !Sign(b.imag() - a.imag());
}

bool cmp(const Tpoint &a, const Tpoint &b) {
	return  a.real() < b.real() - eps
		|| (a.real() < b.real() + eps && a.imag() < b.imag());
}

double cross(const Tpoint &a, const Tpoint &b) {
	return (conj(a) * b).imag();
}

double dot(const Tpoint &a, const Tpoint &b) {
	return (conj(a) * b).real();
}

double cross(const Tpoint &a, const Tpoint &b, const Tpoint &c) {
	return cross(b - a, c - a);
}

double dot(const Tpoint &a, const Tpoint &b, const Tpoint &c) {
	return dot(b - a, c - a);
}

Tpoint unit(const Tpoint &a) {
	return a / abs(a);
}

Tpoint intersect(const Tpoint &a, const Tpoint &b, const Tpoint &c, const Tpoint &d) {
	double k1 = cross(a, b, c), k2 = cross(a, b, d);
	if (Sign(k1 - k2))
		return (c * k2 - d * k1) / (k2 - k1);
	return Tpoint(0.0, 0.0);
}

Tpoint rotate(const Tpoint &a, const Tpoint &b, const Tpoint &c) {
	Tpoint d = b - a;
	d = Tpoint(-d.imag(), d.real());
	if (Sign(cross(a, b, c)) == Sign(cross(a, b, a + d)))
		d *= -1.0;
	return unit(d);
}
//END

Tpoint p[10], a[10], b[10];
int N, T;

double totlen(const Tpoint &p, const Tpoint &a, const Tpoint &b, const Tpoint &c) {
	return abs(p - a) + abs(p - b) + abs(p - c);
}
double fermat(const Tpoint &x, const Tpoint &y, const Tpoint &z, Tpoint &cp) {
	a[0] = a[3] = x;
	a[1] = a[4] = y;
	a[2] = a[5] = z;
	double len = 1e100, len2;
	for (int i = 0; i < 3; i++) {
		len2 = totlen(a[i], x, y, z);
		if (len2 < len) {
			len = len2;
			cp = a[i];
		}
	}
	for (int i = 0; i < 3; i++) {
		b[i] = rotate(a[i + 1], a[i], a[i + 2]);
		b[i] = (a[i + 1] + a[i]) / 2.0 + b[i] * (abs(a[i + 1] - a[i]) * sqrt3 / 2.0);
	}
	b[3] = b[0];
	Tpoint cp2 = intersect(b[0], a[2], b[1], a[3]);
	len2 = totlen(cp2, x, y, z);
	if (len2 < len) {
		len = len2;
		cp = cp2;
	}
	return len;
}

double getans(const Tpoint &a) {
	double len = 0;
	for (int i = 0; i < N; i++) len += abs(a - p[i]);
	return len;
}

double mindist(const Tpoint &p, const Tpoint &a, const Tpoint &b, const Tpoint &c, const Tpoint &d) {
	return min( min(abs(p - a), abs(p - b)),
				min(abs(p - c), abs(p - d)));
}

int main() {
	N = 4;
	for (cin >> T; T; T--) {
		for (int i = 0; i < N; i++) cin >> p[i];
		Tpoint cp;
		double ret = 1e100;
		for (int i = 0; i < N; i++)
			ret = min(ret, getans(p[i]));
		for (int i = 1; i < N; i++)
			for (int j = 1; j < N; j++) if (j != i)
				for (int k = 1; k < N; k++)
					if (k != i && k != j) {
						ret = min(ret, abs(p[0] - p[i]) + abs(p[j] - p[k])
							+ min(min(abs(p[0] - p[j]), abs(p[0] - p[k])),
								  min(abs(p[i] - p[j]), abs(p[i] - p[k]))));
						ret = min(ret, getans(intersect(p[0], p[i], p[j], p[k])));
					}
		for (int i = 0; i < N; i++)
			for (int j = i + 1; j < N; j++)
				for (int k = j + 1; k < N; k++) {
					double len = fermat(p[i], p[j], p[k], cp);
					ret = min(ret, len + mindist(p[6 - i - j - k], p[i], p[j], p[k], cp));
				}
		sort(p, p + N, cmp);
		Tpoint cp1, cp2;
		double len_cur, len_before;
		double len1, len2, len;
		for (int i = 1; i < N; i++) {
			cp1 = (p[0] + p[i]) / 2.0;
			int j, k;
			for (j = 1; j < N && j == i; j++);
			k = 6 - i - j;
			len_before = 1e100;
			for ( ; ; ) {
				len1 = fermat(cp1, p[j], p[k], cp2);
				len1 = fermat(cp2, p[0], p[i], cp1);
				len = len1 + abs(cp2 - p[j]) + abs(cp2 - p[k]);
				if (len < len_before - (1e-6)) len_before = len;
				else break;
			}
			ret = min(ret, len_before);
		}
		printf("%.4f\n", ret);
	}
	return 0;
}

