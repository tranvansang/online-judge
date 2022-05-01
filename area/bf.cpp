#include <bits/stdc++.h>
#define ii pair<int, int>
#define iiii pair<pair<int, int> , pair<int, int> >
#define X first
#define Y second
const int xxx = 33333;
const int Open = 1;
const int Close = -1;
using namespace std;
vector<iiii> event;
ii it[8*xxx];
int n, res;

void Enter() {
	//freopen("AREA.inp", "r", stdin);
	scanf("%d\n", &n);
	int i, x1, y2, x2, y1;
	for(i=1; i<=n; i++) {
		scanf("%d %d %d %d\n", &x1, &y1, &x2, &y2);
		event.push_back(iiii(ii(x1, Open), ii(y1, y2)));
		event.push_back(iiii(ii(x2, Close), ii(y1, y2)));
	}
	sort(event.begin(), event.end());
}

void Upd(int k, int l, int r, int i, int j, int v) {
	if (r<=i || j<=l) return;
	if (i<=l && r<=j )
		it[k].X += v;
	else {
		int m = (l+r) >> 1;
		Upd(k << 1, l, m, i, j, v);
		Upd((k << 1) | 1, m, r, i, j, v);
	}
	if (it[k].X == 0)
		it[k].Y = it[k << 1].Y + it[(k << 1) | 1].Y;
	else it[k].Y = r - l;
}

void SweepLine() {
	int i, y1, y2, type, len, d;
	for(i=0; i<(event.size()-1); i++) {
		y1 = event[i].Y.X; y2 = event[i].Y.Y;
		type = event[i].X.Y;
		Upd(1, 0, xxx, y1, y2, type);
		len = event[i+1].X.X - event[i].X.X;
		d = it[1].Y;
		res += len * d;
	}
}

int main()
{
	Enter();
	SweepLine();
	printf("%d", res);
	return 0;
}

//#include <bits/stdc++.h>
//using namespace std;
//#define PII pair<int,int>
//#define VI vector<int>
//#define For(i,a,b) for(auto i = (a); i < (b); i++)
//#define rep(i,n) For(i,0,(n))
//#define fi first
//#define se second
//#define mp make_pair
//#define pb push_back
//#define all(a) (a).begin(), (a).end()
//#define trav(it,x) for(auto it = (x).begin(); it != (x).end(); it++)
//#define ll long long
//
//#define MAX_N 10000
//#define MAX_VAL 30000
//
//typedef struct {
//	int x1, y1, x2, y2;
//} Rect;
//
//int n;
//vector<Rect> rects;
//
//int main(){
//	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
//
//	int maxY(0), maxX(0);
//	cin >> n;
//	rep(i, n) {
//		int x1, y1, x2, y2;
//		cin >> x1 >> y1 >> x2 >> y2;
//		maxY = max(maxY, y2);
//		maxX = max(maxX, x2);
//
//		rects.pb(Rect({x1, y1, x2, y2}));
//	}
//
//	int area(0);
//	rep(x, maxX) {
//		rep(y, maxY) {
//			trav(it, rects) {
//				auto rect = *it;
//				if (rect.x1 <= x && x < rect.x2 && rect.y1 <= y && y < rect.y2) {
//					area++;
//					break;
//				}
//			}
//		}
//	}
//	cout << area;
//
//	return 0;
//}