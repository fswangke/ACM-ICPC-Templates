const int maxn = 1111, maxm = 1111111;
const int inf = 1000000000;
namespace EdmondsAlgorithm { // O(ElogE + V^2) !!!0-based!!!
    
    int n, m, a, b, c, x[maxn], y[maxn], z[maxn],
	edgeCnt, firstEdge[maxn], from[maxm], nextEdge[maxm],
	inEdge[maxn], depth[maxm], child[maxm][2],
	parent[maxn], choosen[maxn], degree[maxn], queue[maxn];
    int length[maxm], key[maxm], delta[maxm];

void pass (int x) {
	if (delta[x] != 0) {
		key[child[x][0]] += delta[x];
		delta[child[x][0]] += delta[x];
		key[child[x][1]] += delta[x];
		delta[child[x][1]] += delta[x];
		delta[x] = 0;
	}
}

int merge (int x, int y) {
	if (x == 0 or y == 0) {
		return x ^ y;
	}
	if (key[x] > key[y]) {
		swap(x, y);
	}
	pass(x);
	child[x][1] = merge(child[x][1], y);
	if (depth[child[x][0]] < depth[child[x][1]]) {
		swap(child[x][0], child[x][1]);
	}
	depth[x] = depth[child[x][1]] + 1;
	return x;
}

void addEdge (int u, int v, int w) {
	from[++ edgeCnt] = u;
	length[edgeCnt] = w;
	nextEdge[edgeCnt] = firstEdge[v];
	firstEdge[v] = edgeCnt;
	key[edgeCnt] = w;
	delta[edgeCnt] = 0;
	depth[edgeCnt] = 0;
	child[edgeCnt][0] = child[edgeCnt][1] = 0;
	inEdge[v] = merge(inEdge[v], edgeCnt);
}

void deleteMin (int &r) {
	pass(r);
	r = merge(child[r][0], child[r][1]);
}

int findRoot (int u) {
	if (parent[u] != u) {
		parent[u] = findRoot(parent[u]);
	}
	return parent[u];
}

void clear (int E) {
	edgeCnt = 0;
	depth[0] = -1;
    for(int i = 0; i <= E; ++i)
        inEdge[i] = firstEdge[i] = 0;
}

int solve (int root) {
	int result = 0;
	for (int i = 0; i < n; ++ i) {
		parent[i] = i;
	}
	while (true) {
		memset(degree, 0, sizeof(degree));
		for (int i = 0; i < n; ++ i) {
			if (i == root or parent[i] != i) {
				continue;
			}
			while (findRoot(from[inEdge[i]]) == findRoot(i)) {
				deleteMin(inEdge[i]);
			}
			choosen[i] = inEdge[i];
			degree[findRoot(from[choosen[i]])] += 1;
		}
		int head = 0, tail = 0;
		for (int i = 0; i < n; ++ i) {
			if (i != root and parent[i] == i and degree[i] == 0) {
				queue[tail ++] = i;
			}
		}
		while (head < tail) {
			if (-- degree[findRoot(from[choosen[queue[head]]])] == 0) {
				queue[tail ++] = findRoot(from[choosen[queue[head]]]);
			}
			head += 1;
		}
		bool found = false;
		for (int i = 0; i < n; ++ i) {
			if (i != root and parent[i] == i and degree[i] > 0) {
				found = true;
				int j = i, temp = 0;
				do{
					j = findRoot(from[choosen[j]]);
					parent[j] = i;
					deleteMin(inEdge[j]);
					result += key[choosen[j]];
					key[inEdge[j]] -= key[choosen[j]];
					delta[inEdge[j]] -= key[choosen[j]];
					temp = merge(temp, inEdge[j]);
				} while (j != i);
				inEdge[i] = temp;
			}
		}
		if (not found) {
			break;
		}
	}
	for (int i = 0; i < n; ++ i) {
		if (i != root and parent[i] == i) {
			result += key[choosen[i]];
		}
	}
	return result;
}

}

namespace ChuLiu { // O(V ^ 3) !!!1-based!!!

int n, m, used[maxn], pass[maxn], eg[maxn], more, queue[maxn];

int g[maxn][maxn];

void combine(int id, int &sum) {
	int tot = 0, from, i, j, k;
	for (; id != 0 && !pass[id]; id = eg[id]) {
		queue[tot++] = id;
		pass[id] = 1;
	}
	for (from = 0; from < tot && queue[from] != id; from++);
	if (from == tot) return;
	more = 1;
	for (i = from; i < tot; i++) {
		sum += g[eg[queue[i]]][queue[i]];
		if (i != from) {
			used[queue[i]] = 1;
			for (j = 1; j <= n; j++)
				if (!used[j])
					if (g[queue[i]][j] < g[id][j])
						g[id][j] = g[queue[i]][j];
		}
	}
	for (i = 1; i <= n; i++)
		if (!used[i] && i != id) {
			for (j = from; j < tot; j++) {
				k = queue[j];
				if (g[i][id] > g[i][k] - g[eg[k]][k])
					g[i][id] = g[i][k] - g[eg[k]][k];
			}
		}
}
void clear(int V)
{
    for(int i = 1; i <= V; ++i)
        for(int j = 1; j <= V; ++j)
            g[i][j] = inf;
}
int solve(int root) { // return the total length of MDST
	int i, j, k, sum = 0;
	memset(used, 0, sizeof(used));
	for (more = 1; more;) {
		more = 0;
		memset(eg, 0, sizeof(eg));
		for (i = 1; i <= n; i++)
			if (!used[i] && i != root) {
				for (j = 1, k = 0; j <= n; j++)
					if (!used[j] && i != j)
						if (k == 0 || g[j][i] < g[k][i])
							k = j;
				eg[i] = k;
			}
		memset(pass, 0, sizeof(pass));
		for (i = 1; i <= n; i++)
			if (!used[i] && !pass[i] && i != root)
				combine(i, sum);
	}
	for (i = 1; i <= n; i++)
		if (!used[i] && i != root)
			sum += g[eg[i]][i];
	return sum;
}
}
