// PKU 1686 Lazy Math Instructor

#include <cstdio>
#include <cstring>
#include <cctype>
#include <ctime>
#include <cstdlib>

const int maxl = 1000;
const int maxt = 100;
const double eps = 1e-8;

int value[26];
char str1[maxl], str2[maxl];

void getStr(char str[]) {
	gets(str);
	int i, len = 0;
	for (i = 0; str[i]; i++)
		if (str[i] > ' ')
			str[len++] = str[i];
	str[len] = 0;
}

inline int getLevel(char ch) {
	switch (ch) {
	case '+':
	case '-':
		return 0;
	case '*':
		return 1;
	}
	return -1;
}

int evaluate(const char *&p, int level) {
	int res;
	if (level == 2) {
		if (*p == '(') {
			++p; res = evaluate(p, 0);
		} else {
			res = isdigit(*p) ? *p - '0' : value[*p - 'a'];
		}
		++p;
		return res;
	}
	res = evaluate(p, level + 1);
	char op;
	int next;
	while (*p && getLevel(*p) == level) {
		op = *p++;
		next = evaluate(p, level + 1);
		switch (op) {
		case '+':
			res += next;
			break;
		case '-':
			res -= next;
			break;
		case '*':
			res *= next;
			break;
		}
	}
	return res;
}

int makeEvaluation(const char *str) {
	const char *p = str;
	return evaluate(p, 0);
}

void solve() {
	getStr(str1);
	getStr(str2);
	for (int i = 0; i < maxt; i++) {
		for (int j = 0; j < 26; j++)
			value[j] = rand();
		if (makeEvaluation(str1) != makeEvaluation(str2)) {
			puts("NO");
			return;
		}
	}
	puts("YES");
}

int main() {
	int T;
	scanf("%d", &T);
	gets(str1);
	while (T--) solve();
	return 0;
}
