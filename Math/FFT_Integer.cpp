
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MOD = 3 << 18 | 1;
const int PRIMITIVE_ROOT = 10;
const int MAXB = 1 << 20;

namespace PrimitiveRoot {

	int powMod(int a, int d, int p) {
		int res = 1;
		a %= p;
		for ( ; d; d >>= 1) {
			if (d & 1)
				res = (long long)res * a % p;
			a = (long long)a * a % p;
		}
		return res;
	}

	bool isPrime(int n) {
		for (int i = 2; i * i <= n; ++i)
			if (n % i == 0)
				return false;
		return true;
	}

	int getMod(int downLimit) { // 3 * 2 ^ 21 + 1 is a suitable alternate
		for (int c = 3; ; ++c) {
			int t = (c << 21) | 1;
			if (isPrime(t) && t >= downLimit)
				return t;
		}
		return -1;
	}

	bool isPrimitiveRoot(int a, int mod) {
		int phi = mod - 1;
		for (int i = 1; i * i <= phi; ++i) {
			int j = phi / i;
			if (i * j != phi) continue;
			if (i < phi && powMod(a, i, mod) == 1)
				return false;
			if (j < phi && powMod(a, j, mod) == 1)
				return false;
		}
		return true;
	}

	int getPrimitiveRoot(int p) {
		int g = 2;
		while ( !isPrimitiveRoot(g, p) ) ++g;
		return g;
	}
}

namespace FFT {

	int modinv(int a) {
		return a <= 1 ? a : (long long) (MOD - MOD / a) * modinv(MOD % a) % MOD;
	}

	long long powmod(long long a, int b) {
		a %= MOD;
		long long r = 1;
		while (b) {
			if (b & 1) {
				r = r * a % MOD;
			}
			if (b >>= 1) {
				a = a * a % MOD;
			}
		}
		return r;
	}

	void NTT(int P[], int n, int oper) {
		for (int i = 1, j = 0; i < n - 1; i++) {
			for (int s = n; j ^= s >>= 1, ~j & s;);
			if (i < j) {
				swap(P[i], P[j]);
			}
		}
		for (int d = 0; (1 << d) < n; d++) {
			int m = 1 << d, m2 = m * 2;
			long long unit_p0 = powmod(PRIMITIVE_ROOT, (MOD - 1) / m2);
			if (oper < 0) {
				unit_p0 = modinv(unit_p0);
			}
			for (int i = 0; i < n; i += m2) {
				long long unit = 1;
				for (int j = 0; j < m; j++) {
					int &P1 = P[i + j + m], &P2 = P[i + j];
					int t = unit * P1 % MOD;
					P1 = (P2 - t + MOD) % MOD;
					P2 = (P2 + t) % MOD;
					unit = unit * unit_p0 % MOD;
				}
			}
		}
	}

	vector<int> mul(const vector<int> &a, const vector<int> &b) {
		vector<int> ret(max(0, (int) a.size() + (int) b.size() - 1), 0);
		static int A[MAXB], B[MAXB], C[MAXB];
		int len = 1;
		while (len < ret.size()) {
			len *= 2;
		}
		for (int i = 0; i < len; i++) {
			A[i] = i < a.size() ? a[i] : 0;
			B[i] = i < b.size() ? b[i] : 0;
		}
		NTT(A, len, 1);
		NTT(B, len, 1);
		for (int i = 0; i < len; i++) {
			C[i] = (long long) A[i] * B[i] % MOD;
		}
		NTT(C, len, -1);
		int inv = modinv(len);
		for (int i = 0; i < ret.size(); i++) {
			ret[i] = (long long) C[i] * inv % MOD;
		}
		return ret;
	}

}

