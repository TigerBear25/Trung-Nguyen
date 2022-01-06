#pragma GCC optimize ("02,unroll-loops,no-stack-protector")
#include<bits/stdc++.h>
#define NAME "groupdiv"
#define fi first
#define se second

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

using namespace std;
using ii = pair<int, int>;
const int MAX = 3e5 + 7;

int n, d, cnt;
int group[MAX], F[MAX];

vector<int> a[MAX];
set<ii> Q;

void load() {
	read(n);
	for(int i = 1; i <= n; ++i) {
		read(d);
		a[i].assign(d, 0);
		for(int &x : a[i]) read(x);
	}
}

void process() {
	for(int i = 1; i <= n; ++i) {
		int sz = (int)a[i].size();
		group[i] = 0;	F[i] = sz;
		Q.insert({-sz, i});
	}

	cnt = 0;
	while(!Q.empty()) {
		ii q = *Q.begin();
		Q.erase(Q.begin());

		if(-q.fi <= 1) {
			cout << "YES\n";
			for(int i = 1; i <= n; ++i)
				if(!group[i]) cout << i << " ";

			cout << "\n";
			for(int i = 1; i <= n; ++i)
				if(group[i]) cout << i << " ";

			break;
		}

		if(++cnt > 4 * n) {
			cout << "NO\n";
			break;
		}

		d = 0;
		for(int x : a[q.se]) {
			Q.erase(Q.lower_bound(ii(-F[x], x)));

			if(group[q.se] == group[x]) {
				--F[x];
				Q.insert({-F[x], x});
			} else {
				++F[x], ++d;
				Q.insert({-F[x], x});
			}
		}

		F[q.se] = d;
		group[q.se] ^= 1;
		Q.insert({-F[q.se], q.se});
	}
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