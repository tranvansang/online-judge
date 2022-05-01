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

#define MAX_N 10000
#define MAX_VAL 30000

typedef struct {
	bool open;
	int x, y1, y2;
} Line;

int n;
vector<Line> lines;
int cnt[MAX_VAL * 4], cover[MAX_VAL * 4];

bool before(Line l1, Line l2) {
	return l1.x == l2.x ? l1.open > l2.open : l1.x < l2.x;
}

void update(int idx, int l, int r, int ul, int ur, int val) {
	if (ul >= r || ur <= l) return;
	if (ul <= l && r <= ur) {
		cnt[idx] += val;
	} else {
		int mid = (l + r) / 2;
		update(idx * 2, l, mid, ul, ur, val);
		update(idx * 2 + 1, mid, r, ul, ur, val);
	}
	cover[idx] = cnt[idx] ? r - l : cover[idx * 2] + cover[idx * 2 + 1];
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int maxVal(0);
	cin >> n;
	rep(i, n) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		maxVal = max(maxVal, y2);

		lines.pb(Line({true, x1, y1, y2}));
		lines.pb(Line({false, x2, y1, y2}));
	}
	sort(all(lines), before);

	if (n == 0) cout << 0;
	else {
		int lastX = lines[0].x;
		int area = 0;
		fill_n(cnt, MAX_VAL * 4, 0);
		fill_n(cover, MAX_VAL * 4, 0);
		trav(it, lines) {
			auto line = *it;
			area += (line.x - lastX) * cover[1];
			update(1, 0, maxVal, line.y1, line.y2, line.open ? 1 : -1);
			lastX = line.x;
		}
		cout << area;
	}

	return 0;
}