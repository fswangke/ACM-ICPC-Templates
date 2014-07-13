
inline bool randomBySize(int a, int b) {
	return rand() % (a + b) < a;
}

tree merge(tree x, tree y) {
	if (x == null) return y;
	if (y == null) return x;
	tree t = NULL;
	if (randomBySize(x->size, y->size)) {
		t = newNode(x);
		t->r = merge(x->r, y);
	}
	else {
		t = newNode(y);
		t->l = merge(x, y->l);
	}
	update(t);
	return t;
}

void splitByKey(tree t, int k, tree &l, tree &r) { // [-oo, k) [k, +oo)
	if (t == null) l = r = null;
	else if (t->key < k) {
		l = newNode(t);
		splitByKey(t->r, k, l->r, r);
		update(l);
	}
	else {
		r = newNode(t);
		splitByKey(t->l, k, l, r->l);
		update(r);
	}
}
