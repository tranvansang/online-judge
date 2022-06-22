#include <bits/stdc++.h>
using namespace std;
#define V vector
#define For(i,a,b) for(auto (i) = (a); (i) < (b); (i)++)
#define rep(i,n) For(i,0,(n))
#define mt make_tuple
#define eb emplace_back
#define all(a) (a).begin(), (a).end()
#define ll long long

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	V<int> a = {0, 0, 2, 2, 2, 3, 4, 5, 5, 6};
	cout << lower_bound(all(a), 2) - a.begin() << endl;
	cout << upper_bound(all(a), 2) - a.begin() << endl;
	cout << lower_bound(all(a), 1) - a.begin() << endl;
	cout << upper_bound(all(a), 1) - a.begin() << endl;

	sort(all(a), greater<int>());
	cout << lower_bound(all(a), 5, greater<int>()) - a.begin() << endl;
	cout << upper_bound(all(a), 5, greater<int>()) - a.begin() << endl;

	cout << lower_bound(all(a), -1, greater<int>()) - a.begin() << endl;
	cout << upper_bound(all(a), -1, greater<int>()) - a.begin() << endl;
	cout << lower_bound(all(a), 7, greater<int>()) - a.begin() << endl;
	cout << upper_bound(all(a), 7, greater<int>()) - a.begin() << endl;

	cout << "print array" << endl;
	for(auto it: a) cout << it << " ";
	cout << endl;
	sort(all(a), [](auto &x, auto &y) {
		auto x_is_odd = x % 2;
		auto y_is_odd = y % 2;
		if (x_is_odd != y_is_odd) return x_is_odd < y_is_odd;
		return x < y;
	});
	cout << "print array" << endl;
	for(auto it: a) cout << it << " ";
	cout << endl;

	shuffle(all(a), default_random_engine());
	cout << "print array" << endl;
	for(auto it: a) cout << it << " ";
	cout << endl;
	V<tuple<int,int>> b = {};
	rep(i, a.size()) b.eb(i, a[i]);
	sort(all(b), [&](auto &x, auto &y) {
		auto &[ix, vx] = x;
		auto &[iy, vy] = y;
		return a[ix] < a[iy];
	});
	cout << "print array after sort b" << endl;
	for(auto &[i, v]: b) cout << i << " " << v << " ";
	cout << endl;

	cout << "print array after sort b (value only)" << endl;
	for(auto &[i, v]: b) cout << v << " ";
	cout << endl;

	string s = "xin chao";
	cout << s.length() << endl;

	return 0;
}
