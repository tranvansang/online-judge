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

VI nxt, adj;
int start[100], match[100];
bool visited[100];

bool dfs(int x) {
	visited[x] = true;
	for (int k = start[x]; k != -1; k = nxt[k]) {
		int y = adj[k];
		if (match[y] == -1 || !visited[match[y]] && dfs(match[y])) {
			match[y] = x;
			return true;
		}
	}
	return false;
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int m, n; scanf("%d%d", &m, &n);
	fill_n(start, m, -1);
	int u, v;
	while(scanf("%d%d", &u, &v) == 2) {
		u--; v--;
		nxt.pb(start[u]);
		start[u] = nxt.size() - 1;
		adj.pb(v);
	}

	fill_n(match, n, -1);
	int cnt(0);
	rep(i, m) {
		fill_n(visited, m, false);
		cnt += dfs(i);
	}

	cout << cnt << endl;
	rep(i, n) {
		if (match[i] != -1) cout << match[i] + 1 << " " << i + 1 << endl;
	}

	return 0;
}