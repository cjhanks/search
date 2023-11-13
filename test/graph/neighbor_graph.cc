#include <gtest/gtest.h>

#include "search/graph/neighbor_graph.hh"
#include "search/matrix/dense.hh"
#include "search/matrix/sparse_map.hh"

using namespace search;

using Graph = NeighborGraph<unsigned, float>;

TEST(NeighborGraph, Test1) {
  Graph graph;

  graph.AddEdge(0, 1, 1.0);
  graph.AddEdge(0, 2, 2.0);
  graph.AddEdge(3, 0, 2.0);

  graph.AddNode(4);

  ASSERT_EQ(graph.Neighbors(0).size(), 3);
  ASSERT_EQ(graph.Neighbors(1).size(), 1);
  ASSERT_EQ(graph.Neighbors(2).size(), 1);
  ASSERT_EQ(graph.Neighbors(3).size(), 1);
  ASSERT_EQ(graph.Neighbors(4).size(), 0);
}
