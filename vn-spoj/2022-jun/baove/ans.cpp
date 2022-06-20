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

#define MAXN 5000
#define MAXS 65000
#define MAXM 10000

int start[MAXN], nxt[MAXM * 2], adj[MAXM * 2], c[MAXM * 2], f[MAXM * 2], trace[MAXN], v[MAXM * 2];
bool visited[MAXN];
int n, m(0);

int reverseEdge(int k) {
	return k ^ 1;
}

void addEdge(int a, int b, int s) {
	nxt[m] = start[a];
	adj[m] = b;
	v[m] = a;
	c[m] = s;
	start[a] = m;
	m++;
}

bool bfs(int init) {
	queue<int> q;
	q.push(init);
	visited[init] = true;

	while (!q.empty()) {
		int x = q.front();
		q.pop();
		if (x == 0) return true;
		for(int k = start[x]; k!= -1; k = nxt[k]) {
			int y = adj[k];
			if (!visited[y]) {
				int cost = c[k];
				if (cost > 0 ? cost > f[k] : f[k]) {
					trace[y] = k;
					visited[y] = true;
					q.push(y);
				}
			}
		}
	}
	return false;
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	scanf("%d", &n);
	fill_n(start, n, -1);
	int a, b, s;
	while (scanf("%d%d%d", &a, &b, &s) == 3) {
		if (s) {
			a--;b--;
			addEdge(a, b, s);
			addEdge(b, a, -s);
		}
	};

	fill_n(f, m, 0);
	fill_n(visited, n, false);
	while (bfs(n - 1)) {
		int minCost = -1;
		for (int y = 0; y != n - 1; y = v[trace[y]]) {
			int k = trace[y];
			int cost = c[k];
			int augment = cost > 0 ? cost - f[k] : f[k];
			if (minCost == -1 || minCost > augment) minCost = augment;
		}
		for (int y = 0; y != n - 1; y = v[trace[y]]) {
			int k = trace[y];
			if (c[k] > 0) {
				f[k] += minCost;
				f[reverseEdge(k)] += minCost;
			} else {
				f[k] -= minCost;
				f[reverseEdge(k)] -= minCost;
			}
		}
		fill_n(visited, n, false);
	}
	int sum = 0;
	for (int k = start[n - 1]; k != -1; k = nxt[k]) {
		if (c[k] > 0) sum += f[k];
	}
	cout << sum;

	return 0;
}
