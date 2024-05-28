#----------------------------------------------#
#                   Makefile                   #
#----------------------------------------------#

.PHONY: all nowarn quiet silent clean clean-temp

EXECS := primes-c primes-cpp
all:     $(EXECS)

#CC      := clang
#CXX     := clang++
CC       := gcc
CXX      := g++
CFLAGS   := -O2 -std=c11
CXXFLAGS := -O2 -std=c++11
LDFLAGS  := -lm

WARN := -Wall -Wextra -Wunreachable-code \
        -pedantic -Winit-self -Wcast-align \
        -Wpointer-arith -Wswitch-default \
        -Wno-unused-parameter -Wno-comment
WARNX = $(WARN) -Wextra-semi -Wregister

#----------------------------------------------#

nowarn quiet silent: WARN  := -w
nowarn quiet silent: WARNX := -w
nowarn quiet silent: all

%.c.o: %.c $(wildcard *.h)
	@printf '\033[0;96m[%s -> %s]\033[0m\n' "$<" "$@"
	$(CC) $(CFLAGS) $(WARN) -o $@ -c $<

primes-c: $(addsuffix .o, $(wildcard *.c))
	@printf '\033[0;96m[%s -> %s]\033[0m\n' "$^" "$@"
	$(CC) $(CFLAGS) $(WARN) -o $@ $^ $(LDFLAGS)

%.cpp.o: %.cpp $(wildcard *.hpp)
	@printf '\033[0;96m[%s -> %s]\033[0m\n' "$<" "$@"
	$(CXX) $(CXXFLAGS) $(WARNX) -o $@ -c $<

primes-cpp: $(addsuffix .o, $(wildcard *.cpp))
	@printf '\033[0;96m[%s -> %s]\033[0m\n' "$^" "$@"
	$(CXX) $(CXXFLAGS) $(WARNX) -o $@ $^ $(LDFLAGS)

#----------------------------------------------#

clean-temp: EXECS :=
clean-temp: clean

clean:
	@rm -fvr $(EXECS) *.o *~ *.swp .mypy_cache/ __pycache__/ | \
	sed "/\/../ d; s/^[^'\"]*/ \c[[0;91m/; s/[^'\"]*$$/\c[[0m/"

#----------------------------------------------#
