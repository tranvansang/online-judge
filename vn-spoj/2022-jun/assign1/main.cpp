#include <bits/stdc++.h>
using namespace std;
#define II pair<int,int>
#define VI vector<int>
#define VVI vector<VI>
#define VII vector<II>
#define VVII vector<VII>
#define For(i,a,b) for(auto (i) = (a); (i) < (b); (i)++)
#define rep(i,n) For(i,0,(n))
#define fi first
#define se second
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define all(a) (a).begin(), (a).end()
#define ll long long

#define MAXN 200
VVI c;
VI match;
vector<bool> visited;
int limit, n;

bool dfs(int x) {
	visited[x] = true;
	rep(i, n) if (c[x][i] <= limit) {
		if (match[i] == -1 || !visited[match[i]] && dfs(match[i])) {
			match[i] = x;
			return true;
		}
	}
	return false;
}

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	cin >> n;
	c = VVI(n, VI(n, 0));
	set<int> val;
	rep(i, n) rep(j, n) {
		int x; cin >> x;
		c[i][j] = x;
		val.insert(x);
	}
	for(auto v: val) {
		limit = v;
		match = VI(n, -1);
		bool possible = true;
		rep(i, n) {
			visited = vector<bool>(n, false);
			if (!dfs(i)) {
				possible = false;
				break;
			}
		}
		if (possible) {
			cout << v;
			break;
		}
	}

	return 0;
}
