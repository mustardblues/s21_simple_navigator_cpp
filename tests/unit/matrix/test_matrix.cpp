// Copyright 2024 stranger

#include <gtest/gtest.h>

#include "./../../../src/matrix/matrix.hpp"

TEST(Matrix, init){
    {
        // Arrange
        s21::Matrix<int> matrix;

        // Assert
        ASSERT_EQ(matrix.rows(), 0);
        ASSERT_EQ(matrix.columns(), 0);
        ASSERT_EQ(matrix.capacity(), 0);
        ASSERT_EQ(matrix.begin(), nullptr);
        ASSERT_EQ(matrix.end(), nullptr);
    }

    {
        // Arrange
        s21::Matrix<int> matrix(100, 100);

        // Assert
        ASSERT_EQ(matrix.rows(), 100);
        ASSERT_EQ(matrix.columns(), 100);
        ASSERT_EQ(matrix.capacity(), 10000);
        ASSERT_NE(matrix.begin(), nullptr);
        ASSERT_NE(matrix.end(), nullptr);
    }

    {
        // Arrange
        s21::Matrix<int> matrix(100, 100);

        matrix(0) = 1;
        matrix(10) = 2;
        matrix(20) = 3;
        matrix(30) = 4;
        matrix(40) = 5;
        matrix(50) = 6;
        matrix(60) = 7;
        matrix(70) = 8;
        matrix(80) = 9;
        matrix(90) = 10;

        s21::Matrix<int> copy(matrix);

        // Assert
        ASSERT_EQ(copy.rows(), 100);
        ASSERT_EQ(copy.columns(), 100);
        ASSERT_EQ(copy.capacity(), 10000);
        ASSERT_TRUE(std::equal(matrix.begin(), matrix.end(), copy.begin()));
    }

    {
        // Arrange
        s21::Matrix<int> matrix(100, 100);

        matrix(0) = 1;
        matrix(10) = 2;
        matrix(20) = 3;
        matrix(30) = 4;
        matrix(40) = 5;
        matrix(50) = 6;
        matrix(60) = 7;
        matrix(70) = 8;
        matrix(80) = 9;
        matrix(90) = 10;

        s21::Matrix<int> result(matrix);
        s21::Matrix<int> copy(std::move(matrix));

        // Assert
        ASSERT_EQ(copy.rows(), 100);
        ASSERT_EQ(copy.columns(), 100);
        ASSERT_EQ(copy.capacity(), 10000);
        ASSERT_TRUE(std::equal(result.begin(), result.end(), copy.begin()));

        ASSERT_EQ(matrix.rows(), 0);
        ASSERT_EQ(matrix.columns(), 0);
        ASSERT_EQ(matrix.capacity(), 0);
    }
}

TEST(Matrix, operators){
    {
        // Arrange
        s21::Matrix<int> matrix(100, 100);

        matrix(0) = 1;
        matrix(10) = 2;
        matrix(20) = 3;
        matrix(30) = 4;
        matrix(40) = 5;
        matrix(50) = 6;
        matrix(60) = 7;
        matrix(70) = 8;
        matrix(80) = 9;
        matrix(90) = 10;

        s21::Matrix<int> copy;

        // Act
        copy = matrix;

        // Assert
        ASSERT_EQ(copy.rows(), 100);
        ASSERT_EQ(copy.columns(), 100);
        ASSERT_EQ(copy.capacity(), 10000);
        ASSERT_TRUE(std::equal(matrix.begin(), matrix.end(), copy.begin()));
    }

    {
        // Arrange
        s21::Matrix<int> matrix(100, 100);

        matrix(0) = 1;
        matrix(10) = 2;
        matrix(20) = 3;
        matrix(30) = 4;
        matrix(40) = 5;
        matrix(50) = 6;
        matrix(60) = 7;
        matrix(70) = 8;
        matrix(80) = 9;
        matrix(90) = 10;

        s21::Matrix<int> copy(10, 10);

        // Act
        copy = matrix;

        // Assert
        ASSERT_EQ(copy.rows(), 100);
        ASSERT_EQ(copy.columns(), 100);
        ASSERT_EQ(copy.capacity(), 10000);
        ASSERT_TRUE(std::equal(matrix.begin(), matrix.end(), copy.begin()));
    }

    {
        // Arrange
        s21::Matrix<int> matrix(100, 100);

        matrix(0) = 1;
        matrix(10) = 2;
        matrix(20) = 3;
        matrix(30) = 4;
        matrix(40) = 5;
        matrix(50) = 6;
        matrix(60) = 7;
        matrix(70) = 8;
        matrix(80) = 9;
        matrix(90) = 10;

        s21::Matrix<int> result(matrix);

        // Act
        matrix = matrix;

        // Assert
        ASSERT_EQ(matrix.rows(), 100);
        ASSERT_EQ(matrix.columns(), 100);
        ASSERT_EQ(matrix.capacity(), 10000);
        ASSERT_TRUE(std::equal(result.begin(), result.end(), matrix.begin()));
    }

    {
        // Arrange
        s21::Matrix<int> matrix(100, 100);

        matrix(0) = 1;
        matrix(10) = 2;
        matrix(20) = 3;
        matrix(30) = 4;
        matrix(40) = 5;
        matrix(50) = 6;
        matrix(60) = 7;
        matrix(70) = 8;
        matrix(80) = 9;
        matrix(90) = 10;

        s21::Matrix<int> result(matrix);
        s21::Matrix<int> copy;

        // Act
        copy = std::move(matrix);

        // Assert
        ASSERT_EQ(copy.rows(), 100);
        ASSERT_EQ(copy.columns(), 100);
        ASSERT_EQ(copy.capacity(), 10000);
        ASSERT_TRUE(std::equal(result.begin(), result.end(), copy.begin()));

        ASSERT_EQ(matrix.rows(), 0);
        ASSERT_EQ(matrix.columns(), 0);
        ASSERT_EQ(matrix.capacity(), 0);
    }

        {
        // Arrange
        s21::Matrix<int> matrix(100, 100);

        matrix(0) = 1;
        matrix(10) = 2;
        matrix(20) = 3;
        matrix(30) = 4;
        matrix(40) = 5;
        matrix(50) = 6;
        matrix(60) = 7;
        matrix(70) = 8;
        matrix(80) = 9;
        matrix(90) = 10;

        s21::Matrix<int> result(matrix);
        s21::Matrix<int> copy(10, 10);

        // Act
        copy = std::move(matrix);

        // Assert
        ASSERT_EQ(copy.rows(), 100);
        ASSERT_EQ(copy.columns(), 100);
        ASSERT_EQ(copy.capacity(), 10000);
        ASSERT_TRUE(std::equal(result.begin(), result.end(), copy.begin()));

        ASSERT_EQ(matrix.rows(), 0);
        ASSERT_EQ(matrix.columns(), 0);
        ASSERT_EQ(matrix.capacity(), 0);
    }
}