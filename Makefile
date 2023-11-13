CXX=g++
CPPFLAGS=-I./
CXXFLAGS=-O3 -Wall -Wextra -Werror -std=c++20 -g -DNDEBUG
LDFLAGS=-g -L/usr/lib64 -lgtest_main -lgtest

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

SOURCES = \
	test/matrix/dense.cc			\
	test/matrix/sparse_map.cc		\
	test/matrix/conversion.cc		\
	test/graph/neighbor_graph.cc		\
	test/algorithm/djikstra.cc		\
	test/algorithm/floyd_warshall.cc	\
	test/algorithm/knapsack.cc		\
	test/algorithm/bellman_ford.cc		\

OBJECTS = $(subst .cc,.o,$(SOURCES))

docs: $(OBJECTS)
	doxygen doxygen.cfg

buildtest: $(OBJECTS)
	$(CXX) $(LDFLAGS) -o gtest $(OBJECTS)

clean:
	$(RM) $(OBJECTS)

all: buildtest
