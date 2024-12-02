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

MATRIX_TEST_SOURCES					:= tests/unit/matrix/test_matrix.cpp

GRAPH_TEST_SOURCES					:= tests/unit/graph/test_graph.cpp

CONTAINERS_TEST_SOURCES					:= tests/unit/containers/test_queue.cpp \
							   tests/unit/containers/test_stack.cpp

ALGORITMS_TEST_SOURCES					:= test/unit/algorithms/test_algorithms.cpp

COMMON_TEST_SOURCES						:=  $(MATRIX_TEST_SOURCES) \
											$(CONTAINERS_TEST_SOURCES) \
											$(GRAPH_TEST_SOURCES) \
											$(ALGORITMS_TEST_SOURCES)

# ----------------------------------------------------------------------------------------- Targets


.PHONY: all
all: test

.PHONY: help
help:
	@grep -E '^[a-zA-Z0-9 - _]+:.*#'  Makefile | sort | while read -r l; do \
	printf "\033[1;36m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done

build:
	$(CXX) $(CXXFLAGS) $(GRAPH_SOURCES) $(ALGORITMS_SOURCES) main.cpp -o build

# ------------------------------------------------------------------------------------- Application


# ------------------------------------------------------------------------------------------- Tests

.PHONY: test
test: # testing of all project sources
	$(CXX) $(CXXFLAGS) --coverage $(COMMON_TEST_SOURCES) \
	tests/unit/main.cpp -o test $(SYSFLAGS) && ./test

.PHONY: test_algorithms
test_algorithms: # testing of GraphAlgorithms class
	$(CXX) $(CXXFLAGS) --coverage $(ALGORITMS_TEST_SOURCES) $(ALGORITMS_SOURCES) \
	tests/unit/main.cpp -o test_algorithms $(SYSFLAGS) && ./test_algorithms

.PHONY: test_graph
test_graph: # testing of Graph class
	$(CXX) $(CXXFLAGS) --coverage $(GRAPH_TEST_SOURCES) $(GRAPH_SOURCES) \
	tests/unit/main.cpp -o test_graph $(SYSFLAGS) && ./test_graph

.PHONY: test_containers
test_containers: # testing of container classes
	$(CXX) $(CXXFLAGS) --coverage $(CONTAINERS_TEST_SOURCES) \
	tests/unit/main.cpp -o test_containers $(SYSFLAGS) && ./test_containers

.PHONY: test_matrix
test_matrix: # testing of Matrix class
	$(CXX) $(CXXFLAGS) --coverage $(MATRIX_TEST_SOURCES) \
	tests/unit/main.cpp -o test_matrix $(SYSFLAGS) && ./test_matrix

# ---------------------------------------------------------------------------------------- Archives

.PHONY: s21_graph
s21_graph: $(GRAPH_OBJECTS) # creatating a Graph class archive
	ar src s21_graph.a $? && rm -rf $?

$(GRAPH_OBJECTS): $(GRAPH_SOURCES)
	$(CXX) $(CXXFLAGS) -c $? -o $@

.PHONY: s21_graph_algorithms
s21_graph_algorithms: $(ALGORITMS_OBJECTS) # creating a GraphAlgorithm class archive
	ar src s21_graph_algorithms.a $? && rm -rf $?

$(ALGORITMS_OBJECTS): $(ALGORITMS_SOURCES)
	$(CXX) $(CXXFLAGS) -c $? -o $@

# -------------------------------------------------------------------------------------- 

.PHONY: boost_program_options
boost_program_options: # installing libboost-program-options-dev for console application
	sudo apt update && sudo apt install -y libboost-program-options-dev

.PHONY: install_doxygen
install_doxygen: # installing Doxygen
	sudo apt update && sudo apt-get doxygen

# ----------------------------------------------------------------------------------------- Linters

.PHONY: style
style: # checking code for Google style
	find . \( -name "*.h" -o -name "*.c" -o -name "*.hpp" -o -name "*.cpp" \) -print0 \
	| xargs --null clang-format -n --style=Google

cppcheck:
	cppcheck --enable=all --force --suppress=missingIncludeSystem --language=c++ \
	$(GRAPH_SOURCES) $(ALGORITMS_SOURCES) 

.PHONY: leaks
leaks: test # checking code for leaks using Valgrind utility
	valgrind --tool=memcheck --track-fds=yes --quiet --trace-children=yes \
	--track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test

# ------------------------------------------------------------------------------- Abstracts Targets

clean:
	- rm build
	- rm test
	- rm test_graph
	- rm test_containers
	- rm *.dot
	- rm -rf gcov_report
	- rm *.gcno *.gcda *.info
	- rm -rf dvi/doxygen

rebuild: clean all
