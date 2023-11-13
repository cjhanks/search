#ifndef SEARCH_GRAPH_BUILDER_HH_
#define SEARCH_GRAPH_BUILDER_HH_

#include <unordered_map>
#include <vector>


template <typename NodeType_, typename EdgeType_>
class NeighborGraph {
 public:
  using NodeType = NodeType_;
  using EdgeType = EdgeType_;

 private:
  struct Edge {
    NodeType node;
    EdgeType cost;
  };

  using EdgeList = std::vector<Edge>;

 public:
  NeighborGraph(GraphSpec options = {})
    : options(options)
  {}

  void
  AddEdge(const NodeType& fr, const NodeType& to, EdgeType edge) {
    AddNode(fr);
    AddNode(to);
  }

  void
  AddNode(const NodeType& node) {
    if (0 == nodes.count(node))
      nodes[node] = nodes.size();
  }

};

#endif // SEARCH_GRAPH_BUILDER_HH_
