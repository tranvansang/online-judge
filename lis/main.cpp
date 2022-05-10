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

// f[l] = gia tri phan tu ket thuc be nhat cua xau co do dai la l
vector<ll> f;

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n; cin >> n;
	rep(i, n) {
		ll x; cin >> x;
		int l(0), h(f.size());
		while(l < h) {
			int m((l + h) / 2);
			if (f[m] <= x) l = m + 1;
			else h = m;
		}
		if (l == f.size()) f.pb(x);
		else f[l] = x;
	}
	cout << f.size();

	return 0;
}