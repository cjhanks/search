#ifndef SEARCH_ALGORITHM_DJIKSTRA_HH_
#define SEARCH_ALGORITHM_DJIKSTRA_HH_

#include <cassert>
#include <iostream>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>

#include "search/algorithm/common.hh"
#include "search/graph/neighbor_graph.hh"
#include "search/matrix/dense.hh"

namespace search {
///
/// @class Djikstra
///
/// The classic shortest path algorithm.
///
class Djikstra {
 private:
  template <
    typename Graph,
    bool all_pairs,
    typename NodeType = typename Graph::NodeType,
    typename EdgeType = typename Graph::EdgeType
  >
  static void
  ImplSolve(
      const Graph& graph,
      const std::unordered_map<NodeType, std::size_t>& node_map,
      const NodeType& start,
      DenseMatrix<EdgeType>& edges
  ) {
    // Get the index of the starting index.
    std::size_t start_index = node_map.at(start);

    // Initialize the self-loop.
    if (all_pairs)
      edges.At(start_index, start_index) = 0;
    else
      edges.At(0, start_index) = 0;

    // Initialize.
    std::set<NodeType> observed;
    using Pair = std::pair<EdgeType, NodeType>;
    using PriorityQueue =
        std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>>;

    PriorityQueue pq;
    pq.push({EdgeType(0), start});

    while (!pq.empty()) {
      Pair elem = pq.top();
      pq.pop();

      const auto& node = elem.second;

      if (observed.count(node))
        continue;
      else
        observed.insert(node);

      std::size_t node_index = node_map.at(node);

      for (const auto& neigh: graph.Neighbors(node)) {
        EdgeType old_edge;
        EdgeType new_edge;

        std::size_t neigh_index = node_map.at(neigh.node);

        if (all_pairs) {
          old_edge = edges.At(start_index, neigh_index);
          new_edge = edges.At(start_index, node_index) + neigh.edge;
        } else {
          old_edge = edges.At(0, neigh_index);
          new_edge = edges.At(0, node_index) + neigh.edge;
        }

        if (new_edge < old_edge) {
          if (all_pairs)
            edges.At(start_index, neigh_index) = new_edge;
          else
            edges.At(0, neigh_index) = new_edge;

          pq.push({new_edge, neigh.node});
        }
      }
    }
  }
 public:
  /// @tparam Graph      Template for the graph.
  /// @tparam MatrixType This only needs to be overriden if you want sparse.
  /// @tparam NodeType   Inferred.
  /// @tparam EdgeType   Inferred.
  ///
  /// Solve the shortest path for a single starting node.
  template <
    typename Graph,
    typename MatrixType = DenseMatrix<typename Graph::EdgeType>,
    typename NodeType   = typename Graph::NodeType,
    typename EdgeType   = typename Graph::EdgeType
  >
  static NeighborGraphSolution<NodeType, MatrixType>
  Solve(const Graph& graph, const typename Graph::NodeType& start) {
    using NodeMap = typename Graph::NodeMap;
    NodeMap node_map = graph.BuildNodeMap();

    NeighborGraphSolution<NodeType, MatrixType> solution(
        std::move(node_map),
        false,
        graph.DefaultValue()
    );
    ImplSolve<Graph, false>(
      graph,
      solution.Nodes(),
      start,
      solution.Edges()
    );

    return solution;
  }

  /// @tparam Graph      Template for the graph.
  /// @tparam MatrixType This only needs to be overriden if you want sparse.
  /// @tparam NodeType   Inferred.
  /// @tparam EdgeType   Inferred.
  ///
  /// Solve the shortest path for all starting nodes.
  template <
    typename Graph,
    typename MatrixType = DenseMatrix<typename Graph::EdgeType>,
    typename NodeType   = typename Graph::NodeType,
    typename EdgeType   = typename Graph::EdgeType
  >
  static NeighborGraphSolution<NodeType, MatrixType>
  Solve(const Graph& graph) {
    using NodeMap = typename Graph::NodeMap;
    NodeMap node_map = graph.BuildNodeMap();

    NeighborGraphSolution<NodeType, MatrixType> solution(
        std::move(node_map),
        true,
        graph.DefaultValue()
    );

    for (const auto& node: node_map) {
      ImplSolve<Graph, true>(
        graph,
        solution.Nodes(),
        node.first,
        solution.Edges()
      );
    }

    return solution;
  }
};
} // ns search
#endif // SEARCH_ALGORITHM_DJIKSTRA_HH_
