#include <stdio.h>
#include <algorithm>

#define N 11000
#define H 15

int adj[N << 1], gstart[N], gnext[N << 1], costs[N];
int par[N][H], depth[N], low_end[N], subt_size[N];
int lhd_root[N], schild_ind[N], lhd_cnt, lhd_no[N];
int segt_size, segt[N * 6], seg_val[N], segt_ind[N];
int n;

void dfs(int cur, int d){
  subt_size[cur] = 1;
  depth[cur] = d;
  schild_ind[cur] = -1;
  for(int i = gstart[cur]; i + 1; i = gnext[i])
    if (low_end[i >> 1] == -1) {
      int child = adj[i];
      low_end[i >> 1] = child;
      par[child][0] = cur;
      dfs(child, d + 1);
      subt_size[cur] += subt_size[child];
      if (schild_ind[cur] == -1 || subt_size[child] > subt_size[adj[schild_ind[cur]]]) schild_ind[cur] = i;
    }
}

int lca(int u, int v){
  if (depth[u] < depth[v]) std::swap(u, v);
  int diff = depth[u] - depth[v];
  for(int i = 0; i < H; i++) if ((diff >> i) & 1) u = par[u][i];
  if (u == v) return u;
  for(int i = H - 1; i >= 0; i--)
    if (par[u][i] != par[v][i]){
      u = par[u][i]; v = par[v][i];
    }
  return par[u][0];
}

void lhd(int cur, int c){
  if (lhd_root[lhd_cnt] == -1) lhd_root[lhd_cnt] = cur;
  segt_ind[cur] = segt_size;
  seg_val[segt_size++] = c;
  lhd_no[cur] = lhd_cnt;
  if (schild_ind[cur] + 1){
    int child = adj[schild_ind[cur]];
    lhd(child, costs[schild_ind[cur] >> 1]);
  }
  for(int i = gstart[cur]; i + 1; i = gnext[i])
    if (schild_ind[cur] != i && low_end[i >> 1] != cur) {
      lhd_cnt++;
      lhd(adj[i], costs[i >> 1]);
    }
}

int make_segt(int ind, int l, int h){
  if (h == l + 1) return segt[ind] = seg_val[l];
  if (l >= h) return 0;
  int m = (l + h) >> 1;
  return segt[ind] = std::max(make_segt(ind << 1, l, m), make_segt((ind << 1) | 1, m, h));
}

int query_segt(int ind, int l, int h, int ql, int qh){
  if (l >= h) return 0;
  if (qh <= l || ql >= h) return 0;
  if (ql <= l && h <= qh) return segt[ind];
  int m = (l + h) >> 1;
  return std::max(query_segt(ind << 1, l, m, ql, qh), query_segt((ind << 1) | 1, m, h, ql, qh));
}

int upd_segt(int ind, int l, int h, int i, int v){
  if (l >= h) return 0;
  if (i < l || i >= h) return segt[ind];
  if (l + 1 == h) return segt[ind] = v;
  int m = (l + h) >> 1;
  return segt[ind] = std::max(upd_segt(ind << 1, l, m, i, v), upd_segt((ind << 1) | 1, m, h, i, v));
}

int query_up(int as, int ds){
  int ret(0);
  while (lhd_no[as] != lhd_no[ds]){
    int root = lhd_root[lhd_no[ds]];
    ret = std::max(ret, query_segt(1, 0, segt_size, segt_ind[root], segt_ind[ds] + 1));
    ds = par[root][0];
  }
  return std::max(ret, query_segt(1, 0, segt_size, segt_ind[as] + 1, segt_ind[ds] + 1));
}

int main(){
//  freopen("/home/tansei/online-judge/qtree/input", "r", stdin);
  int ntest;
  scanf("%d", &ntest);
  while(ntest--){
    //init
    segt_size = 0;
    lhd_cnt = 0;

    //enter
    scanf("%d", &n);
    std::fill(lhd_root, lhd_root + n, -1);
    std::fill(gstart, gstart + n, -1);
    std::fill(low_end, low_end + n, -1);
    for(int i = 0; i < n - 1; i++){
      int u, v, cost;
      scanf("%d%d%d", &u, &v, &cost);
      u--; v--;

      gnext[i << 1] = gstart[u];
      adj[i << 1] = v;
      gstart[u] = i << 1;

      gnext[(i << 1) | 1] = gstart[v];
      gstart[v] = (i << 1) | 1;
      adj[(i << 1) | 1] = u;

      costs[i] = cost;
    }
    par[0][0] = 1;
    dfs(0, 0);
    lhd(0, 0);
    make_segt(1, 0, segt_size);

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
          upd_segt(1, 0, segt_size, segt_ind[low_end[k - 1]], c);
          break;
      }
    } while (str[0] != 'D');
  }
  return 0;
}
