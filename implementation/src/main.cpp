#include <cassert>
#include <iostream>
#include <vector>

#include <localmin.hpp>

bool dfs(const int v, std::vector<bool> &vis,
         std::vector<std::vector<int>> &adj) {
  vis[v] = true;
  int vis_count = 0;
  for (const int u : adj[v])
    if (vis[u])
      vis_count++;
    else if (!dfs(u, vis, adj))
      return false;
  return true;
}

int main() {
  // read graph main info
  int n, m;
  std::cout << "Enter number of vertices: ";
  std::cin >> n;

  std::cout << "Enter number of edges: ";
  std::cin >> m;

  // read edges
  std::vector<std::vector<int>> adj(n);
  std::cout
      << "Enter edges in format \"u v\" (no quotes, 0 indexed, one per line):"
      << std::endl;
  while (m--) {
    int u, v;
    std::cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  // run localmin on instance
  auto l = mbst::LocalMinHeuristic(adj);

  // assert result is indeed tree
  const auto &tree = l.get_tree();
  adj.clear();
  adj.resize(n);
  for (const auto e : tree) {
    adj[e.first].push_back(e.second);
    adj[e.second].push_back(e.first);
  }
  std::vector<bool> vis(n, false);
  assert(dfs(0, vis, adj));

  // print tree
  std::cout << std::endl << "Output tree:" << std::endl;
  for (const auto e : l.get_tree())
    std::cout << e.first << " " << e.second << std::endl;

  // print number of branch vertices
  std::cout << std::endl
            << "Number of branch vertices: " << l.get_num_branch_vertices()
            << std::endl;
}
