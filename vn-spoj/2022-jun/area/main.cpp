#include <bits/stdc++.h>
using namespace std;
#define VI vector<int>
#define eb emplace_back
#define all(a) (a).begin(), (a).end()
#define NMAX 30000
VI it(NMAX * 8, 0), val(NMAX * 8, 0);

void update(int idx, int low, int high, int left, int right, int v) {
	if (left >= high || right <= low) return;
	if (left <= low && high <= right) val[idx] += v;
	else {
		int m((low + high) / 2);
		update(idx * 2, low, m, left, right, v);
		update(idx * 2 + 1, m, high, left, right, v);
	}
	it[idx] = val[idx] ? high - low : it[idx * 2] + it[idx * 2 + 1];
}

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	int n; cin >> n;
	vector<tuple<int,int,int,int>> rect;
	while(n--) {
		int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		rect.eb(x1, -1, y1, y2); // open
		rect.eb(x2, 1, y1, y2); // close
	}
	sort(all(rect));
	int last_x(0), area(0);
	for(auto [x, v, y1, y2]: rect) {
		area += it[1] * (x - last_x);
		last_x = x;
		update(1, 0, NMAX, y1, y2, -v);
	}
	cout << area;
}