#include <cstdio>
#include <algorithm>
#include <iostream>
#define N 10000
#define H 15
int adj[N << 1], cost[N], gnext[N << 1], gstart[N];
int par[N][H], depth[N];
long long pcost[N][H];
int n;

void dfs(int cur, int c, int d, int p){
  depth[cur] = d;
  pcost[cur][0] = c;
  par[cur][0] = p;
  for(int i = gstart[cur]; i + 1; i = gnext[i]){
    int child = adj[i];
    if (p != child) dfs(child, cost[i >> 1], d + 1, cur);
  }
}

long long dist(int u, int v){
  if (depth[u] < depth[v]) std::swap(u, v);
  long long d(0);
  int diff = depth[u] - depth[v];
  for(int i = 0; i < H; i++)
    if (diff >> i & 1){
      d += pcost[u][i];
      u = par[u][i];
    }
  if (u == v) return d;
  for(int i = H - 1; i>=0;i --)
    if (par[u][i] != par[v][i]){
      d += pcost[u][i] + pcost[v][i];
      u = par[u][i]; v = par[v][i];
    }
  return d + pcost[u][0] + pcost[v][0];
}

int find_lca(int u, int v){
  if (depth[u] < depth[v]) std::swap(u, v);
  int diff = depth[u] - depth[v];
  for(int i = 0; i < H; i++)
    if (diff >> i & 1) u = par[u][i];
  if (u == v) return u;
  for(int i = H - 1; i >= 0; i--)
    if (par[u][i] != par[v][i]) {
      u = par[u][i]; v = par[v][i];
    }
  return par[u][0];
}

int kth(int u, int d){
  for(int i = 0; i < H; i++)
    if (d >> i & 1) u = par[u][i];
  return u + 1;
}

int main(){
//  freopen("/home/tansei/online-judge/qtree2/input", "r", stdin);
  int ntest;
  scanf("%d", &ntest);
  while(ntest--){
    //enter
    scanf("%d", &n);
    std::fill(gstart, gstart + n, -1);
    for(int i = 0; i < n - 1;i ++){
      int u, v, c;
      scanf("%d%d%d", &u, &v, &c); u--; v--;
      gnext[i << 1] = gstart[u];
      gstart[u] = i << 1;
      adj[i << 1] = v;
      gnext[i << 1 | 1] = gstart[v];
      gstart[v] = i << 1 | 1;
      adj[i << 1 | 1] = u;
      cost[i] = c;
    }

    //lca
    dfs(0, 0, 0, 0);
    for(int i = 1; i < H; i++)
      for(int j = 0; j < n; j++){
        par[j][i] = par[par[j][i - 1]][i - 1];
        pcost[j][i] = pcost[j][i - 1] + pcost[par[j][i - 1]][i - 1];
      }

    //query
    char str[10];
    int u, v, k;
    do {
      scanf("%s", str);
      if (str[0] == 'D' && str[1] == 'I'){
        scanf("%d%d", &u, &v); u--; v--;
        std::cout << dist(u, v)<< std::endl;
      } else if (str[0] == 'K'){
        scanf("%d%d%d", &u, &v, &k); u--; v--; k--;
        int lca = find_lca(u, v);
        if (depth[u] - depth[lca] >= k) printf("%d\n", kth(u, k));
        else printf("%d\n", kth(v, depth[v] - depth[lca] * 2 - k + depth[u]));
      }
    } while (str[0] != 'D' || str[1] != 'O');
  }
}
