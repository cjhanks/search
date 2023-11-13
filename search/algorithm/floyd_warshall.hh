#ifndef SEARCH_ALGORITHM_FLOYD_WARSHALL_HH_
#define SEARCH_ALGORITHM_FLOYD_WARSHALL_HH_

#include <cassert>

#include "search/graph/neighbor_graph.hh"
#include "search/matrix/dense.hh"

namespace search {
///
/// @class FloydWarshall
///
/// The Floyd Warshall algorithm is used to solve all shortest paths amongst
/// all nodes in a graph.
///
class FloydWarshall {
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
  Solve(const Graph& graph) {
    assert(matrix.Rows() == matrix.Cols());

    auto node_map = graph.BuildNodeMap();
    MatrixType matrix(
        graph.NodeCount(),
        graph.NodeCount(),
        graph.DefaultValue()
    );

    for (const auto& node: graph.Nodes()) {
      std::size_t idx_fr = node_map[node];
      for (const auto& neigh: graph.Neighbors(node)) {
        std::size_t idx_to = node_map[neigh.node];
        matrix.At(idx_fr, idx_to) = neigh.edge;
      }
    }

    for (std::size_t k = 0; k < matrix.Rows(); ++k) {
      bool changed = false;
      for (std::size_t i = 0; i < matrix.Rows(); ++i) {
        for (std::size_t j = 0; j < matrix.Cols(); ++j) {
          const auto a = matrix.Get(i, j);
          const auto b = matrix.Get(k, j);
          const auto c = matrix.Get(i, k);

          if (b == matrix.DefaultValue()
           || c == matrix.DefaultValue())
            continue;

          if (b + c < a) {
            matrix.Set(i, j, b + c);
            changed = true;
          }
        }
      }

      if (!changed)
        break;
    }

    return NeighborGraphSolution<NodeType, MatrixType>(
        std::move(node_map),
        std::move(matrix)
    );
  }
};
} // ns search

#endif // SEARCH_ALGORITHM_FLOYD_WARSHALL_HH_
