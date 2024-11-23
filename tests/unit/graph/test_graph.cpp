// Copyright 2024 stranger

#include <gtest/gtest.h>

#include "./../../../src/graph/graph.hpp"

inline constexpr std::initializer_list<unsigned int> list{
    0, 29, 20, 21, 16, 31, 100, 12, 4, 31, 18,
    29, 0, 15, 29, 28, 40, 72, 21, 29, 41, 12,
    20, 15, 0, 15, 14, 25, 81, 9, 23, 27, 13,
    21, 29, 15, 0, 4, 12, 92, 12, 25, 13, 25,
    16, 28, 14, 4, 0, 16, 94, 9, 20, 16, 22,
    31, 40, 25, 12, 16, 0, 95, 24, 36, 3, 37,
    100, 72, 81, 92, 94, 95, 0, 90, 101, 99, 84,
    12, 21, 9, 12, 9, 24, 90, 0, 15, 25, 13,
    4, 29, 23, 25, 20, 36, 101, 15, 0, 35, 18,
    31, 41, 27, 13, 16, 3, 99, 25, 35, 0, 38,
    18, 12, 13, 25, 22, 37, 84, 13, 18, 38, 0
};

TEST(Graph, init){
    {
        // Arrange
        s21::Graph graph;

        // Assert
        ASSERT_EQ(graph.length(), 0);
    }

    {
        // Arrange
        s21::Graph graph(100);

        // Assert
        ASSERT_EQ(graph.length(), 100);        
    }

    {
        // Arrange
        s21::Graph graph_1(100);
        s21::Graph graph_2(graph_1);

        // Assert
        ASSERT_EQ(graph_1, graph_2);  
    }

    {
        // Arrange
        s21::Graph graph_1(100);
        s21::Graph graph_2(std::move(graph_1));

        // Assert
        EXPECT_EQ(graph_1.length(), 0); 
        EXPECT_EQ(graph_2.length(), 100);        
    }
}

TEST(Graph, operators){
    {
        // Arrange
        s21::Graph graph;

        // Assert
        ASSERT_EQ(graph(10, 10), 0);
    }

    {
        // Arrange
        const s21::Graph graph;

        // Assert
        ASSERT_EQ(graph(10, 10), 0);
    }

    {
        // Arrange
        s21::Graph graph(2);

        // Act
        graph(0, 0) = 1;
        graph(0, 1) = 2;
        graph(1, 0) = 3;
        graph(1, 1) = 4;

        // Assert
        EXPECT_EQ(graph(0, 0), 1);
        EXPECT_EQ(graph(0, 1), 2);
        EXPECT_EQ(graph(1, 0), 3);
        EXPECT_EQ(graph(1, 1), 4);     
    }

    {
        // Arrange
        s21::Graph graph_1(2);

        graph_1(0, 0) = 1;
        graph_1(0, 1) = 2;
        graph_1(1, 0) = 3;
        graph_1(1, 1) = 4;

        s21::Graph graph_2(std::move(graph_1));

        // Assert
        EXPECT_EQ(graph_2(0, 0), 1);
        EXPECT_EQ(graph_2(0, 1), 2);
        EXPECT_EQ(graph_2(1, 0), 3);
        EXPECT_EQ(graph_2(1, 1), 4);     
    }

    {
        // Arrange
        s21::Graph graph_1(2);

        graph_1(0, 0) = 1;
        graph_1(0, 1) = 2;
        graph_1(1, 0) = 3;
        graph_1(1, 1) = 4;

        s21::Graph graph_2(graph_1);

        // Act
        bool is_equal{graph_1 == graph_2};

        // Assert
        EXPECT_EQ(is_equal, true);
    }

    {
        // Arrange
        s21::Graph graph_1(2);

        graph_1(0, 0) = 1;
        graph_1(0, 1) = 2;
        graph_1(1, 0) = 3;
        graph_1(1, 1) = 4;

        s21::Graph graph_2(std::move(graph_1));

        // Act
        bool is_equal{graph_1 == graph_2};

        // Assert
        EXPECT_EQ(is_equal, false);
    }

    {
        // Arrange
        s21::Graph graph_1(2);

        graph_1(0, 0) = 1;
        graph_1(0, 1) = 2;
        graph_1(1, 0) = 3;
        graph_1(1, 1) = 4;

        s21::Graph graph_2;

        // Act
        graph_2 = graph_1;

        // Assert
        ASSERT_EQ(graph_1, graph_2);
    }

    {
        // Arrange
        s21::Graph graph_1(2);

        graph_1(0, 0) = 1;
        graph_1(0, 1) = 2;
        graph_1(1, 0) = 3;
        graph_1(1, 1) = 4;

        s21::Graph graph_2(graph_1);
        s21::Graph graph_3;

        // Act
        graph_3 = std::move(graph_1);

        // Assert
        EXPECT_EQ(graph_1.length(), 0);
        EXPECT_EQ(graph_3, graph_2);
    }
}

TEST(Graph, begin){
    {
        // Arrange
        s21::Graph graph;

        // Assert
        EXPECT_EQ(graph.begin(), nullptr);
    }

    {
        // Arrange
        s21::Graph graph(1);

        graph(0, 0) = 1;

        // Assert
        EXPECT_EQ(*graph.begin(), 1);
    }
}

TEST(Graph, end){
    {
        // Arrange
        s21::Graph graph;

        // Assert
        EXPECT_EQ(graph.end(), nullptr);
    }

    {
        // Arrange
        s21::Graph graph(10);

        graph(9, 9) = 1;

        // Assert
        EXPECT_EQ(*(graph.end() - 1), 1);
    }
}

TEST(Graph, loadGraphFromFile){
    {
        // Arrange
        s21::Graph graph(10);

        // Act
        bool code = graph.loadGraphFromFile("");

        // Assert
        EXPECT_EQ(code, false);
        EXPECT_EQ(graph.length(), 10);
    }

    {
        // Arrange
        s21::Graph graph_1(11);

        std::copy(list.begin(), list.end(), graph_1.begin());

        s21::Graph graph_2(11);

        // Act
        bool code = graph_2.loadGraphFromFile("tests/unit/graph/adjacency_matrix.txt");

        // Assert
        EXPECT_EQ(code, true);
        EXPECT_EQ(graph_1, graph_2);
    }
}

TEST(Graph, exportGraphToDot){
    {
        // Arrange
        s21::Graph graph;

        // Act
        bool code = graph.exportGraphToDot<s21::GraphType::Undirected>("graph");

        // Assert
        EXPECT_EQ(code, false);
    }

    {
        // Arrange
        s21::Graph graph(11);

        std::copy(list.begin(), list.end(), graph.begin());

        // Act
        bool code = graph.exportGraphToDot<s21::GraphType::Undirected>("graph");

        // Assert
        EXPECT_EQ(code, true);
    }

    {
        // Arrange
        s21::Graph graph;

        // Act
        bool code = graph.exportGraphToDot<s21::GraphType::Directed>("graph");

        // Assert
        EXPECT_EQ(code, false);
    }

    {
        // Arrange
        s21::Graph graph(11);

        std::copy(list.begin(), list.end(), graph.begin());

        // Act
        bool code = graph.exportGraphToDot<s21::GraphType::Directed>("graph");

        // Assert
        EXPECT_EQ(code, true);
    }
}