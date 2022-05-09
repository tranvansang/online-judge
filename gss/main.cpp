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

#define Left(idx) ((idx) << 1)
#define Right(idx) (((idx) << 1) + 1)
#define Mid(l, h) (((l) + (h)) / 2)

#define NMAX 50000
#define VMAX 15000

int maxVal = VMAX * NMAX;

int a[NMAX + 1], s[NMAX + 1];
int maxIt[NMAX * 8], minIt[NMAX * 8], allIt[NMAX * 8];
#define getMin get<0>
#define getMax get<1>
#define getAll get<2>

void build(int idx, int l, int h) {
	if (l > h) return;
	if (l == h) {
		maxIt[idx] = minIt[idx] = s[h];
		allIt[idx] = -maxVal;
		return;
	}
	build(Left(idx), l, Mid(l, h));
	build(Right(idx), Mid(l, h) + 1, h);
	maxIt[idx] = max(maxIt[Left(idx)], maxIt[Right(idx)]);
	minIt[idx] = min(minIt[Left(idx)], minIt[Right(idx)]);
	allIt[idx] = max(max(allIt[Left(idx)], allIt[Right(idx)]), maxIt[Right(idx)] - minIt[Left(idx)]);
}

tuple<int, int, int> query(int idx, int l, int h, int x, int y) {
	if (x > h || y < l) return make_tuple(maxVal, -maxVal, -maxVal);
	if (x <= l && h <= y) return make_tuple(minIt[idx], maxIt[idx], allIt[idx]);
	auto left = query(Left(idx), l, Mid(l, h), x, y);
	auto right = query(Right(idx), Mid(l, h) + 1, h, x, y);
	return make_tuple(
		min(getMin(left), getMin(right)),
		max(getMax(left), getMax(right)),
		max(
			max(getAll(left), getAll(right)),
			Mid(l, h) >= x && Mid(l, h) + 1 <= y ? getMax(right) - getMin(left) : -maxVal
		)
	);
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, m;
	cin >> n;
	s[0] = 0;
	rep(i, n) {
		int x;cin >> x;a[i] = x;
		s[i + 1] = s[i] + x;
	}
	build(1, 0, n);
	cin >> m;
	rep(i, m) {
		int x, y; cin >> x >> y;
		x--; y--;
		cout << getAll(query(1, 0, n, x, y + 1)) << endl;
	}

	return 0;
}