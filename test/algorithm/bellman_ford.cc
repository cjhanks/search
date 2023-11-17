#include <gtest/gtest.h>

#include <string>

#include "search/algorithm/bellman_ford.hh"
#include "search/matrix/dense.hh"
#include "search/matrix/sparse_map.hh"

using namespace search;

using Graph = NeighborGraph<unsigned, float>;

TEST(BellmanFord, Single) {
  Graph graph;
  graph.AddEdge(0, 1, 1.0);
  graph.AddEdge(1, 2, 1.0);
  graph.AddEdge(2, 3, 1.0);
  graph.AddEdge(3, 4, 3.0);
  graph.AddEdge(0, 3, 2.5);
  graph.AddEdge(3, 4, 1);

  auto solution = BellmanFord::Solve(graph, 0);

  ASSERT_FLOAT_EQ(solution.Distance(1), 1.0);
  ASSERT_FLOAT_EQ(solution.Distance(2), 2.0);
  ASSERT_FLOAT_EQ(solution.Distance(3), 2.5);
  ASSERT_FLOAT_EQ(solution.Distance(4), 3.5);
}

TEST(BellmanFord, NegativeCycle) {
  Graph graph;
  graph.AddEdge(0, 1,  1.0);
  graph.AddEdge(1, 2, -1.0);
  graph.AddEdge(2, 3,  1.0);
  graph.AddEdge(3, 4, -3.0);
  graph.AddEdge(0, 3,  2.5);
  graph.AddEdge(3, 4,  1);

  try {
    BellmanFord::Solve(graph, 0);
    FAIL() << "No exception";
  } catch (const BellmanFordNegativeWeight& err) {
  }
}

#if 0
TEST(BellmanFord, Multi) {
  Graph graph;
  graph.AddEdge(0, 1, 1.0);
  graph.AddEdge(1, 2, 1.0);
  graph.AddEdge(2, 3, 1.0);
  graph.AddEdge(3, 4, 3.0);
  graph.AddEdge(0, 3, 2.5);
  graph.AddEdge(3, 4, 1);

  auto solution = BellmanFord::Solve(graph);

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

TEST(BellmanFord, MultiString) {
  using StringGraph = NeighborGraph<std::string, float>;
  StringGraph graph;
  graph.AddEdge("0", "1", 1.0);
  graph.AddEdge("1", "2", 1.0);
  graph.AddEdge("2", "3", 1.0);
  graph.AddEdge("3", "4", 3.0);
  graph.AddEdge("0", "3", 2.5);
  graph.AddEdge("3", "4", 1);

  auto solution = BellmanFord::Solve(graph);

  ASSERT_FLOAT_EQ(solution.Distance("0", "1"), 1.0);
  ASSERT_FLOAT_EQ(solution.Distance("0", "2"), 2.0);
  ASSERT_FLOAT_EQ(solution.Distance("0", "3"), 2.5);
  ASSERT_FLOAT_EQ(solution.Distance("0", "4"), 3.5);
  ASSERT_FLOAT_EQ(solution.Distance("1", "2"), 1.0);
  ASSERT_FLOAT_EQ(solution.Distance("1", "3"), 2.0);
  ASSERT_FLOAT_EQ(solution.Distance("1", "4"), 3.0);
  ASSERT_FLOAT_EQ(solution.Distance("1", "0"), 1.0);
  ASSERT_FLOAT_EQ(solution.Distance("2", "0"), 2.0);
  ASSERT_FLOAT_EQ(solution.Distance("3", "0"), 2.5);
  ASSERT_FLOAT_EQ(solution.Distance("4", "0"), 3.5);
  ASSERT_FLOAT_EQ(solution.Distance("2", "1"), 1.0);
  ASSERT_FLOAT_EQ(solution.Distance("3", "1"), 2.0);
  ASSERT_FLOAT_EQ(solution.Distance("4", "1"), 3.0);
}
#endif
