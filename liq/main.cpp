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

int a[1000], f[1000];

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n; cin >> n;
	rep(i, n) {
		int x; cin >> x; a[i] = x;
	}

	fill_n(f, n, 1);
	int ret = 1;
	rep(i, n) {
		rep(j, i) if (a[j] < a[i] && f[j] + 1 > f[i]) f[i] = f[j] + 1;
		ret = max(ret, f[i]);
	}
	cout << ret;

	return 0;
}