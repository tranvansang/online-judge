#include <bits/stdc++.h>
using namespace std;
#define V vector
#define For(i,a,b) for(auto (i) = (a); (i) < (b); (i)++)
#define rep(i,n) For(i,0,(n))
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define all(a) (a).begin(), (a).end()
#define ll long long

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	int n, m; cin >> n >> m;
	V<int> c;
	while(m--) {
		int x; cin >> x;
		c.pb(x);
	}
	sort(all(c));
	int max_total, price(-1);
	rep(i, c.size()) {
		int total = c[i] * min(n, (int)c.size() - i);
		if (price == -1 || total > max_total) {
			max_total = total;
			price = c[i];
		}
	}
	cout << price << " " << max_total;

	return 0;
}
