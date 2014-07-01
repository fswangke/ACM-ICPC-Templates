/**
 * Time Complexity: O(N ^ 3)
 */

 inline bool toUpLeft(const point &a, const point &b) {
	int c = sign(b.y - a.y);
	if (c > 0) return true;
	return c == 0 && sign(b.x - a.x) > 0;
}

inline bool cmpByPolarAngle(const point &a, const point &b) { // counter-clockwise, shorter first if they share the same polar angle
	int c = sign(det(a, b));
	if (c != 0) return c > 0;
    return sign(b.len() - a.len()) > 0;
}

double maxEmptyConvexHull(point p[], int N) {
	static double dp[MAX_NODE][MAX_NODE];
	static point vec[MAX_NODE];
	static int seq[MAX_NODE]; // empty triangles formed with (0, 0), vec[o], vec[ seq[i] ]

	double ans = 0.0;
	Rep(o, 1, N) {
		int totVec = 0;
		Rep(i, 1, N) if (toUpLeft(p[o], p[i])) 
			vec[++totVec] = p[o] - p[i];
		sort(vec + 1, vec + totVec + 1, cmpByPolarAngle);
		Rep(i, 1, totVec) Rep(j, 1, totVec) dp[i][j] = 0.0;

		Rep(k, 2, totVec) {
			int i = k - 1;
			while (i > 0 && sign( det(vec[k], vec[i]) ) == 0) --i;

			int totSeq = 0;
			for (int j; i > 0; i = j) {
				seq[++totSeq] = i;
				for (j = i - 1; j > 0 && sign(det(vec[i] - vec[k], vec[j] - vec[k])) > 0; --j);

				double v = det(vec[i], vec[k]) * 0.5;
				if (j > 0) v += dp[i][j];
				dp[k][i] = v;
				Up(ans, v);
			}
			for (int i = totSeq - 1; i >= 1; --i)
				Up( dp[k][ seq[i] ], dp[k][seq[i + 1]] );
		}
	}
	return ans;
}
