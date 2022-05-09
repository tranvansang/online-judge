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
	int n(100);
	cout << n << endl;

	int a[101];
	rep(i, n) {
		a[i] = rand() % VMAX * 2 - VMAX;
		cout << a[i] << " ";
	}
	cout << endl;

	cout << n * (n - 1) / 2 << endl;
	rep(i, n) {
		For(j, i, n) {
			cout << i + 1 << " " << j + 1 << endl;
		}
	}
	return 0;
}