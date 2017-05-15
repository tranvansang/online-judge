#include <stdio.h>
#include <algorithm>

#define N 11000
#define H 15

int adj[N], gstart[N], gnext[N << 1], costs[N];
int par[N][H], depth[N], low_end[N], subt_size[N];
int lhd_root[H], schild_ind[N], lhd_cnt, lhd_no[N];
int segt_size, segt[N * 5], seg_val[N], segt_ind[N];
int n;

void dfs(int cur, int prev, int d){
  subt_size[cur] = 1;
  depth[cur] = d;
  schild_ind[cur] = -1;
  for(int i = gstart[cur]; i + 1; i = gnext[i]){
    int child = adj[i];
    if (child != prev){
      low_end[i >> 1] = child;
      par[child][0] = cur;
      dfs(child, cur, d + 1);
      subt_size[cur] += subt_size[child];
      if (schild_ind[cur] == -1 || subt_size[child] > subt_size[adj[schild_ind[cur]]])
        schild_ind[cur] = i;
    }
  }
}

int lca(int u, int v){
  if (depth[u] < depth[v]) std::swap(u, v);
  int diff = depth[u] - depth[v];
  for(int i = 0; i < H; i++)
    if ((diff >> i) & 1) u = par[u][i];
  if (u == v) return u;
  for(int i = H - 1; i >= 0; i--)
    if (par[u][i] != par[v][i]){
      u = par[u][i];
      v = par[v][i];
    }
  return par[u][0];
}

void lhd(int cur){
  if (lhd_root[lhd_cnt] == -1)
    lhd_root[lhd_cnt] = cur;
  if (schild_ind[cur] + 1){
    segt_ind[cur] = segt_size;
    seg_val[segt_size++] = costs[schild_ind[cur] >> 1];
    lhd_no[adj[schild_ind[cur]]] = lhd_cnt;
    lhd(adj[schild_ind[cur]]);
  }
  for(int i = gstart[cur]; i + 1; i = gnext[i])
    if (schild_ind[cur] != i) {
      int child = adj[i];
      if (child != par[cur][0]) {
        lhd_cnt++;
        segt_ind[child] = segt_size;
        seg_val[segt_size++] = costs[i >> 1];
        lhd_no[child] = lhd_cnt;
        lhd(child);
      }
    }
}

int make_segt(int ind, int l, int h){
  if (l == h) return segt[ind] = seg_val[l];
  if (l > h) return 0;
  int m = (l + h) >> 1;
  return segt[ind] = std::max(make_segt(ind << 1, l, m), make_segt((ind << 1) & 1, m + 1, h));
}

int query_segt(int ind, int l, int h, int ql, int qh){
  if (qh < l || ql > h) return 0;
  if (ql <= l && h <= qh) return segt[ind];
  int m = (l + h) >> 1;
  return std::max(query_segt(ind << 1, l, m, ql, qh), query_segt((ind << 1) & 1, m + 1, h, ql, qh));
}

int upd_segt(int ind, int l, int h, int i, int v){
  if (l > h) return 0;
  if (i < l || i > h) return segt[ind];
  if (l == h) return segt[ind] = v;
  int m = (l + h) >> 1;
  return segt[ind] = std::max(upd_segt(ind << 1, l, m, i, v), upd_segt((ind << 1) & 1, m + 1, h, i, v));
}

int query_up(int as, int ds){
  int ret(0);
  while (lhd_no[as] == lhd_no[ds]){
    int root = lhd_root[lhd_no[ds]];
    ret = std::max(ret, query_segt(0, 0, segt_size - 1, segt_ind[root], segt_ind[ds]));
    ds = par[root][0];
  }
  return std::max(ret, query_segt(0, 0, segt_size - 1, segt_ind[as] + 1, segt_ind[ds]));
}

int main(){
  int ntest;
  scanf("%d", &ntest);
  while(ntest--){
    //init
    segt_size = 0;
    lhd_cnt = 0;
    lhd_no[0] = 0;
    std::fill(lhd_root, lhd_root + H, -1);

    //enter
    scanf("%d", &n);
    std::fill(gstart, gstart + n, -1);
    for(int i = 0; i < n - 1; i++){
      int u, v, cost;
      scanf("%d%d%d", &u, &v, &cost);
      u--; v--;
      gnext[i << 1] = gstart[u];
      gstart[u] = i << 1;
      gnext[(i << 1) | 1] = gstart[v];
      gstart[v] = (i << 1) | 1;
      costs[i] = cost;
    }
    par[0][0] = 1;
    dfs(0, 0, 0);
    lhd(0);
    make_segt(1, 0, segt_size - 1);

    //lca
    for(int i = 1; i < H; i++)
      for(int j = 1; j < n; j++)
        par[j][i] = par[par[j][i - 1]][i - 1];

    //query
    char str[10];
    int u, v, k, c, lca_node;
    do {
      scanf("%s", str);
      switch(str[0]) {
        case 'Q':
          scanf("%d%d", &u, &v);u--;v--;
          lca_node = lca(u, v);
          printf("%d\n", std::max(query_up(lca_node, u), query_up(lca_node, v)));
          break;
        case 'C':
          scanf("%d%d", &k, &c);
          upd_segt(0, 0, segt_size - 1, low_end[k - 1], c);
          break;
      }
    } while (str[0] != 'D');
  }
}
