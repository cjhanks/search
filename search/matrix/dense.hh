#ifndef SEARCH_MATRIX_DENSE_HH_
#define SEARCH_MATRIX_DENSE_HH_

#include <cassert>
#include <vector>

#include "search/matrix/common.hh"

namespace search {
/// @class  DenseMatrix
/// @tparam Type_   Underlying type to be stored in this class.
/// @tparam order_  This class can store in Row major OR Col major.
///
/// A dense matrix is a 2D matrix which can be accessed by row/col.
///
template <typename Type_, Order order_=Order::DEFAULT>
class DenseMatrix {
 public:
  static constexpr Order order = order_;
  using Type = Type_;
  using This = DenseMatrix<Type, order>;

  ///
  /// Create a dense matrix of some size.
  ///
  /// @param rows Number of rows in the matrix.
  /// @param cols Number of cols in the matrix.
  /// @param default_value This is the 'sentinal' default value stored in the
  ///                      matrix.
  ///
  DenseMatrix(std::size_t rows, std::size_t cols, Type default_value={})
    : default_value(default_value),
      rows(rows),
      cols(cols),
      data(rows * cols, default_value)
  {}

  ///
  /// Default constructor initializes everything to an empty matrix.
  ///
  DenseMatrix()
    : DenseMatrix(0, 0)
  {}

  /// Movable
  DenseMatrix&
  operator=(DenseMatrix&&) = default;

  /// Constructor Movable
  DenseMatrix(DenseMatrix&&) = default;

  ///
  /// Return the default value for the matrix, this is the `default_value`
  /// passed into the constructor.
  ///
  Type
  DefaultValue() const {
    return default_value;
  }

  ///
  /// @param row Row index to fetch.
  /// @param col Column index to fetch.
  ///
  /// Get *by value* the element.
  ///
  Type
  Get(std::size_t row, std::size_t col) const {
    return data[Index(row, col)];
  }

  ///
  /// @param row Row index to assign.
  /// @param col Column index to assign.
  ///
  /// Assign a value to a given index.
  ///
  void
  Set(std::size_t row, std::size_t col, Type val) {
    data[Index(row, col)] = val;
  }

  ///
  /// @param row Row index to assign.
  /// @param col Column index to assign.
  ///
  /// Get *by reference* the element.
  ///
  Type&
  At(std::size_t row, std::size_t col) {
    return data[Index(row, col)];
  }

  ///
  /// @param row Row index to assign.
  /// @param col Column index to assign.
  ///
  /// Get *by const reference* the element.
  ///
  const Type&
  At(std::size_t row, std::size_t col) const {
    return data[Index(row, col)];
  }

  ///
  /// Return number of rows in the matrix.
  ///
  std::size_t
  Rows() const {
    return rows;
  }

  ///
  /// Return number of cols in the matrix.
  ///
  std::size_t
  Cols() const {
    return cols;
  }

  ///
  /// @tparam NewMat  New matrix storage type.
  ///
  /// Convert this matrix into a new matrix storage type.  This is useful if
  /// you want to convert a dense matrix into a sparse matrix.  Values in the
  /// dense matrix which are the `DefaultValue()` will not be added to the
  /// sparse matrix.
  ///
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

  DenseMatrix&
  operator=(const DenseMatrix&) = default;

  DenseMatrix(const DenseMatrix&) = default;
};
} // ns search

#endif // SEARCH_MATRIX_DENSE_HH_
