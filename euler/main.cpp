#include <bits/stdc++.h>
using namespace std;
#define II pair<int,int>
#define VI vector<int>
#define VVI vector<VI>
#define For(i,a,b) for(auto i = (a); i < (b); i++)
#define rep(i,n) For(i,0,(n))
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define ll long long

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, m; cin >> n >> m;
	VVI g(n, VI()), r(n, VI());
	VI idx(n, 0);
	rep(i, m) {
		int u, v; cin >> u >> v; u--; v--;
		g[u].pb(v); g[v].pb(u);
		r[u].pb(g[v].size() - 1); r[v].pb(g[u].size() - 1);
	}

	stack<int> s, c;
	s.push(0);
	while(!s.empty()) {
		int x(s.top());
		if (idx[x] < g[x].size()) {
			int y(g[x][idx[x]++]);
			if (r[x][idx[x] - 1] != -1) {
				r[y][r[x][idx[x] - 1]] = -1;
				s.push(y);
			}
		} else {
			c.push(x);
			s.pop();
		}
	}
	while(!c.empty()) {
		cout << c.top() + 1 << " "; c.pop();
	}

	return 0;
}