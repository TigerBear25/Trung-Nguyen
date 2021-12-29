#include<bits/stdc++.h>
#define NAME "fill"
using namespace std;

struct Pool {
    int b, h, w, d;
    void input() {
        cin >> b >> h >> w >> d;
    }
};

const int N = 1011010;
const int MAX = 1e5 + 7;
int n, V, f[N];
Pool a[MAX];

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);

    freopen(NAME".inp", "r", stdin);
    freopen(NAME".out", "w", stdout);

    cin >> n >> V;
    for(int i = 1; i <= n; ++i) {
        a[i].input();
        f[a[i].b + 1] += a[i].w * a[i].d;
        f[a[i].b + a[i].h + 1] -= a[i].w * a[i].d;
    }

    for(int i = 1; i < N; ++i) {
        f[i] += f[i - 1];
        if(V - f[i] > 0) V -= f[i];
        else {
            if(V - f[i] == 0) cout << i << ".00";
            else cout << fixed << setprecision(2) << double(V) / double(f[i]) + double(i - 1);
            break;
        }
    }

	return 0;
}