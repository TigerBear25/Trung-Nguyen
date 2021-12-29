#include<bits/stdc++.h>
#define NAME "string"
#define fi first
#define se second

using namespace std;
using ii = pair<int, int>;

const int N = 2010;
const int MOD = 1e9 + 7;

int n, k;
char a[N][22];

ii dist[N];
bool inQueue[N];
vector<int> adj[N];

void add(int &x, int y) { if((x += y) >= MOD) x -= MOD; }

void loadGraph() {
    cin >> n >> k;

    string s;   cin >> s;   k = (int)s.size();
    for(int i = 1; i <= k; ++i) a[0][i] = s[i - 1];

    int cnt = 0;
    for(int i = 1; i <= k; ++i) {
        cin >> a[n + 1][i];
        cnt += (a[0][i] != a[n + 1][i]);
    }

    if(cnt <= 1) {
        if(cnt == 1) cout << "1 1";
        else cout << "0 1";
        exit(0);
    }

    for(int i = 1; i <= n; ++i) {
        int cntS = 0, cntT = 0;
        for(int j = 1; j <= k; ++j) {
            cin >> a[i][j];
            cntS += (a[i][j] != a[0][j]);
            cntT += (a[i][j] != a[n + 1][j]);
        }

        if(cntS == 1) adj[0].push_back(i);
        if(cntT == 1) adj[i].push_back(n + 1);
    }

    for(int i = 1; i < n; ++i)
        for(int j = i + 1; j <= n; ++j) {
            cnt = 0;
            for(int t = 1; t <= k; ++t) 
                cnt += (a[i][t] != a[j][t]);

            if(cnt == 1) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
}

void process() {
    for(int i = 1; i <= (n + 1); ++i) dist[i] = {INT_MAX, 0};
    queue<int> Q;   Q.push(0);  dist[0] = {0, 1};  

    while(!Q.empty()) {
        int u = Q.front();  Q.pop();
        if(u == (n + 1)) break;
        inQueue[u] = 0;

        for(int v : adj[u]) 
            if(dist[v].fi > dist[u].fi + 1) {
                dist[v] = {dist[u].fi + 1, dist[u].se};
                if(!inQueue[v]) {
                    Q.push(v);
                    inQueue[v] = 1;
                }

            } else if(dist[v].fi == dist[u].fi + 1) {
                add(dist[v].se, dist[u].se);
                if(!inQueue[v]) {
                    Q.push(v);
                    inQueue[v] = 1;
                }
            }
    }

    if(dist[n + 1].fi == INT_MAX) cout << "-1 -1";
    else cout << dist[n + 1].fi << " " << dist[n + 1].se;
}

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);

    freopen(NAME".inp", "r", stdin);
    freopen(NAME".out", "w", stdout);

    loadGraph();
    process();            

	return 0;
}