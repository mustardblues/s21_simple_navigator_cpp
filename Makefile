# ------------------------------------------------------------------------------------------ Macros

CXX							:= g++
CXXFLAGS						:= -Wall -Wextra -Werror -pedantic -std=c++17 -g
SYSFLAGS						:= -lgtest -lstdc++

ifeq ($(shell uname), Linux)
	SYSFLAGS					+= -pthread -lrt -lm
endif

GRAPH_SOURCES 						:= src/graph/graph.cpp
GRAPH_OBJECTS						:= graph.o

ALGORITMS_SOURCES					:= src/algorithms/algorithms.cpp
ALGORITMS_OBJECTS					:= algorithms.o

GRAPH_TEST_SOURCES					:= tests/unit/graph/test_graph.cpp

CONTAINERS_TEST_SOURCES					:= tests/unit/containers/test_queue.cpp \
							   tests/unit/containers/test_stack.cpp

ALGORITMS_TEST_SOURCES					:= test/unit/algorithms/test_algorithms.cpp

# ----------------------------------------------------------------------------------------- Targets


.PHONY: all
all: test

.PHONY: help
help:
	@grep -E '^[a-zA-Z0-9 - _]+:.*#'  Makefile | sort | while read -r l; do \
	printf "\033[1;36m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done

.PHONY: install_doxygen
install_doxygen: # installs Doxygen
	sudo apt update && sudo apt-get doxygen

# ------------------------------------------------------------------------------------------- Tests

.PHONY: test
test: # Testing of all project sources
	$(CXX) $(CXXFLAGS) --coverage $(CONTAINERS_TEST_SOURCES) $(GRAPH_TEST_SOURCES) $(GRAPH_SOURCES) \
	tests/unit/main.cpp -o test $(SYSFLAGS) && ./test

.PHONY: test_graph
test_graph: # Testing of Graph class
	$(CXX) $(CXXFLAGS) --coverage $(GRAPH_TEST_SOURCES) $(GRAPH_SOURCES) \
	tests/unit/main.cpp -o test_graph $(SYSFLAGS) && ./test_graph

.PHONY: test_containers
test_containers: # Testing of container classes
	$(CXX) $(CXXFLAGS) --coverage $(CONTAINERS_TEST_SOURCES) \
	tests/unit/main.cpp -o test_containers $(SYSFLAGS) && ./test_containers

# ---------------------------------------------------------------------------------------- Archives

.PHONY: s21_graph
s21_graph: $(GRAPH_OBJECTS) # creates a Graph class archive
	ar src s21_graph.a $? && rm -rf $?

$(GRAPH_OBJECTS): $(GRAPH_SOURCES)
	$(CXX) $(CXXFLAGS) -c $? -o $@

.PHONY: s21_graph_algorithms
s21_graph_algorithms: $(ALGORITMS_OBJECTS) # creates a GraphAlgorithm class archive
	ar src s21_graph_algorithms.a $? && rm -rf $?

$(ALGORITMS_OBJECTS): $(ALGORITMS_SOURCES)
	$(CXX) $(CXXFLAGS) -c $? -o $@

# ----------------------------------------------------------------------------------------- Linters

.PHONY: style
style: # checks code for Google style
	find . \( -name "*.h" -o -name "*.c" -o -name "*.hpp" -o -name "*.cpp" \) -print0 \
	| xargs --null clang-format -n --style=Google

cppcheck:
	cppcheck --enable=all --force --suppress=missingIncludeSystem --language=c++ \
	$(GRAPH_SOURCES) $(ALGORITMS_SOURCES) 

.PHONY: leaks
leaks: test # checks code for leaks using Valgrind utility
	valgrind --tool=memcheck --track-fds=yes --quiet --trace-children=yes \
	--track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test

# ------------------------------------------------------------------------------- Abstracts Targets

clean:
	- rm test
	- rm test_graph
	- rm test_containers
	- rm *.dot
	- rm -rf gcov_report
	- rm *.gcno *.gcda *.info
	- rm -rf dvi/doxygen

rebuild: clean all
