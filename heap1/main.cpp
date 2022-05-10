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

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int ntest; cin >> ntest;
	rep(t, ntest) {
		int n; cin >> n;
		priority_queue<int, VI, greater<int>> q;
		rep(i, n) {
			int a; cin >> a;
			q.push(a);
		}
		ll sum(0);
		rep(i, n - 1) {
			int t1 = q.top(); q.pop();
			int t2 = q.top(); q.pop();
			sum += t1 + t2;
			q.push(t1 + t2);
		}
		cout << sum << endl;
	}

	return 0;
}