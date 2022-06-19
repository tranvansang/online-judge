#include <bits/stdc++.h>
using namespace std;
#define PII pair<int,int>
#define VI vector<int>
#define For(i, a, b) for(auto i = (a); i < (b); i++)
#define rep(i, n) For(i,0,(n))
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define trav(it, x) for(auto it = (x).begin(); it != (x).end(); it++)
#define ll long long

int s, n, k;
vector<PII > families;
map<int, ll> row, col;
map<PII, ll> val;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> s >> n >> k;
	rep(i, n) {
		int x, y, a;
		cin >> x >> y >> a;
		families.pb(mp(x, y));
		col[x] += a;
		row[y] += a;
		val[mp(x, y)] += a;
	}

	ll ret = -1;
	trav(it, families) {
		For(c, it->fi - k, it->fi + 2) if (c >= 0 && c < s - k + 1)
				For(r, it->se - k, it->se + 2) if (r >= 0 && r < s - k + 1) {
						ll cost = 0;
						rep(i, k) cost += col[c + i] + row[r + i];
						rep(i, k) rep(j, k) cost -= val[mp(c + i, r + j)];
						if (ret == -1 || ret > cost) {
							cout << c << " " << r << " " << cost << endl;
							ret = cost;
						}
					}
	}

	cout << ret;
	return 0;
}