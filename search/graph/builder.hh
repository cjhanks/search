#ifndef SEARCH_GRAPH_BUILDER_HH_
#define SEARCH_GRAPH_BUILDER_HH_

#include "search/matrix/dense.hh"
#include "search/matrix/sparse_map.hh"


template <typename MatrixType_>
struct AdjacencyGraph {
  using MatrixType = MatrixType_;
  using NodeType   = typename MatrixType::NodeType;
  using EdgeType   = typename MatrixType::EdgeType;

  GraphSpec spec;
  std::vector<NodeType> nodes;
  MatrixType matrix;
};

template <typename MatrixType_>
class GraphBuilder {
 public:
  using MatrixType = MatrixType_;
  using NodeType   = typename MatrixType::NodeType;
  using EdgeType   = typename MatrixType::EdgeType;

 private:
  struct Edge {
    std::size_t node_fr_index;
    std::size_t node_to_index;
    EdgeType edge;
  };

 public:
  GraphBuilder(GraphSpec options = {})
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

  AdjacencyGraph<MatrixType>
  Build() const {
    AdjacencyGraph<MatrixType> out(nodes.size(), options.sentinal);
    out.spec = options;

    for (auto& elem: nodes)
      out.nodes[elem->second] = elem->first;

    for (const auto& edge: edges) {
      out.matrix.At(edge.node_fr_index, edge.node_to_index) = edge;

      if (!options.directional)
        out.matrix.At(edge.node_to_index, edge.node_fr_index) = edge;
    }

    return out;
  }

 private:
  GraphSpec options;
  std::unordered_map<NodeType, std::size_t> nodes;
  std::vector<Edge> edges;
};
