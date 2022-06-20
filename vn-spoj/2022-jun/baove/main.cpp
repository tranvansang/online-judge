#include <bits/stdc++.h>
using namespace std;
#define V vector
#define For(i,a,b) for(auto (i) = (a); (i) < (b); (i)++)
#define rep(i,n) For(i,0,(n))
#define mt make_tuple
#define eb emplace_back
#define all(a) (a).begin(), (a).end()
#define ll long long

V<tuple<int,int>> trace;
V<V<tuple<int,int,int, int>>> g;

// dfs gets TLE
// bfs ACCEPTED
bool dfs(int x) {
	if (!x) return true;
	rep(i, g[x].size()) {
		auto &[y, cost, reverse_idx, flow] = g[x][i];
		auto &[y_trace_vertex, y_trace_idx] = trace[y];
		if ((cost > 0 ? cost > flow : flow) && y_trace_vertex == -1) {
			y_trace_vertex = x; y_trace_idx = i;
			if(dfs(y)) return true;
		}
	}
	return false;
}

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	int n; scanf("%d", &n);
	g = V<V<tuple<int,int,int,int>>>(n, V<tuple<int,int,int,int>>());
	int u, v, c;
	while (scanf("%d%d%d", &u, &v, &c) == 3) if (c) {
		u--; v--;
		g[u].eb(v, c, g[v].size(), 0);
		g[v].eb(u, -c, g[u].size() - 1, 0);
	}
	int sum(0);
	while(true) {
		trace = V<tuple<int,int>>(n, mt(-1, 0));
		if (!dfs(n-1)) break;
		int aug = -1;
		for(auto y = 0; y != n-1; ) {
			auto &[x, idx] = trace[y];
			auto &[_y, cost, reverse_idx, flow] = g[x][idx];
			y = x;
			int current_aug = cost > 0 ? cost - flow : flow;
			if (aug == -1 || aug > current_aug) aug = current_aug;
		}
		sum += aug;
		for(auto y = 0; y != n-1; ) {
			auto &[x, idx] = trace[y];
			auto &[_y, cost, reverse_idx, flow] = g[x][idx];
			if (cost > 0) flow += aug; else flow -= aug;
			get<3>(g[y][reverse_idx]) = flow;
			y = x;
		}
	}
	cout << sum;

	return 0;
}
