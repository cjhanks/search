#ifndef SEARCH_GRAPH_COMMON_HH_
#define SEARCH_GRAPH_COMMON_HH_

#include <limits>


template <typename NodeType_, typename EdgeType_>
struct GraphSpecification {
  using NodeType = NodeType_;
  using EdgeType = EdgeType_;

  bool directional = false;
  EdgeType sentinal = std::numeric_limits<EdgeType>::max();
};

#endif // SEARCH_GRAPH_COMMON_HH_
