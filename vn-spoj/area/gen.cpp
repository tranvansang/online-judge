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

#define MAX_N 10000
#define MAX_VAL 30000
//#define MAX_N 100
//#define MAX_VAL 1000

void doSort(int& x, int& y) {
	if (x > y) {
		int t = y;
		y = x;
		x = t;
	}
}
int main() {
	srand(time(NULL));
	int n = 5;
	cout << n << endl;
	rep(i, n) {
		int x1 = rand() % MAX_VAL;
		int x2 = rand() % MAX_VAL;
		int y1 = rand() % MAX_VAL;
		int y2 = rand() % MAX_VAL;
		doSort(x1, x2);
		doSort(y1, y2);
		cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
	}
	return 0;
}