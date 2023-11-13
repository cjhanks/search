#include <gtest/gtest.h>
#include "search/matrix/sparse_map.hh"

using namespace search;


TEST(SparseMapMatrix, DefaultConstruct) {
  using Mat = SparseMapMatrix<unsigned>;

  const Mat mat(3, 4, 1U);
  ASSERT_EQ(mat.DefaultValue(), 1U);

  for (std::size_t r = 0; r < mat.Rows(); ++r) {
    for (std::size_t c = 0; c < mat.Cols(); ++c) {
      ASSERT_EQ(mat.At(r, c), 1U);
    }
  }
}

TEST(SparseMapMatrix, DefaultConstructConst) {
  using Mat = SparseMapMatrix<unsigned>;

  Mat mat(3, 4, 1U);
  for (std::size_t r = 0; r < mat.Rows(); ++r) {
    for (std::size_t c = 0; c < mat.Cols(); ++c) {
      ASSERT_EQ(mat.At(r, c), 1U);
    }
  }
}

TEST(SparseMapMatrix, Assignment) {
  using Mat = SparseMapMatrix<unsigned>;

  Mat mat(3, 4, 1U);
  for (std::size_t r = 0; r < mat.Rows(); ++r) {
    for (std::size_t c = 0; c < mat.Cols(); ++c) {
      mat.At(r, c) = (1 + r) * (1 + c);
    }
  }

  for (std::size_t r = 0; r < mat.Rows(); ++r) {
    for (std::size_t c = 0; c < mat.Cols(); ++c) {
      ASSERT_EQ(mat.At(r, c), (1 + r) * (1 + c));
      ASSERT_EQ(mat.Get(r, c), (1 + r) * (1 + c));
    }
  }
}
