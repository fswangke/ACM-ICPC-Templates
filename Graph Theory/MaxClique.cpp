namespace MaxClique {
	// 1-based
	// mc[i]: max clique in [i ... n]
	// mc[i] = mc[i + 1] or mc[i + 1] + 1
	int g[MAXN][MAXN], len[MAXN], list[MAXN][MAXN], mc[MAXN], ans;
	bool found;
	void DFS(int size) {
		int i, j, k;
		if (len[size] == 0) {
			if (size > ans) {
				ans = size;
				found = true;
			}
			return;
		}
		for (k = 0; k < len[size] && !found; ++k) {
			if (size + len[size] - k <= ans)
				break;
			i = list[size][k];
			if (size + mc[i] <= ans)
				break;
			for (j = k + 1, len[size + 1] = 0; j < len[size]; ++j)
				if (g[i][list[size][j]])
					list[size + 1][len[size + 1]++] = list[size][j];
			DFS(size + 1);
		}
	}
	int work(int n) {
		int i, j;
		mc[n] = ans = 1;
		for (i = n - 1; i; --i) {
			found = false;
			len[1] = 0;
			for (j = i + 1; j <= n; ++j)
				if (g[i][j])
					list[1][len[1]++] = j;
			DFS(1);
			mc[i] = ans;
		}
		return ans;
	}

}
