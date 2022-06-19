#include <iostream>

using namespace std;
#define For(i, a, b) for(auto i = (a); i < (b); i++)
#define rep(i, n) For(i,0,(n))

#define MAXV 100000

int cnt[MAXV + 1];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	fill_n(cnt, MAXV + 1, 0);
	int n, m;
	cin >> n >> m;
	int maxv(0), minv(MAXV);
	rep(i, m) {
		int x;
		cin >> x;
		maxv = max(maxv, x);
		minv = min(minv, x);
		cnt[x]++;
	}
	int best(-1), bestIncome, sum(0);
	for (int i = maxv; i >= minv; i--) {
		sum += cnt[i];
		if (best == -1 || bestIncome < min(n, sum) * i) {
			best = i;
			bestIncome = min(n, sum) * i;
		}
		if (sum >= n) break;
	}
	cout << best << " " << bestIncome;

	return 0;
}