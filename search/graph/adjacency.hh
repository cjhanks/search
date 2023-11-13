#ifndef SEARCH_GRAPH_ADJACENCY_HH_
#define SEARCH_GRAPH_ADJACENCY_HH_

#include "search/matrix/sparse_map.hh"

namespace search {

template <typename NodeType_, typename EdgeType_>
class SparseAdjacencyGraph {
 public:
  using NodeType = NodeType_;
  using EdgeType = EdgeType_;

  explit SparseAdjacencyGraph(std::size_t node_count)
    : edges(node_count, node_count)
  {}

  explit SparseAdjacencyGraph(const std::vector<NodeType>& nodes)
    : edges(nodes.size(), nodes.size())
  {
    for (const auto& node: nodes)
      AddNode(node);
  }

  explit SparseAdjacencyGraph(std::vector<NodeType>&& nodes)
    : edges(nodes.size(), nodes.size())
  {
    for (const auto& node: nodes)
      AddNode(node);

    nodes.clear();
  }

  void
  AddNode(const NodeType& node) {
    if (addresses.find(node) == addresses.end())
      addresses[node] = addresses.size();
  }

  void
  AddNode(NodeType&& node) {
    if (addresses.find(node) == addresses.end())
      addresses[std::move(node)] = addresses.size();
  }

  void
  AddEdge(const NodeType& a, const NodeType& b, EdgeType edge) {
    assert(addresses.find(a) != addresses.end());
    assert(addresses.find(b) != addresses.end());
    edges.At(addresses[a], addresses[b]) = edge;
  }

 private:
  std::unordered_map<NodeType, std::size_t> addresses;
  SparseMapMatrix<EdgeType> edges;
};
} // ns search

#endif // SEARCH_GRAPH_ADJACENCY_HH_
