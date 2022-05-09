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

#define MAX 50000

int it[MAX * 8], maxIt[MAX * 8];
#define Left(idx) ((idx) << 1)
#define Right(idx) (((idx) << 1) + 1)

void update(int idx, int l, int h, int u, int v, int k) {
	if (u > h || v < l) return;
	if (u <= l && h <= v) {
		it[idx] += k;
		maxIt[idx] += k;
		return;
	}
	int mid = (l + h) / 2;
	it[Left(idx)] += it[idx]; maxIt[Left(idx)] += it[idx];
	it[Right(idx)] += it[idx]; maxIt[Right(idx)] += it[idx];
	it[idx] = 0;
	update(Left(idx), l, mid, u, v, k);
	update(Right(idx), mid + 1, h, u, v, k);
	maxIt[idx] = max(maxIt[idx * 2], maxIt[idx * 2 + 1]);
}

int query(int idx, int l, int h, int u, int v) {
	if (u > h || v < l) return 0;
	if (u <= l && h <= v) return maxIt[idx];
	int mid = (l + h) / 2;
	int left = query(Left(idx), l, mid, u, v);
	int right = query(Right(idx), mid + 1, h, u, v);
	return max(left, right) + it[idx];
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, m;
	cin >> n >> m;
	fill_n(it, n * 8, 0);
	fill_n(maxIt, n * 8, 0);
	rep(i, m) {
		int t, u, v, k;
		cin >> t >> u >> v;
		if (t == 0) {
			cin >> k;
			update(1, 0, n, u, v, k);
		} else {
			cout << query(1, 0, n, u, v) << endl;
		}
	}

	return 0;
}