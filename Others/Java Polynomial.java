class Polynomial {
	public final static Polynomial ZERO = new Polynomial(new int[] { 0 });
	public final static Polynomial ONE = new Polynomial(new int[] { 1 });
	public final static Polynomial X = new Polynomial(new int[] { 0, 1 });

	int[] coef;

	static Polynomial valueOf(int val) {
		return new Polynomial(new int[] { val });
	}

	Polynomial(int[] coef) {
		this.coef = Arrays.copyOf(coef, coef.length);
	}

	Polynomial add(Polynomial o, int mod) {
		int n = coef.length, m = o.coef.length;
		int[] ret = new int[Math.max(n, m)];
		// Arrays.fill(ret, 0);
		for (int i = 0; i < n; ++i)
			ret[i] = coef[i] % mod;
		for (int i = 0; i < m; ++i)
			ret[i] = (ret[i] + o.coef[i]) % mod;
		return new Polynomial(ret);
	}

	Polynomial subtract(Polynomial o, int mod) {
		int n = coef.length, m = o.coef.length;
		int[] ret = new int[Math.max(n, m)];
		for (int i = 0; i < n; ++i)
			ret[i] = coef[i];
		for (int i = 0; i < m; ++i)
			ret[i] = (ret[i] + mod - o.coef[i]) % mod;
		return new Polynomial(ret);
	}

	Polynomial multiply(Polynomial o, int mod) {
		int n = coef.length, m = o.coef.length;
		int[] ret = new int[n + m - 1];
		// Arrays.fill(ret, 0);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				ret[i + j] = (int) ((ret[i + j] + (long) coef[i] * o.coef[j]) % mod);
		return new Polynomial(ret);
	}

	Polynomial scale(int o, int mod) {
		int n = coef.length;
		int[] ret = new int[n];
		for (int i = 0; i < n; ++i)
			ret[i] = (int) ((long) coef[i] * o % mod);
		return new Polynomial(ret);
	}

	public String toString() {
		int n = coef.length;
		String ret = "";
		for (int i = n - 1; i > 0; --i)
			if (coef[i] != 0)
				ret += coef[i] + "x^" + i + "+";
		return ret + coef[0];
	}

	static int pow(int x, int y, int mod) {
		if (y == 0) return 1;
		int ret = pow(x, y / 2, mod);
		ret = (int) ((long) ret * ret % mod);
		if ((y & 1) == 1)
			ret = (int) ((long) ret * x % mod);
		return ret;
	}

	static Polynomial lagrangeInterpolation(int[] x, int[] y, int mod) {
		int n = x.length;
		Polynomial ret = Polynomial.ZERO;
		for (int i = 0; i < n; ++i) {
			Polynomial poly = Polynomial.valueOf(y[i]);
			for (int j = 0; j < n; ++j)
				if (i != j) {
					poly = poly.multiply(Polynomial.X.subtract(
							Polynomial.valueOf(x[j]), mod), mod);
					int inv = pow(x[i] - x[j] + mod, mod - 2, mod);
					poly = poly.scale(inv, mod);
				}
			ret = ret.add(poly, mod);
		}
		return ret;
	}
}
