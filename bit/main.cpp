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

#define NMAX 1000

void update(VI &bit, int v, int val = 1) {
	for(auto i(v); i < NMAX; i+=i&(-i)) bit[i] += val;
}
int query(VI &bit, int v) {
	int sum(0);
	for(auto i(v); i; i-=i&(-i))sum += bit[i];
	return sum;
}

void point_update_range_query() {
	VI bit(NMAX, 0);
	update(bit, 5);
	update(bit, 6);
	update(bit, 10);
	update(bit, 13);
	For(i, 4, 15) cout << "query(" << i << "): " << query(bit, i) << endl;
}

void range_update_point_query() {
	VI bit(NMAX, 0);
	update(bit, 5, 2);
	update(bit, 7, -2);
	update(bit, 3, 3);
	update(bit, 5, -3);
	update(bit, 8, 2);
	update(bit, 11, -2);
	update(bit, 2, 5);
	update(bit, 15, -5);
	For(i, 1, 16) cout << "query(" << i << "): " << query(bit, i) << endl;
}

void update_range(VI &b1, VI &b2, int l, int h, int v) {
	update(b1, l, v); update(b1, h + 1, -v);
	update(b2, l, v * (l - 1)); update(b2, h + 1, -v * h);
}

int query(VI &b1, VI &b2, int x) {
	return query(b1, x) * x - query(b2, x);
}
int query(VI &b1, VI &b2, int l, int h) {
	return query(b1, b2, h) - (l ? query(b1, b2, l - 1) : 0);
}
void range_update_range_query() {
	VI b1(NMAX, 0), b2(NMAX, 0);
	update_range(b1, b2, 3, 5, 7);
	update_range(b1, b2, 4, 10, -3);
	update_range(b1, b2, 9, 20, 5);

	VI a;
	rep(i, 23) a.pb(query(b1, b2, i, i));
	rep(i, a.size()) cout << "a[" << i << "] = " << a[i] << endl;
	cout << "check" << endl;
	rep(i, 23) For(j, i, 23) {
		int sum(0);
		For(k, i, j + 1) sum+=a[k];
		if (sum != query(b1, b2, i, j)) cout << "failed range(" << i << "," << j << ")" << endl;
	}
	cout << "done" << endl;
}

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	cout << "point update range query" << endl;
	point_update_range_query();
	cout << "range update point query" << endl;
	range_update_point_query();
	cout << "range update range query" << endl;
	range_update_range_query();

	return 0;
}
