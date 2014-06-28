int N;
double R; // 以原点为圆心
point info[maxn];

double area2(point pa, point pb) { // 用有向面积，划分成一个三角形和圆的面积的交
	if (pa.len() < pb.len()) swap(pa, pb);
	if (pb.len() < eps) return 0;
	point pc = pb - pa;
	double a = pb.len(), b = pa.len(), c = pc.len();
	double cosB = dot(pb, pc) / a / c, B = acos(cosB);
	double cosC = dot(pa, pb) / a / b, C = acos(cosC);
	double S, h, theta;
	if (a > R) {
		S = C * 0.5 * R * R;
		h = a * b * sin(C) / c;
		if (h < R && B < PI * 0.5)
			S -= acos(h / R) * R * R - h * sqrt(R * R - h * h);
	} else if (b > R) {
		theta = PI - B - asin(sin(B) / R * a);
		S = 0.5 * a * R * sin(theta) + (C - theta) * 0.5 * R * R;
	} else {
		S = 0.5 * sin(C) * a * b;
	}
	return S;
}

double area() { // 点保存在info[0, N)里面
	double S = 0;
	info[N] = info[0];
	for (int i = 0; i < N; ++i) S += area2(info[i], info[i + 1]) * sign(det(info[i], info[i + 1]));
	return fabs(S);
}
