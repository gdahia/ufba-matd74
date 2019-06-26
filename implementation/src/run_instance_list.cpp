#include <cassert>
#include <fstream>
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

int main(const int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage " << argv[0] << " path_to_instance_list" << std::endl;
    return 1;
  }

  // open instance list file
  std::ifstream instance_list(argv[1]);
  if (!instance_list.is_open()) {
    std::cerr << "Unable to open instance list in path " << argv[1]
              << std::endl;
    return 1;
  }

  std::string instance_path;
  while (instance_list >> instance_path) {
    // open instance file
    std::ifstream instance(instance_path);
    if (!instance.is_open()) {
      std::cerr << "Unable to open instance in path " << instance_path
                << std::endl;
      return 1;
    }

    // read graph main info
    int n, m, ignore;
    instance >> n >> m >> ignore;

    // read edges
    std::vector<std::vector<int>> adj(n);
    while (m--) {
      int u, v;
      instance >> u >> v >> ignore;
      u--, v--;
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

    // print "instance_path number_of_branchings"
    std::cout << instance_path << " " << l.get_num_branch_vertices()
              << std::endl;
  }
}
