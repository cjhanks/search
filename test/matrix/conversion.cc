#include <gtest/gtest.h>

#include "search/matrix/dense.hh"
#include "search/matrix/sparse_map.hh"

using namespace search;


TEST(MatrixConversion, DenseToSparse) {
  DenseMatrix<unsigned> dense(4, 10, 0U);

  for (std::size_t r = 0; r < dense.Rows(); ++r) {
    for (std::size_t c = 0; c < dense.Cols(); ++c) {
      if (r % 2 == 0 && c % 2 == 0)
        dense.At(r, c) = (1 + r) * (1 + c);
    }
  }

  auto sparse = dense.ConvertTo<SparseMapMatrix<unsigned>>();

  for (std::size_t r = 0; r < dense.Rows(); ++r) {
    for (std::size_t c = 0; c < dense.Cols(); ++c) {
      ASSERT_EQ(dense.At(r, c), sparse.At(r, c));
    }
  }
}

TEST(MatrixConversion, SparseToDense) {
  SparseMapMatrix<unsigned> dense(4, 10, 0U);

  for (std::size_t r = 0; r < dense.Rows(); ++r) {
    for (std::size_t c = 0; c < dense.Cols(); ++c) {
      if (r % 2 == 0 && c % 2 == 0)
        dense.At(r, c) = (1 + r) * (1 + c);
    }
  }

  auto sparse = dense.ConvertTo<DenseMatrix<unsigned>>();

  for (std::size_t r = 0; r < dense.Rows(); ++r) {
    for (std::size_t c = 0; c < dense.Cols(); ++c) {
      ASSERT_EQ(dense.At(r, c), sparse.At(r, c));
    }
  }
}
