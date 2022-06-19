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

	string haystack, needle;
	getline(cin, haystack); getline(cin, needle);
	VI kmp;
	kmp.pb(0);
	For(i, 1, needle.length()) {
		int j(kmp[i - 1]);
		while(j && needle[j] != needle[i]) j = kmp[j - 1];
		kmp.pb(j + (needle[j] == needle[i]));
	}

	int j = 0;
	rep(i, haystack.length()) {
		while(j && needle[j] != haystack[i]) j = kmp[j - 1];
		if (needle[j] == haystack[i]) j++;
		if (j == needle.length()) {
			cout << i - j + 2 << " ";
			j = kmp[j - 1];
		}
	}

	return 0;
}