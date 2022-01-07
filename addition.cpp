#pragma GCC optimize ("02,unroll-loops,no-stack-protector")
#include<bits/stdc++.h>
#define int long long
#define NAME "addition"
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

int gcd(int a, int b, int &x, int &y) {
	if(b == 0) {
		x = 1;
		y = 0;
		return a;
	}

	int x1, y1, d;
	d = gcd(b, a % b, x1, y1);

	x = y1;
	y = x1 - y1 * (int)(a / b);
	return d;
}

bool check(int a, int b, int c, int &x0, int &y0, int &g) {
	g = gcd(a, b, x0, y0);
	if(c % g) return 0;
	x0 *= (c / g);
	y0 *= (c / g);
	return 1;
}

int countWay(int a, int b, int c) {
	int x, y, g;
	if(!check(a, b, c, x, y, g)) return 0;
	a /= g, b /= g;
	
	int l = (-x) / b;
	int r = y / a;

	if(x % b && (-x) > 0) ++l;
	if(y % a && y < 0) --r;

	if(l > r) return 0;
	return r - l + 1;
}

void solve() {
	int a, b, c, N;
	read(a), read(b), read(c), read(N);

	int res = 0;
	for(int z = 0; c * z <= N; ++z) 
		res += countWay(a, b, N - c * z);
	cout << res << "\n";
}

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);

	freopen(NAME".inp", "r", stdin);
	freopen(NAME".out", "w", stdout);

	int t;	read(t);
	while(t--) solve();

	return 0;
}