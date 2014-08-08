#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <utility>
#include <queue>
#include <stack>

#define rep(I,L,R) for(int I(L);I<=R;++I)
#define reprv(I,L) for(int I(L);I;--I)
#define for_(IT,C) for(__typeof(C.begin())IT(C.begin());IT!=C.end();++IT)

using namespace std;

const int Maxn = 110000, Maxm = 1100000;

int getint()
{
   char ch = getchar();
   for ( ; ch > '9' || ch < '0'; ch = getchar());
   int tmp = 0;
   for ( ; '0' <= ch && ch <= '9'; ch = getchar())
     tmp = tmp * 10 + int(ch) - 48;
   return tmp;
}

namespace LCT
{
	#define nil NULL
	class node
	{
	public:
		node *l, *r, *f, *u, *v, *mp;
		int w, m, id;
		bool rev;
		node()
		{
			l = r = f = u = v = mp = nil;
			w = m = id = rev = 0;
		}
		void update()
		{
			m = w, mp = this;
			if(l && l -> m > m) m = l -> m, mp = l -> mp;
			if(r && r -> m > m) m = r -> m, mp = r -> mp;
		}
		void pushdown()
		{
			if(rev)
			{
				rev = false;
				swap(l, r);
				if(l) l -> rev ^= 1;
				if(r) r -> rev ^= 1;
			}
		}
	};
	stack<node*> sta;
	node pool[Maxn + Maxm + 100], *cur = pool, *T[Maxn + 10];
	node* newnode(int w)
	{
		node *ret = cur++;
		ret -> w = ret -> m = w;
		ret -> mp = ret;
		return ret;
	}
	node* newnode(node *U, node *V, int w)
	{
		node *ret = newnode(w);
		ret -> u = U, ret -> v = V;
		return ret;
	}
	node* newnode(int x, int y, int w)
	{
		return newnode(T[x], T[y], w);
	}

	void init() //this procedure must be called first
	{
		for(int i = 0; i < Maxn + 10; ++i)
		{
			T[i] = cur++;
			T[i] -> id = i;
		}
	}
	//Basic operation collection
	class Splay
	{
	public:
		bool isroot(node *x)
		{
			if(!x) return false;
			if(!(x -> f)) return true;
			if(x -> f -> l == x || x -> f -> r == x) return false;
			return true;
		}
		void up(node *x)
		{
			while(!isroot(x)) sta.push(x), x = x -> f;//up(x -> f);
			x -> pushdown();
			while(!sta.empty()) x = sta.top(), x -> pushdown(), sta.pop();
		}
		void Zig(node *x)
		{
			node *f = x -> f, *g = f -> f;
			if(!isroot(f)) g -> pushdown();
			if(!isroot(x)) f -> pushdown();
			if(x != nil) x -> pushdown();
			if(g && g -> l == f) g -> l = x;
			else if(g && g -> r == f) g -> r = x;
			x -> f = g;
			if(x -> r) x -> r -> f = f;
			f -> l = x -> r;
			x -> r = f;
			f -> f = x;
			f -> update();
			x -> update();
		}
		void Zag(node *x)
		{
			node *f = x -> f, *g = f -> f;
			if(!isroot(f)) g -> pushdown();
			if(!isroot(x)) f -> pushdown();
			if(x != nil) x -> pushdown();
			if(g && g -> l == f) g -> l = x;
			else if(g && g -> r == f) g -> r = x;
			x -> f = g;
			if(x -> l) x -> l -> f = f;
			f -> r = x -> l;
			x -> l = f;
			f -> f = x;
			f -> update();
			x -> update();
		}
		void splay(node *x)
		{
			if(!x) return;
			up(x);
			while(!isroot(x))
			{
				node *f, *g;
				f = x -> f, g = f -> f;
				
				if(!isroot(f)) g -> pushdown();
				if(!isroot(x)) f -> pushdown();
				if(x != nil) x -> pushdown();
				if(isroot(f))
				{
					if(f -> l == x) Zig(x);
					else Zag(x);
				}
				else
				{
					if(g -> l == f)
					{
						if(f -> l == x) Zig(f), Zig(x);
						else Zag(x), Zig(x);
					}
					else
					{
						if(f -> r == x) Zag(f), Zag(x);
						else Zig(x), Zag(x);
					}
				}
			}
			x -> update();
		}
	};
	Splay st;
	void expose(node *x)
	{
		for(node *y = nil; x; x = x -> f)
		{
			st.splay(x), x -> r = y, x -> update(), y = x;
		}
	}
	inline void evert(node *x){ expose(x), st.splay(x), x -> rev ^= 1;}
	inline void link(node *x, node *y)
	{
		evert(x);
		st.splay(x);
		x -> f = y;
		expose(x);
	}
	inline void cut(node *x, node *y)
	{
		expose(x);
		st.splay(y);
		//y -> pushdown(), x -> pushdown();
		if(y -> f != x)
		{
			expose(y), st.splay(x);
			x -> f = nil;
			if(y -> l == x) y -> l = nil;
			if(y -> r == x) y -> r = nil;
			x -> update();
			y -> update();
		}
		else
		{
			y -> f = nil;
			if(x -> l == y) x -> l = nil;
			else if(x -> r == y) x -> r = nil;
			x -> update();
			y -> update();
		}
	}

	pair<int, node*> query(node *x, node* y)
	{
		int ret = 0;
		node *retp = 0;
		expose(x);
		for(x = nil; y; x = y, y = y -> f)
		{
			st.splay(y);

			if(y -> f == nil)
			{
				if(y -> w > ret) ret = y -> w, retp = y;
				if(y -> r && y -> r -> m > ret) ret = y -> r -> m, retp = y -> r -> mp;
				if(x && x -> m > ret) ret = x -> m, retp = x -> mp;
			}
			y -> r = x, y -> update();
		}
		return make_pair(ret, retp);
	}
	int query(int x, int y)
	{
		return query(T[x], T[y]).first;
	}
	inline void update_mst(int u, int v, int w)
	{
		node *x = T[u], *y = T[v], *r = query(x, y).second;
		if(!r || r -> w <= w) return;
		cut(r -> u, r), cut(r, r -> v);
		node *t = newnode(u, v, w);
		link(x, t), link(t, y);
	}
	class edge
	{
	public:
		int t, w;
		edge *n;
		edge(){}
		edge(int T, int W, edge *N)
		{
			t = T, w = W, n = N;
		}
	}ebf[Maxn * 10], *ec, *h[Maxn * 10];
	
	void initedge()
	{
		ec = ebf;
		for(int i = 0; i < Maxn + 10; ++i)
			h[i] = nil;
	}

	void addedge(int u, int v, int w)
	{
		edge *nxt;
		nxt = ec++;
		nxt -> n = h[u];
		h[u] = nxt;
		nxt -> t = v;
		nxt -> w = w;
	}
	queue<int> q;
	int fa[Maxn + 10];
	
	//LCT builder
	void bfs()
	{
		while(!q.empty()) q.pop();
		q.push(1);
		while(!q.empty())
		{
			int cur = q.front();
			q.pop();
			for(edge *x = h[cur]; x; x = x -> n)
			{
				if(x -> t != fa[cur])
				{
					fa[x -> t] = cur;
					T[x -> t] -> f = newnode(cur, x -> t, x -> w);
					T[x -> t] -> f -> f = T[cur];
					q.push(x -> t);
				}
			}
		}
	}
}
