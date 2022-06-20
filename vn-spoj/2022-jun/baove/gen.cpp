#include <bits/stdc++.h>
using namespace std;
#define V vector
#define For(i,a,b) for(auto (i) = (a); (i) < (b); (i)++)
#define rep(i,n) For(i,0,(n))
#define mt make_tuple
#define eb emplace_back
#define all(a) (a).begin(), (a).end()
#define ll long long

int main() {
	srand(time(nullptr));
	int n(10);
	cout << n << endl;
	int m(10000);
	int vmax(10);
	while(m--) {
		int x = rand() % n + 1;
		int y = rand() % n + 1;
		int c = rand() % vmax;
		cout << x << " " << y << " " << c << endl;
	}
	return 0;
}
