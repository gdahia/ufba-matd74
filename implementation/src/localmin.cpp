#include <cassert>
#include <localmin.hpp>

using namespace std;
using namespace mbst;

pair<int, int> LocalMinHeuristic::find_max_unexpanded_degree() {
  const int n = adj.size();

  int max_unexpanded = 0;
  int best = -1;
  for (int i = 0; i < n; i++)
    // only check frontier vertices
    if (color[i] == 1) {
      const auto &neigh_list = adj[i];

      // compute number of unexpanded neighbors
      int unexpanded_neighs = 0;
      for (const int neigh : neigh_list)
        if (color[neigh] == 0)
          unexpanded_neighs++;

      // update best
      if (unexpanded_neighs > max_unexpanded) {
        best = i;
        max_unexpanded = unexpanded_neighs;
      }
    }

  return {best, max_unexpanded};
}

int LocalMinHeuristic::find_highest_degree_vertex() {
  int max_deg = 0;
  int best = 0;
  for (int i = 0; i < n; i++)
    if ((int)adj[i].size() > max_deg) {
      max_deg = adj[i].size();
      best = i;
    }
  return best;
}

void LocalMinHeuristic::expand(const int v) {
  // only vertex which gets expanded without being on frontier is the first
  // vertex
  assert(color[v] == 1 || first);

  // color it with 2
  color[v] = 2;

  // expand v by adding edges to 0 colored neighbors to tree,
  // and coloring its neighbors with 1
  for (const int neigh : adj[v])
    if (color[neigh] == 0) {
      // color neighbor
      color[neigh] = 1;

      // add this edge to tree
      tree.emplace_back(v, neigh);

      // update degrees
      deg_in_tree[v]++;
      deg_in_tree[neigh]++;
    }

  // update branchings count
  if (deg_in_tree[v] > 2)
    branch_vertices++;

  // no longer first on subsequent expansions
  first = false;
}

int LocalMinHeuristic::find_single_neighbor_vertex() {
  for (int i = 0; i < n; i++)
    if (color[i] == 1) {
      // compute number of unexpanded neighbors
      int unexpanded_neighs = 0;
      for (const int neigh : adj[i])
        if (color[neigh] == 0)
          unexpanded_neighs++;

      if (unexpanded_neighs == 1)
        return i;
    }

  return -1;
}

LocalMinHeuristic::LocalMinHeuristic(const vector<vector<int>> &adj_list)
    : n(adj_list.size()), adj(adj_list) {
  // init resources
  branch_vertices = 0;
  color.resize(n, 0);
  deg_in_tree.resize(n, 0);

  // begin by expanding highest degree vertex
  first = true;
  vector<pair<int, int>> tree;
  vector<int> color(n, 0);
  const int root = find_highest_degree_vertex();
  expand(root);

  // continue expansion untill tree is spanning
  while ((int)tree.size() < n - 1) {
    const auto query = find_max_unexpanded_degree();
    const int max_unex_deg = query.second;
    int v = query.first;

    // check if better move is available by expanding 1 degree vertex
    if (max_unex_deg == 2) {
      const int cand = find_single_neighbor_vertex();
      if (cand > 0)
        v = cand;
    }

    expand(v);
  }
}

vector<pair<int, int>> LocalMinHeuristic::get_tree() const { return tree; }

int LocalMinHeuristic::get_num_branch_vertices() const {
  return branch_vertices;
}
