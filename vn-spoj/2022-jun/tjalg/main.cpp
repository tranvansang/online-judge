#include <bits/stdc++.h>
using namespace std;
#define V vector
#define For(i,a,b) for(auto (i) = (a); (i) < (b); (i)++)
#define rep(i,n) For(i,0,(n))
#define eb emplace_back

V<V<int>> g;
V<int> low, num;
V<bool> removed;
stack<int> s;
int cnt(0), n_comp(0);

void dfs(int x, int p = -1) {
	s.push(x);
	num[x] = low[x] = ++cnt;
	for(auto y: g[x]) if (y != p && !removed[y]) {
		if (!low[y]) {
			dfs(y, x);
			low[x] = min(low[x], low[y]);
		} else low[x] = min(low[x], num[y]);
	}
	if (num[x] == low[x]) {
		n_comp++;removed[x] = true;
		for (auto i = s.top(); i != x; s.pop(), i = s.top())removed[i] = true;
	}
}

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	int n, m; cin >> n >> m;
	g = V<V<int>>(n, V<int>());
	low = V<int>(n);
	num = V<int>(n);
	removed = V<bool>(n);
	while(m--) {
		int u, v; cin >> u >> v; u--; v--;
		g[u].eb(v);
	}
	rep(i, n) if (!num[i]) dfs(i);
	cout << n_comp;

	return 0;
}
