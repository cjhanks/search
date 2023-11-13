#ifndef SEARCH_MATRIX_SPARSE_MAP_HH_
#define SEARCH_MATRIX_SPARSE_MAP_HH_

#include <unordered_map>
#include <utility>

namespace search {
template <typename Type_>
class SparseMapMatrix {
 private:
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

  SparseMapMatrix(std::size_t rows, std::size_t cols, Type default_value={})
    : rows(rows),
      cols(cols),
      default_value(default_value),
      data(1, PointHasher(rows, cols))
  {}

  SparseMapMatrix()
    : SparseMapMatrix(0, 0)
  {}

  Type
  DefaultValue() const {
    return default_value;
  }

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

  const Type&
  At(std::size_t row, std::size_t col) const {
    const auto elem = data.find(Point(row, col));
    if (elem == data.end())
      return default_value;
    else
      return elem->second;
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
  std::size_t rows;
  std::size_t cols;
  const Type default_value;
  std::unordered_map<Point, Type, PointHasher> data;
};
} // ns search

#endif // SEARCH_MATRIX_SPARSE_MAP_HH_
