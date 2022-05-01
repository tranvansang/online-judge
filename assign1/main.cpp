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
int match[MAXN];
bool visited[MAXN];
int n, mid;

bool dfs(int x) {
	rep(y, n) {
		if (!visited[y] && c[x][y] <= mid) {
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
	rep(i, n) rep(j, n) cin >> c[i][j];
	int l(c[0][0]), h(c[0][0]);
	rep(i, n) rep(j, n) {
			l = min(l, c[i][j]);
			h = max(h, c[i][j]);
	}
	while (l < h) {
		mid = (l + h) / 2;

		bool possible = true;
		rep(i, n) {
			fill_n(match, n, -1);
			fill_n(visited, n, false);
			if (!dfs(i)) {
				possible = false;
				break;
			}
		}

		if (possible) h = mid;
		else l = mid + 1;
	}
	cout << l;
	return 0;
}