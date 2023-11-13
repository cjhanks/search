#include <gtest/gtest.h>

#include <string>

#include "search/algorithm/floyd_warshall.hh"
#include "search/graph/neighbor_graph.hh"
#include "search/matrix/dense.hh"
#include "search/matrix/sparse_map.hh"

using namespace search;

using Graph = NeighborGraph<unsigned, float>;

TEST(FloydWarshall, Dense) {
  Graph graph;
  graph.AddEdge(0, 1, 1.0);
  graph.AddEdge(1, 2, 1.0);
  graph.AddEdge(2, 3, 1.0);
  graph.AddEdge(3, 4, 3.0);
  graph.AddEdge(0, 3, 2.5);
  graph.AddEdge(3, 4, 1);

  auto solution = FloydWarshall::Solve(graph);

  ASSERT_FLOAT_EQ(solution.Distance(0, 1), 1.0);
  ASSERT_FLOAT_EQ(solution.Distance(0, 2), 2.0);
  ASSERT_FLOAT_EQ(solution.Distance(0, 3), 2.5);
  ASSERT_FLOAT_EQ(solution.Distance(0, 4), 3.5);
  ASSERT_FLOAT_EQ(solution.Distance(1, 2), 1.0);
  ASSERT_FLOAT_EQ(solution.Distance(1, 3), 2.0);
  ASSERT_FLOAT_EQ(solution.Distance(1, 4), 3.0);

  ASSERT_FLOAT_EQ(solution.Distance(1, 0), 1.0);
  ASSERT_FLOAT_EQ(solution.Distance(2, 0), 2.0);
  ASSERT_FLOAT_EQ(solution.Distance(3, 0), 2.5);
  ASSERT_FLOAT_EQ(solution.Distance(4, 0), 3.5);
  ASSERT_FLOAT_EQ(solution.Distance(2, 1), 1.0);
  ASSERT_FLOAT_EQ(solution.Distance(3, 1), 2.0);
  ASSERT_FLOAT_EQ(solution.Distance(4, 1), 3.0);
}

TEST(FloydWarshall, Sparse) {
  Graph graph;
  graph.AddEdge(0, 1, 1.0);
  graph.AddEdge(1, 2, 1.0);
  graph.AddEdge(2, 3, 1.0);
  graph.AddEdge(3, 4, 3.0);
  graph.AddEdge(0, 3, 2.5);
  graph.AddEdge(3, 4, 1);

  auto solution = FloydWarshall::Solve(graph);

  ASSERT_FLOAT_EQ(solution.Distance(0, 1), 1.0);
  ASSERT_FLOAT_EQ(solution.Distance(0, 2), 2.0);
  ASSERT_FLOAT_EQ(solution.Distance(0, 3), 2.5);
  ASSERT_FLOAT_EQ(solution.Distance(0, 4), 3.5);
  ASSERT_FLOAT_EQ(solution.Distance(1, 2), 1.0);
  ASSERT_FLOAT_EQ(solution.Distance(1, 3), 2.0);
  ASSERT_FLOAT_EQ(solution.Distance(1, 4), 3.0);

  ASSERT_FLOAT_EQ(solution.Distance(1, 0), 1.0);
  ASSERT_FLOAT_EQ(solution.Distance(2, 0), 2.0);
  ASSERT_FLOAT_EQ(solution.Distance(3, 0), 2.5);
  ASSERT_FLOAT_EQ(solution.Distance(4, 0), 3.5);
  ASSERT_FLOAT_EQ(solution.Distance(2, 1), 1.0);
  ASSERT_FLOAT_EQ(solution.Distance(3, 1), 2.0);
  ASSERT_FLOAT_EQ(solution.Distance(4, 1), 3.0);
}
