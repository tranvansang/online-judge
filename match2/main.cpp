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

VI adj, nxt, cost;
int start[200], f[200], g[200], match[200];
bool visited[200], visitedY[200];

bool dfs(int x) {
	visited[x] = true;
	for (int k = start[x]; k != -1; k = nxt[k]) {
		int y = adj[k], c = cost[k];
		if (c == f[x] - g[y]) {
			visitedY[y] = true;
			if (match[y] == -1 || !visited[match[y]] && dfs(match[y])) {
				match[y] = x;
				return true;
			}
		}
	}
	return false;
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n; scanf("%d", &n);
	fill_n(start, n, -1);
	fill_n(match, n, -1);

	int u, v, c;
	while (scanf("%d%d%d", &u, &v, &c) == 3) {
		u--; v--;
		nxt.pb(start[u]);
		adj.pb(v);
		cost.pb(c);
		start[u] = nxt.size() - 1;
	}

	rep(i, n) {
		while (true) {
			fill_n(visited, n, false);
			fill_n(visitedY, n, false);
			if (dfs(i))break;
			int aug = -1;
			rep(x, n) if (visited[x]) {
				for (int k = start[x]; k != -1; k = nxt[k]) {
					int y = adj[k]; c = cost[k];
					if (!visitedY[y] && (aug == -1 || aug > c - f[x] + g[y])) aug = c - f[x] + g[y];
				}
			}
			if (aug == -1) break;
			rep(x, n) if (visited[x]) f[x] += aug;
			rep(x, n) if (visitedY[x]) g[x] += aug;
		}
	}

	int sum = 0;
	rep(i, n) sum += f[i] - g[i];
	cout << sum << endl;
	rep(i, n) cout << match[i] + 1 << " " << i + 1 << endl;

	return 0;
}