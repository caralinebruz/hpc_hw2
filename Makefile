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
LDFLAGS+= \
        -L/opt/homebrew/opt/llvm/lib\
        -L/opt/homebrew/opt/libomp/lib\

CPPFLAGS+= \
		-I/opt/homebrew/opt/llvm/include\
		-I/opt/homebrew/opt/libomp/include\

all : $(TARGETS)

%:%.cpp
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(CXXFLAGS) $^ -o $@

clean:
	$(RM) $(TARGETS)