#ifndef SEARCH_GRAPH_NEIGHBOR_GRAPH_HH_
#define SEARCH_GRAPH_NEIGHBOR_GRAPH_HH_

#include <unordered_map>
#include <vector>

namespace search {
// Forward declaration.
template <typename NodeType, typename EdgeType>
class NeighborGraph;

///
/// @class  NeighborGraphSolution
/// @tparam NodeType_   What data type is being stored in this solution.
/// @tparam MatrixType_ What is the underlying matrix storing data.
///
/// This class holds a mapped solution for shortest path.  It stores internally
/// the `Node` mapping to the matrix index.
///
template <typename NodeType_, typename MatrixType_>
class NeighborGraphSolution {
 public:
  using NodeType   = NodeType_;
  using MatrixType = MatrixType_;
  using EdgeType   = MatrixType::Type;
  using NodeMap    = std::unordered_map<NodeType, std::size_t>;

  NeighborGraphSolution() = default;

  ///
  /// @param nodes Initialize the node map.
  /// @param edges Initialize the edge matrix.
  ///
  /// Initialize a graph solution with pre-computed solutions.
  ///
  NeighborGraphSolution(
      NodeMap&& nodes,
      MatrixType&& edges
  ) : nodes(std::move(nodes)),
      edges(std::move(edges))
  {}

  ///
  /// @param nodes         Initialize the node map.
  /// @param all_pairs     If it's a partial solution, false.
  /// @param default_value The default value for the matrix.
  ///
  /// Initialize an empty graph solution.
  ///
  NeighborGraphSolution(
      NodeMap&& nodes,
      bool all_pairs,
      EdgeType default_value
  ) : nodes(nodes),
      edges(all_pairs ? nodes.size() : 1, nodes.size(), default_value)
  {}

  NeighborGraphSolution(NeighborGraphSolution&&) = default;

  NeighborGraphSolution&
  operator=(NeighborGraphSolution&&) = default;

  ///
  /// @param node Find the distance for a given node.
  ///
  /// This assumes that the solution was made without `all_pairs`.  This
  /// will return the shortest edge distance between the node it was created
  /// for and the requested node.
  ///
  EdgeType
  Distance(const NodeType& node) const {
    assert(edges.Rows() == 1);
    return edges.At(0, nodes.at(node));
  }

  ///
  /// @param fr Edge 'from'
  /// @param to Edge 'to'
  ///
  /// This assumes that the solution was made with `all_pairs`.  This
  /// will return the shortest edge distance between the edge from `fr`
  /// to `to`.
  ///
  const EdgeType&
  Distance(const NodeType& fr, const NodeType& to) const {
    assert(edges.Rows() == edges.Cols());
    return edges.At(nodes.at(fr), nodes.at(to));
  }

  ///
  /// Return a reference to the edge matrix.
  ///
  MatrixType&
  Edges() {
    return edges;
  }

  ///
  /// Return a const reference to the edge matrix.
  ///
  const MatrixType&
  Edges() const {
    return edges;
  }

  ///
  /// Return a reference to the node map.
  ///
  NodeMap&
  Nodes() {
    return nodes;
  }

  ///
  /// Return a const reference to the node map.
  ///
  const NodeMap&
  Nodes() const {
    return nodes;
  }

 private:
  NodeMap    nodes;
  MatrixType edges;

  friend class NeighborGraph<NodeType, EdgeType>;

  NeighborGraphSolution(const NeighborGraphSolution&) = default;
  NeighborGraphSolution&
  operator=(const NeighborGraphSolution&) = default;
};

///
/// @class  NeighborGraph
/// @tparam NodeType_  What data type is being stored in this solution.
/// @tparam EdgeType_  What data type is being stored in the edge.
///
/// The `NeighborGraph` is used to store a neighbor graph in graph form,
/// opposed to the `NeighborGraphSolution` which stores it in matrix
/// form.
///
template <typename NodeType_, typename EdgeType_>
class NeighborGraph {
 public:
  using NodeType = NodeType_;
  using EdgeType = EdgeType_;
  using NodeMap  = std::unordered_map<NodeType, std::size_t>;

  ///
  /// @struct Spec
  ///
  /// Specification for constructing a NeighborGraph.
  ///
  struct Spec {
    bool directed = false;
    EdgeType sentinal = std::numeric_limits<EdgeType>::max();
  };

  ///
  /// @struct Edge
  ///
  /// Structure for storing the edge.
  ///
  struct Edge {
    NodeType node;
    EdgeType edge;
  };

  using EdgeList = std::vector<Edge>;

  ///
  /// Basic constructor.
  ///
  NeighborGraph(Spec spec = {})
    : spec(spec)
  {}

  ///
  /// Return the default value for the matrix, this is the `default_value`
  /// passed into the constructor.
  ///
  EdgeType
  DefaultValue() const {
    return spec.sentinal;
  }

  ///
  /// Build a node map.
  ///
  NodeMap
  BuildNodeMap() const {
    NodeMap node_map;
    for (const auto& node: Nodes())
      node_map[node] = node_map.size();

    return node_map;
  }

  ///
  /// Return a list of nodes.
  ///
  std::vector<NodeType>
  Nodes() const {
    std::vector<NodeType> nodes;
    for (const auto& edge: edges)
      nodes.push_back(edge.first);

    return nodes;
  }

  ///
  /// Return the number of unique nodes.
  ///
  std::size_t
  NodeCount() const {
    return edges.size();
  }

  ///
  /// @param node  New node to add.
  /// Add a new node to the graph with no edges.
  ///
  void
  AddNode(NodeType node) {
    edges[node] = {};
  }

  ///
  /// @param node_fr Edge source.
  /// @param node_to Edge destination.
  /// @param edge    Edge weight from source -> destination.
  ///
  /// Add a new edge between the two nodes.  If those nodes did not exist,
  /// create them.
  ///
  void
  AddEdge(NodeType node_fr, NodeType node_to, EdgeType edge) {
    edges[node_fr].push_back({node_to, edge});
    if (!spec.directed) {
      edges[node_to].push_back({node_fr, edge});
    }
  }

  ///
  /// @param node Node to get edges for.
  ///
  /// Fetch a constant reference to the edges for a provided node.
  ///
  const EdgeList&
  Neighbors(NodeType node) const {
    return edges.at(node);
  }

 private:
  Spec spec;
  std::unordered_map<NodeType, EdgeList> edges;
};
} // ns search

#endif // SEARCH_GRAPH_NEIGHBOR_GRAPH_HH_
