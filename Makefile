CXX					:= g++
CXXFLAGS			:= -Wall -Wextra -Werror -pedantic -std=c++17 -g

SOURCES				:= src/graph/graph.cpp

.PHONY: all
all: build

.PHONY: build
build:
	$(CXX) $(CXXFLAGS) $(SOURCES) main.cpp -o build

.PHONY: dvi
dvi:
	cd dvi/ && doxygen && open html/index.html && cd ..

.PHONY: clean
clean:
	- rm -rf build
	- rm -rf cd/html cd/latex