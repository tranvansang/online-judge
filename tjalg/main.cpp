#include <bits/stdc++.h>
using namespace std;
#define PII pair<int,int>
#define VI vector<int>
#define For(i,a,b) for(auto i = (a); i < (b); i++)
#define rep(i,n) For(i,0,(n))
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define trav(it,x) for(auto it = (x).begin(); it != (x).end(); it++)
#define ll long long

#define NMAX 10000
VI nxt, adj;
stack<int> s;
int start[NMAX], low[NMAX], num[NMAX], comp[NMAX];
int cnt(0), numCnt(0);

void dfs(int x) {
	s.push(x);
	num[x] = low[x] = ++numCnt;
	for(int k = start[x]; k != -1; k = nxt[k]) {
		int y = adj[k];
		if (!comp[y]) {
			if (!num[y]) {
				dfs(y);
				low[x] = min(low[x], low[y]);
			} else low[x] = min(low[x], num[y]);
		}
	}
	if (low[x] == num[x]) {
		cnt++; int last;
		do {
			comp[last = s.top()] = cnt; s.pop();
		} while (last != x);
	}
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, m; cin >> n >> m;
	fill_n(start, n, -1);
	rep(i, m) {
		int u, v; cin >> u >> v;
		u--; v--;
		nxt.pb(start[u]);
		adj.pb(v);
		start[u] = nxt.size() - 1;
	}
	rep(i, n) if (!num[i]) dfs(0);
	cout << cnt;

	return 0;
}