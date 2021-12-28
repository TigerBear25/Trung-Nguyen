#include<bits/stdc++.h>
#define sz(x) (int)x.size()
#define NAME "factory"
using namespace std;

template<typename T> inline void read(T& x){
    bool Neg = false;
    char c;
    for (c = getchar(); c < '0' || c > '9'; c = getchar())
            if (c == '-') Neg = !Neg;
    x = c - '0';    
    for (c = getchar(); c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    if (Neg) x = -x;
}

struct Edge {
	int v, cap, flow;
	Edge(int _v = 0, int _cap = 0, int _flow = 0) {
		v = _v, cap = _cap, flow = _flow;
	}
};

struct Flow {
	int n, S, T;
	vector < vector <int> > a;
	vector <int> cur, d;
	vector <Edge> e;

	Flow() {}
	Flow(int _n, int _S, int _T) {
		n = _n, S = _S, T = _T;
		a = vector < vector <int> >(n + 1);

		cur = vector <int>(n + 1);
		d = vector <int>(n + 1);

	}

	void addEdge(int u, int v, int _cap) {
		Edge e1 = Edge(v, _cap, 0);
		Edge e2 = Edge(u, 0, 0);

		a[u].push_back(sz(e));	e.push_back(e1);
		a[v].push_back(sz(e));	e.push_back(e2);

	}

	bool bfs() {
		for(int i = 0; i <= n; ++i) d[i] = -1;
		queue<int> Q;	Q.push(S);	d[S] = 0;

		while(!Q.empty() && d[T] < 0) {
			int u = Q.front();	Q.pop();

			for(int i = 0; i < sz(a[u]); ++i) {
				int id = a[u][i], v = e[id].v;

				if(d[v] < 0 && e[id].flow < e[id].cap) {
					d[v] = d[u] + 1;
					Q.push(v);
				}
			}
		} return d[T] >= 0;
	}

	int dfs(int u, int val) {
		if(!val) return 0;
		if(u == T) return val;

		for(; cur[u] < sz(a[u]); ++cur[u]) {
			int id = a[u][cur[u]], v = e[id].v;
			if(d[v] != d[u] + 1) continue;

			int nVal = dfs(v, min(val, e[id].cap - e[id].flow));
			if(nVal) {
				e[id].flow += nVal;
				e[id ^ 1].flow -= nVal;
				return nVal;
			}
		} return 0;
	}

	int maxFlow(int tmp) {
		int res = tmp;
		while(bfs()) {
			for(int i = 0; i <= n; ++i) cur[i] = 0;
			while(true) {
				int val = dfs(S, INT_MAX);
				if(!val) break;
				res -= 2 * val;
			} 
		} return res;
	}
};

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

int t, n, m;
char a[410][410], tmp;

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);

	freopen(NAME".inp", "r", stdin);
    freopen(NAME".out", "w", stdout);
	
    read(t);
	while(t--) {
		read(n), read(m);
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= m; ++j) 
				a[i][j] = getchar();
			tmp = getchar();
		}

		Flow F(n * m + 1, 0, n * m + 1);

		int cnt = 0;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j) {
				cnt += (a[i][j] == '1');
				int node = (i - 1) * m + j;

				if(a[i][j] == '1') {
					if((i % 2) == (j % 2)) {
						F.addEdge(0, node, 1);

						for(int k = 0; k < 4; ++k) {
							int i_nxt = i + dx[k], j_nxt = j + dy[k];

							if(1 <= i_nxt && i_nxt <= n && 1 <= j_nxt 
								&& j_nxt <= m && a[i_nxt][j_nxt] == '1') {
									int node_nxt = (i_nxt - 1) * m + j_nxt;
									F.addEdge(node, node_nxt, 1);
								}
						}
					} else F.addEdge(node, n * m + 1, 1);
				}
			}
		cout << F.maxFlow(cnt) << "\n";
	}

	return 0;
}
