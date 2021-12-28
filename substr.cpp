#include<bits/stdc++.h>
#define NAME "substr"
using namespace std;

const int MAX = 5e3 + 7;
int n, dp[2][MAX][MAX];
string s;

bool type(char c) {
	if(c == 'a' || c == 'e' || c == 'i'
		|| c == 'o' || c == 'u') return 1;
	return 0;
}

void maximize(int &x, int y) {
	x = max(x, y);
}

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);

    freopen(NAME".inp", "r", stdin);
    freopen(NAME".out", "w", stdout);

    cin >> n >> s;	s = " " + s;
    for(int len = 2; len <= n; ++len)
    	for(int l = 1, r = len; r <= n; ++l, ++r) {
    		dp[0][l][r] = max(dp[0][l + 1][r], dp[0][l][r - 1]);
    		dp[1][l][r] = max(dp[1][l + 1][r], dp[1][l][r - 1]);

    		int k = type(s[l]);
    		if(type(s[r]) == k)
    			maximize(dp[k][l][r], dp[(k + 1) % 2][l + 1][r - 1] + 2);
    	}
    cout << n - max(dp[0][1][n], dp[1][1][n]);

	return 0;
}