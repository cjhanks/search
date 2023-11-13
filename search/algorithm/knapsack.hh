#ifndef SEARCH_ALGORITHM_KNAPSACK_HH_
#define SEARCH_ALGORITHM_KNAPSACK_HH_

#include <tuple>
#include <utility>

#include "search/matrix/dense.hh"

namespace search {
///
/// @class  KnapsackAccess
/// @tparam Type for the underlying knapsack data type.
///
/// This class is used to define an access pattern for fetching the value and
/// cost for a single item in the list.
///
template <typename Type>
struct KnapsackAccess;

///
/// @class  KnapsackAccess<std::pair<A, B>>
/// @tparam A Value
/// @tparam B Cost
///
template <typename A, typename B>
struct KnapsackAccess<std::pair<A, B>> {
  static A
  Value(const std::pair<A, B>& pair) {
    return pair.first;
  }

  static B
  Cost(const std::pair<A, B>& pair) {
    return pair.second;
  }
};

///
/// @class  KnapsackAccess<std::tuple<A, B>>
/// @tparam A Value
/// @tparam B Cost
///
template <typename A, typename B>
struct KnapsackAccess<std::tuple<A, B>> {
  static A
  Value(const std::tuple<A, B>& tuple) {
    return std::get<0>(tuple);
  }

  static B
  Cost(const std::tuple<A, B>& tuple) {
    return std::get<1>(tuple);
  }
};

///
/// This is a C++ concept helps with compilations errors for custom
/// `KnapsackAccess`.
///
template <typename Access, typename Type>
concept KnapsackAccessConcept =
  requires(Access access, Type obj) {
  { access.Value(obj) };
  { access.Cost(obj)  };
};

///
/// @class  KnapsackTypeTrait
/// @tparam Access  Structure for the accessor.
///
/// This is a helper class for storing type traits.
///
template <typename Access>
struct KnapsackTypeTrait {
  using ValueType = decltype(((Access*)nullptr)->Value({}));
  using CostType  = decltype(((Access*)nullptr)->Cost({}));
};

///
/// @class Knapsack
///
/// Implementaiton of the standard knapsack problem.
///
class Knapsack {
 public:
  /// @tparam Container  This only needs to be overriden if you want sparse.
  /// @tparam Access     This can be overriden to support new types.
  /// @tparam Type       Inferred.
  /// @tparam Traits     Inferred.
  ///
  /// Solve and return a single value.
  template <
    typename Container,
    typename Access = KnapsackAccess<typename Container::value_type>,
    typename Type   = typename Container::value_type,
    typename Traits = KnapsackTypeTrait<Access>
  >
  static typename Traits::ValueType
  Solve(const Container& elems, Traits::ValueType cost)
    requires KnapsackAccessConcept<Access, Type> {
    using Cost = typename Traits::CostType;
    DenseMatrix<Cost> mat(elems.size() + 1, cost + 1, 0);

    for (std::size_t n = 1; n < mat.Rows(); ++n) {
      const auto& v = Access::Value(elems[n - 1]);
      const auto& w = Access::Cost(elems[n - 1]);

      for (std::size_t c = 1; c < mat.Cols(); ++c) {
        if (w <= c) {
          const auto& a = mat.At(n - 1, c - w) + v;
          const auto& b = mat.At(n - 1, c);

          mat.At(n, c) = std::max(a, b);
        } else {
          mat.At(n, c) = mat.At(n - 1, c);
        }
      }
    }

    return mat.Get(mat.Rows() - 1, mat.Cols() - 1);
  }
};
} // ns search

#endif // SEARCH_ALGORITHM_KNAPSACK_HH_
