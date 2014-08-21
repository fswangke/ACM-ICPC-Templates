
// ax + by = g = gcd(x, y)
void exgcd(long long x, long long y, long long &a0, long long &b0, long long &g) { //Warning: possiblly overflow, even if the answer and the inputs are in range
	long long a1 = 0, b1 = 1, t;
	a0 = 1; b0 = 0;
	while (y != 0) {
		t = a0 - x / y * a1; a0 = a1; a1 = t;
		t = b0 - x / y * b1; b0 = b1; b1 = t;
		t = x % y; x = y; y = t;
	}
	if (x < 0) {
		a0 = -a0; b0 = -b0; x = -x;
	}
	g = x;
}
