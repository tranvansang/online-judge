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

#define MAXN 200

int c[MAXN][MAXN];
int match[MAXN], fx[MAXN], fy[MAXN];
bool visited[MAXN];
int n;

bool dfs(int x) {
	rep(y, n) {
		if (c[x][y] == fx[x] - fy[y] && !visited[y]) {
			visited[y] = true;
			if (match[y] == -1 || dfs(match[y])) {
				match[y] = x;
				return true;
			}
		}
	}
	return false;
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	rep(i, n) {
		rep(j, n) {
			cin >> c[i][j];
		}
	}
	fill_n(match, n, -1);
	rep(i, n) {
		while (true) {
			fill_n(visited, n, false);
			if (dfs(i)) break;
			int val = -1;
			For(j, -1, n) {
				if (j == -1 || visited[j]) {
					int x = j == -1 ? i : match[j];
					rep(y, n) {
						if (!visited[y]) {
							if (val == -1 || val > c[x][y]) {
								val = c[x][y];
							}
						}
					}
				}
			}
			For(j, -1, n) {
				if (j == -1 || visited[j]) {
					int x = j == -1 ? i : match[j];
					fx[x] += val;
				}
			}
			rep(y, n) {
				if (visited[y]) {
					fy[y] += val;
				}
			}
		}
	}
	int ret = 0;
	rep(i, n) {
		if (c[match[i]][i] > ret) ret = c[match[i]][i];
	}
	cout << ret;
	return 0;
}