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

#define MAX_M 5000
#define MAX_N 2000
#define LAST_EDGE -1

int nxtCnt(0), start[MAX_N], nxt[MAX_M * 2], adj[MAX_M * 2];
bool visited[MAX_N];
bool marked[MAX_M * 2];

int addEdge(int a, int b) {
	nxt[nxtCnt] = start[a];
	start[a] = nxtCnt;
	adj[nxtCnt] = b;
	nxtCnt++;
	return nxtCnt - 1;
}

int reverseEdge(int e) {
	return e ^ 1;
}

void dfs(int cur, int& ans) {
	visited[cur] = true;
	for (int k = start[cur]; k != LAST_EDGE; k = nxt[k]) {
		if (!marked[k]) {
			marked[k] = marked[reverseEdge(k)] = true;
			int v = adj[k];
			if (!visited[v]) {
				dfs(v, ans);
			} else ans++;
		}
	}
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n, m;

	nxt[0] = LAST_EDGE;
	cin >> n >> m;
	fill_n(start, n, LAST_EDGE);
	fill_n(visited, n, false);
	fill_n(marked, 2 * m, false);

	rep(i, m) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		addEdge(a, b);
		addEdge(b, a);
	}

	int ans(0);
	rep(i, n) {
		if (!visited[i]) dfs(i, ans);
	}
	cout << ans;

	return 0;
}