#include <iostream>
#include <stack>
#include <cstdio>
using namespace std;

int *head, *head1, *v, *v1, *nxt, *next1;
int *com, ncom;
bool *mark;
int n;

void add(int *head, int *v, int *nxt, int k, int x, int y){
	nxt[k] = head[x];
	head[x] = k;
	v[k] = y;
}

void enter(){
	int m;
	cin >> n >> m;
	head = new int[n + 10];
	head1 = new int[n + 10];
	v = new int[m + 10];
	v1 = new int[m + 10];
	nxt = new int [m + 10];
	next1 = new int [m + 10];
	com = new int [n + 10];
	mark = new bool [n + 10];
	fill_n(head, n + 1, 0);
	fill_n(head1, n + 1, 0);
	for(int i = 1; i <= m; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		add(head, v, nxt, i, x, y);
		add(head1, v1, next1, i, y, x);
	}
}

stack<int> st;

void dfs(int x){
	mark[x] = true;
	for(int i = head[x]; i; i = nxt[i])
		if (!mark[v[i]]) dfs(v[i]);
	st.push(x);
}

void dfs1(int x){
	mark[x] = false;
	com[x] = ncom;
	for(int i = head1[x]; i; i = next1[i])
		if (mark[v1[i]]) dfs1(v1[i]);
}
void find_com(){
	fill_n(mark, n + 1, false);
	for(int i = 1; i <= n; i++)
		if (!mark[i]) dfs(i);
	ncom = 0;
	while (!st.empty()){
		int t = st.top();
		st.pop();
		if (mark[t]){
			ncom++;
			dfs1(t);
		};
	}
}

void solve(){
	find_com();
//	int cnt = 0;
//	for(int i = 1; i <= n; i++)
//		for(int j = head[i]; j; j = nxt[j])
//			if (com[i] != com[v[j]]) mark[com[v[j]]] = true;
//	for(int i = 1; i <= ncom; i++)
//		if (!mark[i]) cnt++;
//	cout << cnt;
	cout << ncom;

	//finish
	delete[] mark;
	delete[] head;
	delete[] head1;
	delete[] v;
	delete[] v1;
	delete[] nxt;
	delete[] next1;
	delete[] com;
}

int main(){
	enter();
	solve();
}
