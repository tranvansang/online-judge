#include <stdio.h>
#include <vector>
using namespace std;

#define NMAX 11000
#define HMAX 15

vector<int> next_adj, start, adj, cost, tree_size, max_size_child, lhd, max_edge_to_lhd_root, parent_edge, begin_no, end_no, lhd_root, lhd_size;
int parent[NMAX + 1][HMAX];
int seg_tree[HMAX][NMAX + 1][HMAX];
vector<pair<pair<int, int>, pair<int, int> > >edge;
vector<bool> mark;
int root(1), n;

void add_edge(int a, int b, int c){
  adj.push_back(b);
  next_adj[adj.size() - 1] = start[a];
  start[a] = adj.size() - 1;
  cost[adj.size() - 1] = c;
}

int get_tree_size(int x, int cnt){
  cnt++;
  begin_no[x] = cnt;
  tree_size[x] = 1;
  mark[x] = true;
  max_size_child[x] = -1;
  for(int i = start[x]; i != -1; i = next_adj[i])
  if (!mark[adj[i]]){
    parent_edge[adj[i]] = i;
    parent[adj[i]][0] = x;
    cnt = get_tree_size(adj[i], cnt);
    tree_size[x] += tree_size[adj[i]];
    if (max_size_child[x] == -1 || tree_size[adj[i]] > tree_size[max_size_child[x]])
      max_size_child[x] = adj[i];
  }
  cnt++;
  end_no[x] = cnt;
  return cnt;
}

void get_lhd(int lhd_no, int x, int offset) {
  mark[x] = true;
  lhd[x] = lhd_no;
  lhd_size[lhd_no]++;
  for(int i = start[x]; i + 1; i = next_adj[i])
    if (!mark[adj[i]]) {
      if (adj[i] == max_size_child[x]){
        max_edge_to_lhd_root[adj[i]] = max(max_edge_to_lhd_root[x], cost[i]);
        get_lhd(root, adj[i], offset + 1);
      }
      else{
        lhd_root.push_back(adj[i]);
        lhd_size.push_back(0);
        max_edge_to_lhd_root[adj[i]] = 0;
        get_lhd(lhd_root.size() - 1, adj[i], 0);
      }
    }
}

void build_hld(){
  //build tree size
  tree_size = vector<int>(n + 1);
  begin_no = vector<int>(n + 1);
  end_no = vector<int>(n + 1);
  parent_edge = vector<int>(n + 1);
  max_size_child = vector<int>(n + 1);
  mark = vector<bool>(n + 1, false);
  get_tree_size(root, 0);

  //build lhd
  mark = vector<bool>(n + 1, false);
  lhd = vector<int>(n + 1);
  max_edge_to_lhd_root = vector<int>(n + 1, 0);
  lhd_root.push_back(root);
  get_lhd(lhd.size() - 1, root, 0);
}

void update_lhd(int x){
  for(int i = start[x]; i + 1; i = next_adj[i]) {
    if (adj[i] == max_size_child[x]) {
      max_edge_to_lhd_root[adj[i]] = max(max_edge_to_lhd_root[x], cost[i]);
      update_lhd(adj[i]);
      break;
    }
  }
}

bool is_ascentor(int ascentor, int descender) {
  return begin_no[ascentor] <= begin_no[descender] && end_no[descender] <= end_no[ascentor];
}

int find_max_edge(int root, int x){
  int max_edge = 0;
  while(!is_ascentor(lhd[x], root)) {
    max_edge = max(max_edge, max(max_edge_to_lhd_root[x], cost[parent_edge[lhd[x]]]));
    //printf("%d %d\n", parent_edge[lhd[x]], cost[parent_edge[lhd[x]]]);
    x = parent[lhd[x]][0];
  }
  while (x != root) {
    max_edge = max(max_edge, cost[parent_edge[x]]);
    x = parent[x][0];
  }
  return max_edge;
}

void build_lca(){
  parent[root][0] = root;
  for(int j = 1; j < HMAX; j++)
    for(int i = 1; i <= n; i++)
      parent[i][j] = parent[parent[i][j - 1]][j - 1];
}

int lca(int x, int y) {
  if (is_ascentor(x, y))
    return x;
  for (int i = HMAX - 1; i >= 0; i--){
    if (!is_ascentor(parent[x][i], y))
      x = parent[x][i];
  }
  return parent[x][0];
}

void solve(){
  scanf("%d", &n);
  next_adj = vector<int>((n - 1) * 2);
  start = vector<int>(n + 1, -1);
  cost = vector<int>((n - 1) * 2);
  edge = vector<pair<pair<int, int>, pair<int, int> > >(n);
  adj.clear();
  lhd_size.clear();
  lhd_size.reserve(HMAX);
  lhd_root.clear();
  lhd_root.reserve(HMAX);
  adj.reserve((n - 1) * 2);

  //enter
  for(int i = 1; i < n;i ++){
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
//set vertexes for edge
    edge[i].first.first = a;
    edge[i].first.second = b;
    add_edge(a, b, c);
    edge[i].second.first = adj.size() - 1;
    add_edge(b, a, c);
    edge[i].second.second = adj.size() - 1;
  }

  build_hld();
  build_lca();

  //query
  char s[10];
  s[0] = 0;
  while(s[0] != 'D'){
    scanf("%s", s);
    int x, y, k, c, edge1, edge2, lca_node;
    switch (s[0]) {
      case 'Q':
        //query
        scanf("%d%d", &x, &y);
        lca_node = lca(x, y);
        //printf("lca = %d\n", lca_node);
        printf("%d\n", max(find_max_edge(lca_node, x), find_max_edge(lca_node, y)));
        break;
      case 'C':
        //change
        scanf("%d%d", &k, &c);
        x = edge[k].first.first;
        y = edge[k].first.second;
        edge1 = edge[k].second.first;
        edge2 = edge[k].second.second;
        //printf("%d %d\n", edge1, edge2);
        cost[edge1] = c;
        cost[edge2] = c;
        if (lhd[x] == lhd[y]){
          if (is_ascentor(x, y)){
          update_lhd(x);
          } else
            update_lhd(y);
        }
        break;
    }
  }
}

int main(){
  int ntest;
  scanf("%d", &ntest);
  while(ntest--){
    solve();
  }
  return 0;
}
