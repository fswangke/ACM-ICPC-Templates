LL Mul(LL a, LL b, LL P) {
	LL t = a * b - LL(((long double)a / P * b) + 1e-3) * P;
	t = t % P;
	if (t < 0) t += P;
	return t;
}