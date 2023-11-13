#include <gtest/gtest.h>
#include "search/matrix/dense.hh"

using namespace search;


TEST(DenseMatrixRow, Constructor) {
  using Mat = DenseMatrix<unsigned, Order::ROW_MAJOR>;

  Mat mat(3, 3, 1U);
  ASSERT_EQ(mat.DefaultValue(), 1U);

  for (std::size_t r = 0; r < mat.Rows(); ++r) {
    for (std::size_t c = 0; c < mat.Cols(); ++c) {
      ASSERT_EQ(mat.At(r, c), 1U);
    }
  }
}

TEST(DenseMatrixRow, Size) {
  using Mat = DenseMatrix<unsigned, Order::ROW_MAJOR>;

  Mat mat(3, 5, 1U);
  ASSERT_EQ(mat.Rows(), 3);
  ASSERT_EQ(mat.Cols(), 5);
}

TEST(DenseMatrixRow, Assign) {
  using Mat = DenseMatrix<unsigned, Order::ROW_MAJOR>;

  Mat mat(3, 3, 1U);
  for (std::size_t r = 0; r < mat.Rows(); ++r) {
    for (std::size_t c = 0; c < mat.Cols(); ++c) {
      mat.At(r, c) = (1 + r) * (1 + c);
    }
  }

  for (std::size_t r = 0; r < mat.Rows(); ++r) {
    for (std::size_t c = 0; c < mat.Cols(); ++c) {
      ASSERT_EQ(mat.At(r, c), (1 + r) * (1 + c));
    }
  }
}

TEST(DenseMatrixRow, Alignment) {
  using Mat = DenseMatrix<unsigned, Order::ROW_MAJOR>;

  Mat mat(3, 3, 1U);
  ASSERT_EQ(&mat.At(0, 1) - &mat.At(0, 0), 1);
}

TEST(DenseMatrixCol, Constructor) {
  using Mat = DenseMatrix<unsigned, Order::COL_MAJOR>;

  Mat mat(3, 3, 1U);
  for (std::size_t r = 0; r < mat.Rows(); ++r) {
    for (std::size_t c = 0; c < mat.Cols(); ++c) {
      ASSERT_EQ(mat.At(r, c), 1U);
    }
  }
}

TEST(DenseMatrixCol, Size) {
  using Mat = DenseMatrix<unsigned, Order::COL_MAJOR>;

  Mat mat(3, 5, 1U);
  ASSERT_EQ(mat.Rows(), 3);
  ASSERT_EQ(mat.Cols(), 5);
}


TEST(DenseMatrixCol, Assign) {
  using Mat = DenseMatrix<unsigned, Order::COL_MAJOR>;

  Mat mat(3, 3, 1U);
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

TEST(DenseMatrixCol, Alignment) {
  using Mat = DenseMatrix<unsigned, Order::COL_MAJOR>;

  Mat mat(3, 3, 1U);
  ASSERT_EQ(&mat.At(1, 0) - &mat.At(0, 0), 1);
}
