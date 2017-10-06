CXX=clang++
CXXFLAGS=-O2 -W -std=c++11
LDFLAGS=-lgflags

SRCS=$(shell ls *.cc)
OBJS=$(SRCS:.cc=.o)

all: primes

primes: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.cc.o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o primes

