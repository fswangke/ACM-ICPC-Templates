// for a_{i + n} = (\sum_{i = 0}^{n - 1} k_j a_{i + j}) + d
// a_m = (\sum_{i = 0}^{n - 1} c_i a_i) + c_n d
vector<int> recFormula(int n, int k[], int m) {
	vector<int> c(n + 1, 0);
	if (m < n) c[m] = 1;
	else {
		static int a[MAX_K * 2 + 1];
		vector<int> b = recFormula(n, k, m >> 1);

		for (int i = 0; i < n + n; ++i)
			a[i] = 0;
		int s = m & 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				a[i + j + s] += b[i] * b[j];
			c[n] += b[i];
		}
		c[n] = (c[n] + 1) * b[n];
		for (int i = n * 2 - 1; i >= n; i--) {
			int add = a[i];
			if (add == 0) continue;
			for (int j = 0; j < n; j++) {
				a[i - n + j] += k[j] * add;
			}
			c[n] += add;
		}
		for (int i = 0; i < n; ++i)
			c[i] = a[i];
	}
	return c;
}
