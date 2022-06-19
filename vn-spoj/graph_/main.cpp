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
#define ll long long

VVI g;
int cutEdgeCnt, cutVertexCnt, dfsClock;
int low[10000], num[10000];

void dfs(int x, int p) {
	low[x] = num[x] = ++dfsClock;
	int nchild = 0;
	bool isCutVertex(false);
	for (auto y: g[x]) if (y != p) {
		if (low[y]) low[x] = min(low[x], num[y]);
		else {
			nchild++;
			dfs(y, x);
			low[x] = min(low[x], low[y]);
			if (low[y] == num[y]) cutEdgeCnt++;
			if (low[y] >= num[x]) isCutVertex = true;
		}
	}
	if (p == -1 ? nchild > 1 : isCutVertex) cutVertexCnt++;
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, m;cin >> n >> m;
	g = VVI(n, VI());
	rep(i, m) {
		int u, v;cin >> u >> v;
		g[--u].pb(--v);g[v].pb(u);
	}
	rep(i, n) if (!low[i]) dfs(i, -1);
	cout << cutVertexCnt << " " << cutEdgeCnt;

	return 0;
}