#ifndef SEARCH_MATRIX_DENSE_HH_
#define SEARCH_MATRIX_DENSE_HH_

#include <cassert>
#include <vector>

#include "search/matrix/common.hh"

namespace search {
template <typename Type_, Order order_=Order::DEFAULT>
class DenseMatrix {
 public:
  static constexpr Order order = order_;
  using Type = Type_;
  using This = DenseMatrix<Type, order>;
  // -

  DenseMatrix(std::size_t rows, std::size_t cols, Type default_value={})
    : default_value(default_value),
      rows(rows),
      cols(cols),
      data(rows * cols, default_value)
  {}

  DenseMatrix()
    : DenseMatrix(0, 0)
  {}

  Type
  DefaultValue() const {
    return default_value;
  }

  Type&
  At(std::size_t row, std::size_t col) {
    return data[Index(row, col)];
  }

  const Type&
  At(std::size_t row, std::size_t col) const {
    return data[Index(row, col)];
  }

  std::size_t
  Rows() const {
    return rows;
  }

  std::size_t
  Cols() const {
    return cols;
  }

  template <typename NewMat>
  NewMat
  ConvertTo() {
    if constexpr (std::is_same<This, typename NewMat::This>::value) {
      return *this;
    } else {
      NewMat mat(Rows(), Cols(), DefaultValue());

      for (std::size_t r = 0; r < Rows(); ++r) {
        for (std::size_t c = 0; c < Cols(); ++c) {
          const auto& val = At(r, c);
          if (val != DefaultValue())
            mat.At(r, c) = val;
        }
      }

      return mat;
    }
  }

 private:
  Type default_value;
  std::size_t rows;
  std::size_t cols;
  std::vector<Type> data;

  std::size_t
  Index(std::size_t row, std::size_t col) const {
    assert(row < rows);
    assert(col < cols);
    if (order == Order::ROW_MAJOR)
      return (row * cols) + col;
    else
      return (col * rows) + row;
  }
};
} // ns search

#endif // SEARCH_MATRIX_DENSE_HH_
