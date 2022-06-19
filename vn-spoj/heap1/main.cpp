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

#define NMAX 20000

int top, heap[NMAX + 1];

void push(int a) {
	top++;
	heap[top] = a;
	for(int i = top; i / 2 > 0; i /= 2) {
		int p = i / 2;
		if (heap[p] <= heap[i]) break;
		int t = heap[p]; heap[p] = heap[i]; heap[i] = t;
	}
}

int pop() {
	int val = heap[1];
	heap[1] = heap[top]; top--;
	for(int i = 1; i * 2 <= top; ) {
		int c = i * 2;
		if (c < top && heap[c + 1] < heap[c]) c++;
		if (heap[i] <= heap[c]) break;
		int t = heap[i]; heap[i] = heap[c]; heap[c] = t;
		i = c;
	}
	return val;
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int ntest; cin >> ntest;
	rep(_, ntest) {
		top = 0;
		int n; cin >> n;
		rep(i, n) {
			int a; cin >> a; push(a);
		}
		ll sum(0);
		rep(i, n - 1) {
			int t = pop() + pop();
			sum += t;
			push(t);
		}
		cout << sum << endl;
	}

	return 0;
}