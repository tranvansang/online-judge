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
	int x1, y1, x2, y2;
} Rect;

int n;
vector<Rect> rects;

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int maxY(0), maxX(0);
	cin >> n;
	rep(i, n) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		maxY = max(maxY, y2);
		maxX = max(maxX, x2);

		rects.pb(Rect({x1, y1, x2, y2}));
	}

	int area(0);
	rep(x, maxX) {
		rep(y, maxY) {
			trav(it, rects) {
				auto rect = *it;
				if (rect.x1 <= x && x < rect.x2 && rect.y1 <= y && y < rect.y2) {
					area++;
					break;
				}
			}
		}
	}
	cout << area;

	return 0;
}