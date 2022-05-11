#include <bits/stdc++.h>
using namespace std;
#define II pair<int,int>
#define VI vector<int>
#define VVI vector<VI>
#define VII vector<II>
#define VVII vector<VII>
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
	VVII g(n, VII());
	while(m--) {
		int u, v, c; cin >> u >> v >> c; u--; v--;
		g[u].pb(mp(v, c)); g[v].pb(mp(u, c));
	}
	VI d(n, -1);
	map<II, bool> q;
	d[0] = 0;
	q[mp(d[0], 0)] = true;
	int sum(0);
	while(!q.empty()) {
		int x(q.begin()->fi.se);
		sum+=d[x];
		q.erase(mp(d[x], x));
		for(auto e: g[x]) {
			int y(e.fi), c(e.se);
			if (d[y] == -1 || d[y] > c) {
				q.erase(mp(d[y], y));
				d[y] = c;
				q[mp(d[y], y)] = true;
			}
		}
	}
	cout << sum;

	return 0;
}