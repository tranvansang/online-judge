#include <bits/stdc++.h>
using namespace std;
#define II pair<int,int>
#define VI vector<int>
#define VVI vector<VI>
#define VII vector<II>
#define VVII vector<VII>
#define For(i,a,b) for(auto i = (a); i < (b); i++)
#define rep(i,n) For(i,0,(n))
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define ll long long

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n; cin >> n;
	VI bit(60001, 0);
	ll total(0);
	rep(i,n) {
		int x; cin >> x;
		total+=i;
		for(int j=x; j; j-=j&-j) total-= bit[j];
		for(int j=x; j<=60000; j+=j&-j) bit[j]++;
	}
	cout << total;

	return 0;
}