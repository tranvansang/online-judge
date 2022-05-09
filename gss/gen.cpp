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

#define VMAX 15000

int main() {
	srand(time(NULL));
	int n(50000);
	cout << n << endl;

	rep(i, n) {
		cout << rand() % VMAX * 2 - VMAX << " ";
	}
	cout << endl;

	int m = 50000;
//	cout << n * (n - 1) / 2 << endl;
	cout << m << endl;
	rep(i, m) {
		int x = rand() % n + 1;
		int y = rand() % (n - x + 1) + x;
		cout << x << " " << y << endl;
	}
//	rep(i, n) {
//		For(j, i, n) {
//			cout << i + 1 << " " << j + 1 << endl;
//		}
//	}
	return 0;
}