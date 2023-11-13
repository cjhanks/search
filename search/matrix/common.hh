#ifndef SEARCH_MATRIX_COMMON_HH_
#define SEARCH_MATRIX_COMMON_HH_

namespace search {
///
/// @enum Order
/// Storage order of the underlying type.
///
enum class Order {
  ROW_MAJOR = 1,
  COL_MAJOR = 2,
  DEFAULT   = ROW_MAJOR,
};
} // ns search

#endif // SEARCH_MATRIX_COMMON_HH_
