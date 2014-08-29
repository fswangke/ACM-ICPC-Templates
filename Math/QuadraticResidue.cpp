// solve equation x ^ 2 == a (mod p), where p is a prime number
bool QuadraticResidue(int a, int p, int &x, int &y) {
	a = (a % p + p) % p;
	if (p == 2) {
		if (a == 0)
			x = y = 0;
		else
			x = y = 1;
		return true;
	}
	if (powMod(a, p / 2, p) == p - 1)
		return false;
	if ((p + 1) % 4 == 0) {
		x = powMod(a, (p + 1) / 4, p);
		y = x == 0 ? 0 : p - x;
		if (x > y) swap(x, y);
		return true;
	}
	else {
		int t, h, pb = 0;
		h = p - 1;
		for (t = 0; (h & 1) == 0; h >>= 1, ++t);
		if (t >= 2) {
			int b;
			do {
				b = random() % (p - 2) + 2; // pay attention to the range of rand()
			} while (powMod(b, p / 2, p) != p - 1);
			pb = powMod(b, h, p);
		}
		int s = powMod(a, h / 2, p);
		for (int step = 2; step <= t; step++) {
			int ss = (LL)s * s % p * a % p;
			for (int i = 0; i < t - step; i++)
				ss = (LL)ss * ss % p;
			if (ss + 1 == p)
				s = (LL)s * pb % p;
			pb = (LL)pb * pb % p;
		}
		x = (LL)s * a % p;
		y = x == 0 ? 0 : p - x;
		if (x > y) swap(x, y);
	}
	return true;
}
