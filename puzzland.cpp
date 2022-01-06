#include<bits/stdc++.h>
#define NAME "puzzland"
using namespace std;

int n, m;
int pos[26];
char val[26];

int deg[26];
bool used[26];
vector<int> adj[26];

void loadGraph() {
	cin >> n >> m;
	for(int i = 1; i <= n; ++i) {
		cin >> val[i];
		pos[val[i] - 'A'] = i;

		adj[i].clear();
		used[i] = 0;
		deg[i] = 0;
	}

	for(int i = 1; i <= m; ++i) {
		char x, y;	cin >> x >> y;
		int u = pos[x - 'A'];
		int v = pos[y - 'A'];

		++deg[u], ++deg[v];
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
} 

void dfs(int u, string res) {
	used[u] = 1;
	res.push_back(val[u]);

	if(u == n) {
		if((int)res.size() == n) {
			cout << res << "\n";
			throw 1;
		} 

		used[u] = 0;
		res.pop_back();
		return;
	} 

	for(int v : adj[u]) 
		if(!used[v]) dfs(v, res);

	used[u] = 0;
	res.pop_back();
}

void process() {
	for(int i = 1; i <= n; ++i)
		sort(adj[i].begin(), adj[i].end(), [](const int &x, const int &y) {
			return val[x] < val[y];
		});

	try {
		dfs(1, "");
		cout << "IMPOSSIBLE\n";
	} catch(...) {}
}

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);

	freopen(NAME".inp", "r", stdin);
	freopen(NAME".out", "w", stdout);

	int t;	cin >> t;
	while(t--) {
		loadGraph();
		process();
	}

	return 0;
}