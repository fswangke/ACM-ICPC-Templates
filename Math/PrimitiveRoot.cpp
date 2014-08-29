vector<int> findPrimitiveRoot(int N) {
	if (N <= 4) return vector<int>(1, max(1, N - 1));

	int phi = N;
	{ // check no solution && calculate phi
		int M = N;
		if (~M & 1) M >>= 1, phi >>= 1;
		if (~M & 1) return vector<int>(0);
		int k = 0;
		for (int d = 3; d * d <= M; ++d) if (M % d == 0) {
			for (; M % d == 0; M /= d);
			++k;
			if (k > 1) return vector<int>(0);
			phi -= phi / d;
		}
		if (M > 1) {
			++k;
			phi -= phi / M;
		}
		if (k > 1) return vector<int>(0);
	}

	vector<int> ans;
	for (int g = 2; g <= N; ++g) if (Gcd(g, N) == 1) {
		bool good = true;
		for (int i = 1, p = 1; i < phi; ++i) {
			p = (LL)p * g % N;
			if (p == 1) {
				good = false;
				break;
			}
		}
		if (good) {
			for (int i = 1, gp = 1; i <= phi; ++i) {
				gp = (LL)gp * g % N;
				if (Gcd(i, phi) == 1)
					ans.push_back(gp);
			}
			break;
		}
	}
	sort(ans.begin(), ans.end());
	return ans;
}
