void exGcd(int a, int b, int &x, int &y) {
	if (b == 0) {
		x = 1;
		y = 0;
	}
	else {
		exGcd(b, a % b, x, y);
		int t = x;
		x = y;
		y = t - a / b * y;
	}
}

// A ^ x = B (mod C)
// -1 if no solution
// O(sqrt(C) * log(C)), log(C) for sort & binary-search

int modLog(int A, int B, int C) {
	static pii baby[MAX_SQRT_C + 11];
	if (B >= C) return -1;
	int d = 0;
	LL k = 1 % C, D = 1 % C;

	for (int i = 0; i < 100; ++i) { // [0, log(C)]
		if (k == B) return i;
		k = k * A % C;
	}

	for (int g; ; ++d) {
		g = gcd(A, C);
		if (g == 1) break;
		if (B % g != 0) return -1;
		C /= g;
		B /= g;
		D = (A / g * D) % C;
	}

	int m = (int) ceil(sqrt((double) C));
	k = 1 % C;
	for (int i = 0; i <= m; ++i) {
		baby[i].second = i;
		baby[i].first = k;
		k = k * A % C;
	}

	sort(baby, baby + m + 1); // [0, m]
	int n = unique(baby, baby + m + 1, equalVal) - baby;
	int am = PowMod(A, m, C);
	for (int i = 0; i <= m; ++i) {
		int e, x, y;
		exGcd(D, C, x, y);
		e = (LL) x * B % C;
		if (e < 0) e += C;
		if (e >= 0) {
			int k = lower_bound(baby, baby + n, pii(e, -1)) - baby;
			if (baby[k].first == e)
				return i * m + baby[k].second + d;
		}
		D = D * am % C;
	}
	return -1;
}
