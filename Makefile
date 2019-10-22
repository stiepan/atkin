CC=g++-4.8
CXXFLAGS=-Wall -Wextra -Wpedantic -std=c++11 -c
LDFALGS= -pthread

all: release

release: CXXFLAGS += -DNDEBUG -O3
release: primes

primes: primes.o atkin.o lattice_points.o
	$(CC) $(LDFALGS) $^ -o $@

%.o: %.cc
	$(CC) $(CXXFLAGS) $< -o $@

debug: CXXFLAGS += -DDEBUG -g
debug: primes

.PHONY: clean

clean:
	rm *.o primes
