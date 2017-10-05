CXX=clang++
CXXFLAGS=-O2 -W -std=c++11

SRCS=$(shell ls *.cc)
OBJS=$(SRCS:.cc=.o)

all: primes

primes: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

.cc.o:
	$(CXX) $(CXXFLAGS) -c $<

