CXX					:= g++
CXXFLAGS			:= -Wall -Wextra -Werror -pedantic -std=c++17 -g

SOURCES				:=  src/graph/graph.cpp

TEST_SOURCES		:=  tests/unit/containers/test_queue.cpp \
						tests/unit/containers/test_stack.cpp

.PHONY: all
all: build

.PHONY: build
build:
	$(CXX) $(CXXFLAGS) $(SOURCES) main.cpp -o build 

.PHONY: test
test:
	$(CXX) $(CXXFLAGS) $(SOURCES) tests/unit/graph/test_graph.cpp tests/unit/main.cpp -o test -pthread -lgtest -lstdc++ -lrt -lm
	- rm graph.dot

.PHONY: dvi
dvi:
	cd dvi/ && doxygen && open html/index.html && cd ..

.PHONY: clean
clean:
	- rm -rf build
	- rm -rf cd/html cd/latex