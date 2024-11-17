// Copyright 2024 stranger

#include <gtest/gtest.h>

#include "./../../../src/containers/queue/queue.hpp"

TEST(Queue, init){
    {
        // Arrange
        s21::Queue<int> queue;

        // Assert
        ASSERT_EQ(queue.empty(), true);
        ASSERT_EQ(queue.size(), 0);
    }

    {
        // Arrange
        s21::Queue<int> queue{1, 2, 3, 4, 5};

        // Assert
        ASSERT_EQ(queue.empty(), false);
        ASSERT_EQ(queue.size(), 5);        
    }
}

TEST(Queue, front){
    {
        // Arrange
        s21::Queue<int> queue;

        // Assert
        ASSERT_EQ(queue.front(), 0);
    }

    {
        // Arrange
        s21::Queue<int> queue{1, 2, 3, 4, 5};

        // Assert
        ASSERT_EQ(queue.front(), 1);       
    }
}

TEST(Queue, back){
    {
        // Arrange
        s21::Queue<int> queue;

        // Assert
        ASSERT_EQ(queue.back(), 0);
    }

    {
        // Arrange
        s21::Queue<int> queue{1, 2, 3, 4, 5};

        // Assert
        ASSERT_EQ(queue.back(), 5);       
    }
}

TEST(Queue, pop){
    {
        // Arrange
        s21::Queue<int> queue;

        // Assert
        ASSERT_EQ(queue.pop(), 0);
        ASSERT_EQ(queue.empty(), true);
        ASSERT_EQ(queue.size(), 0);
    }

    {
        // Arrange
        s21::Queue<int> queue{1, 2, 3, 4, 5};

        // Act
        for(int i = 0; i < 5; ++i){
            if(queue.pop() != i + 1){ i = 5; }
        }

        // Assert
        ASSERT_EQ(queue.empty(), true);
        ASSERT_EQ(queue.size(), 0);    
    }
}

TEST(Queue, push){
    {
        // Arrange
        s21::Queue<int> queue;

        // Act
        for(int value = 0; value < 100; ++value){
            queue.push(value);

            if(queue.front() != 0 || queue.back() != value){ value = 100; }
        }

        // Assert
        EXPECT_EQ(queue.empty(), false);
        EXPECT_EQ(queue.size(), 100);
    }
}

TEST(Queue, clear){
    {
        // Arrange
        s21::Queue<int> queue{1, 2, 3, 4, 5};

        // Act
        queue.clear();

        // Assert
        EXPECT_EQ(queue.empty(), true);
        EXPECT_EQ(queue.size(), 0);
    }
}