CXX=g++
CPPFLAGS=-I./
CXXFLAGS=-O3 -Wall -Wextra -Werror -flto -std=c++20 -g -DNDEBUG
LDFLAGS=-flto -g -L/usr/lib64 -lgtest_main -lgtest

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

SOURCES = \
	test/matrix/dense.cc		\
	test/matrix/sparse_map.cc	\
	test/matrix/conversion.cc	\

OBJECTS = $(subst .cc,.o,$(SOURCES))

buildtest: $(OBJECTS)
	$(CXX) $(LDFLAGS) -o tester $(OBJECTS)

all: buildtest
