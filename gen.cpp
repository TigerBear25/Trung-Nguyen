#include<bits/stdc++.h>
#define NAME "gen"
using namespace std;

const int N = 510;
const int M = 22;

int n, m;
int dp[N];
int a[M][N];
int pos[M][N];

bool ok(int x, int y) {
	for(int i = 2; i <= m; ++i)
		if(pos[i][x] > pos[i][y]) return 0;
	return 1;
}

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);

    freopen(NAME".inp", "r", stdin);
    freopen(NAME".out", "w", stdout);

    cin >> n >> m;
    for(int i = 1; i <= m; ++i)
    	for(int j = 1; j <= n; ++j) {
    		cin >> a[i][j];
    		pos[i][a[i][j]] = j;
    	}

    for(int i = 1; i <= n; ++i) {
    	dp[i] = 1;
    	for(int j = 1; j < i; ++j)  if(ok(a[1][j], a[1][i])) 
    		dp[i] = max(dp[i], dp[j] + 1);
    } cout << *max_element(dp + 1, dp + 1 + n);

	return 0;
}