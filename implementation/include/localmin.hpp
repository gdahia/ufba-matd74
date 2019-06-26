#ifndef LOCALMIN_HPP
#define LOCALMIN_HPP

#include <utility>
#include <vector>

namespace mbst {

class LocalMinHeuristic {
public:
  LocalMinHeuristic(const std::vector<std::vector<int>> &adj_list);
  ~LocalMinHeuristic() = default;

  std::vector<std::pair<int, int>> get_tree() const;
  int get_num_branch_vertices() const;

private:
  bool first;
  const int n;
  int branch_vertices;
  const std::vector<std::vector<int>> adj;
  std::vector<std::pair<int, int>> tree;
  std::vector<int> color;
  std::vector<int> deg_in_tree;

  std::pair<int, int> find_max_unexpanded_degree();
  int find_highest_degree_vertex();
  void expand(const int v);
  int find_single_neighbor_vertex();
};

} // namespace mbst

#endif
