
const int MAXLEN = 100033;
const int MAXNODE = MAXLEN * 2 + 1;

struct node {
	int len, opt, ans;
	node *fa, *go[26];
} base[MAXNODE], *top = base, *root;
typedef node *tree;

int N, Ncnt;
char A[MAXLEN];
tree Q[MAXNODE];

inline tree newNode(int len) {
	top->len = top->ans = len;
	top->fa = NULL;
	top->opt = 0;
	memset(top->go, 0, sizeof(top->go));
	return top++;
}

inline tree newNode(int len, tree fa, tree *go) {
	top->len = top->ans = len;
	top->fa = fa;
	top->opt = 0;
	memcpy(top->go, go, sizeof(top->go));
	return top++;
}

void construct() {
	tree p, q, up, fa;
	N = strlen(A);
	p = root = newNode(0);
	for (int i = 0; i < N; ++i) {
		int w = A[i] - 'a';
		up = p; p = newNode(i + 1);
		for ( ; up && !up->go[w]; up = up->fa)
			up->go[w] = p;
		if (!up) p->fa = root;
		else {
			q = up->go[w];
			if (up->len + 1 == q->len) p->fa = q;
			else {
				fa = newNode(up->len + 1, q->fa, q->go);
				p->fa = q->fa = fa;
				for ( ; up && up->go[w] == q; up = up->fa)
					up->go[w] = fa;
			}
		}
	}
	static int cnt[MAXLEN];
	memset(cnt, 0, sizeof(cnt));
	Ncnt = top - base;
	for (tree i(base); i != top; ++i) ++cnt[i->len];
	Rep(i, 1, N) cnt[i] += cnt[i - 1];
	for (tree i(base); i != top; ++i) Q[ cnt[i->len]-- ] = i;
}

void work() {
	scanf("%s", A);
	construct();
	while (scanf("%s", A) != EOF) {
		int len = 0;
		tree t = root;
		for (int i(0), Len(strlen(A)); i < Len; ++i) {
			int w = A[i] - 'a';
			if (t->go[w]) {
				++len;
				t = t->go[w];
			} else {
				for ( ; t && !t->go[w]; t = t->fa);
				if (t) {
					len = t->len + 1;
					t = t->go[w];
				} else {
					len = 0;
					t = root;
				}
			}
			Up(t->opt, len);
		}
		Til(i, Ncnt, 1) {
			tree x = Q[i], y = x->fa;
			if (y) Up(y->opt, x->opt);
			Down(x->ans, x->opt);
			x->opt = 0;
		}
	}
	int ans = 0;
	for (tree i(base); i != top; ++i) Up(ans, i->ans);
	printf("%d\n", ans);
}

int main() {
	solve();
	return 0;
}
