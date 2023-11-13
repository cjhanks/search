#ifndef SEARCH_ALGORITHM_BELLMAN_FORD_HH_
#define SEARCH_ALGORITHM_BELLMAN_FORD_HH_

#include <stdexcept>

#include "search/graph/neighbor_graph.hh"
#include "search/matrix/dense.hh"

namespace search {
///
/// @class BellmanFordNegativeWeight
///
/// If there is a negative weight cycle in the Bellman Ford solver, this
/// exception is thrown.
///
class BellmanFordNegativeWeight : public std::runtime_error {
 public:
  BellmanFordNegativeWeight()
    : std::runtime_error("BellmanFordNegativeWeight") {}
};


///
/// @class BellmanFord
///
/// Shortest path solver.
///
class BellmanFord {
 public:
  /// @tparam Graph      Template for the graph.
  /// @tparam MatrixType This only needs to be overriden if you want sparse.
  /// @tparam NodeType   Inferred.
  /// @tparam EdgeType   Inferred.
  template <
    typename Graph,
    typename MatrixType = DenseMatrix<typename Graph::EdgeType>,
    typename NodeType = typename Graph::NodeType,
    typename EdgeType = typename Graph::EdgeType
  >
  static NeighborGraphSolution<NodeType, MatrixType>
  Solve(const Graph& graph, const typename Graph::NodeType& start) {
    MatrixType matrix(
        1,
        graph.NodeCount(),
        graph.DefaultValue()
    );
    auto node_map = graph.BuildNodeMap();
    matrix.At(0, node_map[start]) = 0;

    for (std::size_t i = 1; i < graph.NodeCount(); ++i) {
      bool changes = false;

      // Iterate all edges.
      for (const auto& node: graph.Nodes()) {
        std::size_t idx_fr = node_map[node];

        for (const auto& neigh: graph.Neighbors(node)) {
          std::size_t idx_to = node_map[neigh.node];

          if (matrix.At(0, idx_fr) != graph.DefaultValue()
           && matrix.At(0, idx_fr) + neigh.edge < matrix.At(0, idx_to)) {
            matrix.At(0, idx_to) = matrix.At(0, idx_fr) + neigh.edge;
            changes = true;
          }
        }
      }

      if (!changes)
        break;
    }

    // Test for negative-weight cycles.
    for (const auto& node: graph.Nodes()) {
      std::size_t idx_fr = node_map[node];

      for (const auto& neigh: graph.Neighbors(node)) {
        std::size_t idx_to = node_map[neigh.node];

        if (matrix.At(0, idx_fr) != graph.DefaultValue()
         && matrix.At(0, idx_fr) + neigh.edge < matrix.At(0, idx_to)) {
          throw BellmanFordNegativeWeight();
        }
      }
    }

    return NeighborGraphSolution<NodeType, MatrixType>(
        std::move(node_map),
        std::move(matrix)
    );
  }
};
} // ns search

#endif /// SEARCH_ALGORITHM_BELLMAN_FORD_HH_
