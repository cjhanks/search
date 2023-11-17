#include <gtest/gtest.h>

#include <string>
#include <utility>
#include <vector>

#include "search/algorithm/knapsack.hh"
//#include "search/matrix/dense.hh"
//#include "search/matrix/sparse_map.hh"

using namespace search;


TEST(Knapsack, Pair) {
  using Type = std::pair<unsigned, float>;

  std::vector<Type> data = {
    {3, 1.0},
    {2, 2.0},
    {5, 7.5},
    {8, 5.0},
  };

  ASSERT_FLOAT_EQ(Knapsack::Solve(data,  7), 11.0);
  ASSERT_FLOAT_EQ(Knapsack::Solve(data,  8), 13.0);
  ASSERT_FLOAT_EQ(Knapsack::Solve(data, 10), 13.0);
}

TEST(Knapsack, Tuple) {
  using Type = std::tuple<unsigned, float>;

  std::vector<Type> data = {
    {3, 1.0},
    {2, 2.0},
    {5, 7.5},
    {8, 5.0},
  };

  ASSERT_FLOAT_EQ(Knapsack::Solve(data,  7), 11.0);
  ASSERT_FLOAT_EQ(Knapsack::Solve(data,  8), 13.0);
  ASSERT_FLOAT_EQ(Knapsack::Solve(data, 10), 13.0);
}
