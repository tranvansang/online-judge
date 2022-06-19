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

int m, n;
VVII g;
vector<bool> visited, g_visited;
int cnt(0);

void dfs(int x) {
	visited[x] = true;
	for(auto [y, idx]: g[x]) {
		if (!g_visited[idx]) {
			g_visited[idx] = true;
			if (visited[y]) cnt++;
			else dfs(y);
		}
	}
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;
	g = VVII(n, VII());
	rep(i, m) {
		int u, v; cin >> u >> v; u--; v--;
		g[u].pb(mp(v, i));g[v].pb(mp(u, i));
	}
	visited = vector<bool>(n, false);
	g_visited = vector<bool>(m, false);
	rep(i,n) if (!visited[i]) dfs(i);
	cout << cnt;

	return 0;
}