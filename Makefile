# CXX = g++
# # CXXFLAGS = -std=c++11 -O3 -march=native
# # CXXFLAGS = -std=c++11 -O3 -mcpu=apple-m1
# CXXFLAGS = -std=c++11 -O3 -mcpu=apple-m1
# # CXXFLAGS = -std=c++11 -O2 -mcpu=apple-m1

CXX = g++
CXXFLAGS = -std=c++11 -O3 -mcpu=apple-m1

RM = rm -f
MKDIRS = mkdir -p

TARGETS = $(basename $(wildcard *.cpp))

all : $(TARGETS)

%:%.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	$(RM) $(TARGETS)