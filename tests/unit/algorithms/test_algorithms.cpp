// Copyright 2024 stranger

#include <gtest/gtest.h>

#include "./../../../src/algorithms/algorithms.hpp"

const s21::Graph graph_1("tests/unit/data/matrix_6_1.txt");
const s21::Graph graph_2("tests/unit/data/matrix_6_2.txt");
const s21::Graph graph_3("tests/unit/data/matrix_6_3.txt");
const s21::Graph empty;

TEST(GraphAlgorithms, depthFirstSearch){
    {
        // Arrange
        std::deque<unsigned int> path{1, 6, 3, 4, 5, 2};

        // Act
        std::deque<unsigned int> result = s21::GraphAlgorithms::depthFirstSearch(graph_1);

        // Assert
        ASSERT_EQ(result, path);
    }

    {
        // Arrange
        std::deque<unsigned int> path{3, 6, 1, 2, 5, 4};

        // Act
        std::deque<unsigned int> result = s21::GraphAlgorithms::depthFirstSearch(graph_1, 3);

        // Assert
        ASSERT_EQ(result, path);
    }

    {
        // Arrange
        std::deque<unsigned int> path{1, 3, 6, 2, 5, 4};

        // Act
        std::deque<unsigned int> result = s21::GraphAlgorithms::depthFirstSearch(graph_2);

        // Assert
        ASSERT_EQ(result, path);
    }

    {
        // Arrange
        std::deque<unsigned int> path{3, 6, 2, 5, 4};

        // Act
        std::deque<unsigned int> result = s21::GraphAlgorithms::depthFirstSearch(graph_2, 3);

        // Assert
        ASSERT_EQ(result, path);
    }

    {
        // Act
        std::deque<unsigned int> result = s21::GraphAlgorithms::depthFirstSearch(graph_1, 7);

        // Assert
        ASSERT_EQ(result.size(), 0);
    }

    {
        // Act
        std::deque<unsigned int> result = s21::GraphAlgorithms::depthFirstSearch(empty);

        // Assert
        ASSERT_EQ(result.size(), 0);
    }
}

TEST(GraphAlgorithms, breadthFirstSearch){
    {
        // Arrange
        std::deque<unsigned int> path{1, 2, 3, 6, 4, 5};

        // Act
        std::deque<unsigned int> result = s21::GraphAlgorithms::breadthFirstSearch(graph_1);

        // Assert
        ASSERT_EQ(result, path);
    }

    {
        // Arrange
        std::deque<unsigned int> path{3, 1, 2, 4, 6, 5};

        // Act
        std::deque<unsigned int> result = s21::GraphAlgorithms::breadthFirstSearch(graph_1, 3);

        // Assert
        ASSERT_EQ(result, path);
    }

    {
        // Arrange
        std::deque<unsigned int> path{1, 2, 3, 4, 5, 6};

        // Act
        std::deque<unsigned int> result = s21::GraphAlgorithms::breadthFirstSearch(graph_2);

        // Assert
        ASSERT_EQ(result, path);
    }

    {
        // Arrange
        std::deque<unsigned int> path{3, 6, 2, 4, 5};

        // Act
        std::deque<unsigned int> result = s21::GraphAlgorithms::breadthFirstSearch(graph_2, 3);

        // Assert
        ASSERT_EQ(result, path);

        s21::Graph graph;
    }

    {
        // Act
        std::deque<unsigned int> result = s21::GraphAlgorithms::breadthFirstSearch(graph_1, 7);

        // Assert
        ASSERT_EQ(result.size(), 0);
    }

    {
        // Act
        std::deque<unsigned int> result = s21::GraphAlgorithms::breadthFirstSearch(empty);

        // Assert
        ASSERT_EQ(result.size(), 0);
    }
}

TEST(GraphAlgorithms, getShortestPathBetweenVertices){
    {
        // Act
        int result = s21::GraphAlgorithms::getShortestPathBetweenVertices(graph_1, 5, 6);

        // Assert
        ASSERT_EQ(result, 3);
    }

    {
        // Act
        int result = s21::GraphAlgorithms::getShortestPathBetweenVertices(graph_2, 1, 5);

        // Assert
        ASSERT_EQ(result, 13);
    }

    {
        // Act
        int result = s21::GraphAlgorithms::getShortestPathBetweenVertices(graph_2, 6, 1);

        // Assert
        ASSERT_EQ(result, 0);
    }

    {
        // Act
        int result = s21::GraphAlgorithms::getShortestPathBetweenVertices(graph_3, 1, 5);

        // Assert
        ASSERT_EQ(result, 5);
    }

    {
        // Act
        int result = s21::GraphAlgorithms::getShortestPathBetweenVertices(graph_3, 4, 6);

        // Assert
        ASSERT_EQ(result, 6);
    }

        {
        // Act
        int result = s21::GraphAlgorithms::getShortestPathBetweenVertices(graph_3, 4, 3);

        // Assert
        ASSERT_EQ(result, 5);
    }

    {
        // Act
        int result = s21::GraphAlgorithms::getShortestPathBetweenVertices(graph_1, 1, 7);

        // Assert
        ASSERT_EQ(result, 0);
    }

    {
        // Act
        int result = s21::GraphAlgorithms::getShortestPathBetweenVertices(empty, 1, 6);

        // Assert
        ASSERT_EQ(result, 0);
    }
}

TEST(GraphAlgorithms, getShortestPathBetweenAllVertices){
    {
        // Arrange
        s21::Matrix<int> matrix(
            6, 6, 
            {
                0, 1, 1, 2, 2, 1,
                1, 0, 1, 1, 1, 2,
                1, 1, 0, 1, 2, 1,
                2, 1, 1, 0, 1, 2,
                2, 1, 2, 1, 0, 3,
                1, 2, 1, 2, 3, 0
            }
        );

        // Act
        s21::Matrix<int> result = s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(graph_1);

        // Assert
        ASSERT_EQ(result, matrix);
    }

    {
        int inf = static_cast<int>(s21::Constants::inf);

        // Arrange
        s21::Matrix<int> matrix{
            6, 6,
            {
                0, 5, 4, 7, 13, 5,
                inf, 0, inf, 2, 8, inf,
                inf, 4, 0, 6, 12, 1,
                inf, inf, inf, 0, inf, inf,
                inf, inf, inf, inf, 0, inf,
                inf, 3, inf, 5, 11, 0
            }
        };

        // Act
        s21::Matrix<int> result = s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(graph_2);

        // Assert
        ASSERT_EQ(result, matrix);
    }

    {
        // Arrange
        s21::Matrix<int> matrix(
            6, 6,
            {
                0, 4, 2, 3, 5, 3,
                4, 0, 3, 5, 4, 2,
                2, 3, 0, 5, 3, 1,
                3, 5, 5, 0, 7, 6,
                5, 4, 3, 7, 0, 2,
                3, 2, 1, 6, 2, 0
            }
        );

        // Act
        s21::Matrix<int> result = s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(graph_3);

        // Assert
        ASSERT_EQ(result, matrix);
    }

    {
        // Act
        s21::Matrix<int> result = s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(empty);

        // Assert
        ASSERT_EQ(result.capacity(), 0);
    }
}

TEST(GraphAlgorithms, getLeastSpanningTree){
    {
        // Arrange
        s21::Matrix<int> matrix(
            6, 6, 
            {
                0, 0, 2, 3, 0, 0,
                0, 0, 0, 0, 0, 2, 
                2, 0, 0, 0, 0, 1, 
                3, 0, 0, 0, 0, 0, 
                0, 0, 0, 0, 0, 2, 
                0, 2, 1, 0, 2, 0
            }
        );

        // Act
        s21::Matrix<int> result = s21::GraphAlgorithms::getLeastSpanningTree(graph_3);

        // Assert
        ASSERT_EQ(result, matrix);
    }

    {
        // Act
        s21::Matrix<int> result = s21::GraphAlgorithms::getLeastSpanningTree(empty);

        // Assert
        ASSERT_EQ(result.capacity(), 0);
    }
}