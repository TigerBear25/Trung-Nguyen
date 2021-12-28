#include<bits/stdc++.h>
#define fi first
#define se second
#define NAME "equation"
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

typedef pair<int, int> ii;
const int MOD = 1e9 + 7;
const int MAX = 1e6 + 7;

ii a[22];
int n, m, k;
int h[22], s[MAX];
int dp[22][MAX];

int Add(int a, int b) {
    if((a += b) >= MOD) a -= MOD;
    return a;
}

int Sub(int a, int b) {
    if((a -= b) < 0) a += MOD;
    return a;
}

void load() {
    read(n), read(m), read(k);
    for(int i = 1; i <= n; ++i) a[i] = {0, m};

    while(k--) {
        int type, pos, val;
        read(type), read(pos), read(val);

        if(type == 1) a[pos].fi = max(a[pos].fi, val);
        else a[pos].se = min(a[pos].se, val);
    }
}

void process() {
    for(int i = 1; i <= n; ++i) {
        h[i] = a[i].se - a[i].fi;
        m -= a[i].fi;

        if(h[i] < 0) {
            cout << "0";
            exit(0);
        }
    }

    for(int j = 0; j <= min(h[1], m); ++j) dp[1][j] = 1;
    for(int i = 2; i <= n; ++i) {
        s[0] = dp[i][0] = dp[i - 1][0];
        for(int j = 1; j <= m; ++j) {
            s[j] = Add(s[j - 1], dp[i - 1][j]);
            int nxt = j - h[i];
            if(nxt <= 0) dp[i][j] = s[j];
            else dp[i][j] = Sub(s[j], s[nxt - 1]);
        }
    } cout << dp[n][m];
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    freopen(NAME".inp", "r", stdin);
    freopen(NAME".out", "w", stdout);

    load();
    process();

    return 0;
}
