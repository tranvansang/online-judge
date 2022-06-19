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

#define VII vector<II>
#define VVII vector<VII>

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, m, k; cin >> n >> m >> k;
	VVII g(n, VII());
	while(m--) {
		int u, v, c; cin >> u >> v >> c; u--; v--;
		g[u].pb(mp(v, c)); g[v].pb(mp(u, c));
	}
	while(k--) {
		int t, u, v; cin >> t >> u >> v; u--; v--;
		VI d(n, -1), trace(n, -1);
		map<II, bool> q;
		d[u] = 0;
		q[mp(0, u)] = true;
		while (!q.empty()) {
			int x(q.begin()->fi.se);
			q.erase(mp(d[x], x));
			if (x == v) break;
			for(auto e: g[x]) {
				int y(e.fi), c(e.se);
				if (d[y] == -1 || d[y] > d[x] + c) {
					q.erase(mp(d[y], y));
					d[y] = d[x] + c;
					q[mp(d[y], y)] = true;
					trace[y] = x;
				}
			}
		}
		if (t == 0) cout << d[v] << endl;
		else {
			stack<int> s;
			for(int i(v); i != u; i = trace[i]) s.push(i);
			s.push(u);
			int len(s.size());
			cout << len;
			while(!s.empty()) {
				cout << " " << s.top() + 1;
				s.pop();
			}
			cout << endl;
		}
	}

	return 0;
}