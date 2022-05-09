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

#define NMAX 50000
#define VMAX 15000

int a[NMAX + 1], s[NMAX + 1];

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, m;
	cin >> n;
	rep(i, n) {
		int x;cin >> x;a[i] = x;
		s[i + 1] = s[i] + x;
	}
	cin >> m;
	rep(i, m) {
		int x, y; cin >> x >> y;
		x--; y--;

		int ans = 0;
		For(j, x, y + 1) {
			For(k, j, y + 1) {
				ans = max(ans, s[k + 1] - s[j]);
			}
		}
		cout << ans << endl;
	}
	return 0;
}