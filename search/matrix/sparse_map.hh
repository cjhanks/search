#ifndef SEARCH_MATRIX_SPARSE_MAP_HH_
#define SEARCH_MATRIX_SPARSE_MAP_HH_

#include <unordered_map>
#include <utility>

namespace search {
/// @class  SparseMapMatrix
/// @tparam Type_   Underlying type to be stored in this class.
///
/// A sparse matrix is a 2D matrix which can be accessed by row/col.  By
/// default, all of the indices are empty.
///
template <typename Type_>
class SparseMapMatrix {
 private:
  ///
  /// @struct Point
  /// Simple structure to hold a row/col index.
  ///
  struct Point {
    Point() = default;
    Point(std::size_t row, std::size_t col)
      : row(row),
        col(col)
    {}

    bool
    operator==(const Point& pt) const {
      return row == pt.row
          && col == pt.col;
    }

    std::size_t row = 0;
    std::size_t col = 0;
  };

  ///
  /// @struct PointHasher
  /// To be used in conjunection with the `Point` to be used in an
  /// unordered_map.
  ///
  struct PointHasher {
    PointHasher(std::size_t rows, std::size_t cols)
      : rows(rows),
        cols(cols)
    {}

    std::size_t
    operator()(const Point& pt) const {
      return pt.row * cols + pt.col;
    }

    std::size_t rows;
    std::size_t cols;
  };

 public:
  using Type = Type_;
  using This = SparseMapMatrix<Type>;

  ///
  /// Create a sparse matrix of some size.
  ///
  /// @param rows Number of rows in the matrix.
  /// @param cols Number of cols in the matrix.
  /// @param default_value This is the 'sentinal' default value stored in the
  ///                      matrix.
  ///
  SparseMapMatrix(std::size_t rows, std::size_t cols, Type default_value={})
    : rows(rows),
      cols(cols),
      default_value(default_value),
      data(1, PointHasher(rows, cols))
  {}

  ///
  /// Default constructor initializes everything to an empty matrix.
  ///
  SparseMapMatrix()
    : SparseMapMatrix(0, 0)
  {}

  /// Movable
  SparseMapMatrix&
  operator=(SparseMapMatrix&&) = default;

  /// Constructor Movable
  SparseMapMatrix(SparseMapMatrix&&) = default;

  ///
  /// Default constructor initializes everything to an empty matrix.
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
    return At(row, col);
  }

  ///
  /// @param row Row index to assign.
  /// @param col Column index to assign.
  ///
  /// Assign a value to a given index.
  ///
  void
  Set(std::size_t row, std::size_t col, Type val) {
    At(row, col) = val;
  }

  ///
  /// @param row Row index to assign.
  /// @param col Column index to assign.
  ///
  /// Get *by reference* the element.  If it does not exist, it is created and
  /// initialized to the default value.
  ///
  Type&
  At(std::size_t row, std::size_t col) {
    Point pt(row,col);
    auto elem = data.find(pt);
    if (elem == data.end()) {
      Type& value = (data[pt] = default_value);
      return value;
    } else {
      return elem->second;
    }
  }

  ///
  /// @param row Row index to assign.
  /// @param col Column index to assign.
  ///
  /// Get *by const reference* the element.  If it does not exist, it is not
  /// created.
  ///
  const Type&
  At(std::size_t row, std::size_t col) const {
    const auto elem = data.find(Point(row, col));
    if (elem == data.end())
      return default_value;
    else
      return elem->second;
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
  std::size_t rows;
  std::size_t cols;
  const Type default_value;
  std::unordered_map<Point, Type, PointHasher> data;

  SparseMapMatrix&
  operator=(const SparseMapMatrix&) = default;

  SparseMapMatrix(const SparseMapMatrix&) = default;
};
} // ns search

#endif // SEARCH_MATRIX_SPARSE_MAP_HH_
