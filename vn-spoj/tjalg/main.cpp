#include <bits/stdc++.h>
using namespace std;
#define PII pair<int,int>
#define VI vector<int>
#define VVI vector<VI>
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
VVI g;
stack<int> s;
int low[NMAX], num[NMAX], comp[NMAX];
int cnt(0), numCnt(0);

void dfs(int x) {
	s.push(x);
	num[x] = low[x] = ++numCnt;
	trav(it, g[x]) {
		int y = *it;
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
	g = VVI(n, VI());
	rep(i, m) {
		int u, v; cin >> u >> v;
		g[--u].pb(--v);
	}
	rep(i, n) if (!num[i]) dfs(i);
	cout << cnt;

	return 0;
}