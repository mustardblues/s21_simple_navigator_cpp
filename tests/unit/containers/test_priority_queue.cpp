// Copyright 2024 stranger

#include <gtest/gtest.h>

#include "./../../../src/containers/priority_queue/priority_queue.hpp"

TEST(PriorityQueue, init){
    {
        // Arrange
        s21::PriorityQueue<int> queue;

        // Assert
        ASSERT_EQ(queue.empty(), true);
        ASSERT_EQ(queue.size(), 0);
    }

    {
        // Arrange
        s21::PriorityQueue<int> queue{5, 1, 2, 4, 5};

        // Assert
        ASSERT_EQ(queue.empty(), false);
        ASSERT_EQ(queue.size(), 5);

        ASSERT_EQ(queue.pop(), 1);        
        ASSERT_EQ(queue.pop(), 2);        
        ASSERT_EQ(queue.pop(), 4);        
        ASSERT_EQ(queue.pop(), 5);        
        ASSERT_EQ(queue.pop(), 5);        
    }
}

TEST(PriorityQueue, front){
    {
        // Arrange
        s21::PriorityQueue<int> queue;

        // Assert
        ASSERT_EQ(queue.front(), 0);
    }

    {
        // Arrange
        s21::PriorityQueue<int> queue{5, 1, 2, 4, 3};

        // Assert
        ASSERT_EQ(queue.front(), 1);       
    }
}

TEST(PriorityQueue, back){
    {
        // Arrange
        s21::PriorityQueue<int> queue;

        // Assert
        ASSERT_EQ(queue.back(), 0);
    }

    {
        // Arrange
        s21::PriorityQueue<int> queue{5, 1, 2, 4, 3};

        // Assert
        ASSERT_EQ(queue.back(), 5);       
    }
}

TEST(PriorityQueue, pop){
    {
        // Arrange
        s21::PriorityQueue<int> queue;

        // Assert
        ASSERT_EQ(queue.pop(), 0);
        ASSERT_EQ(queue.empty(), true);
        ASSERT_EQ(queue.size(), 0);
    }

    {
        // Arrange
        s21::PriorityQueue<int> queue{5, 1, 2, 4, 3};

        // Act
        for(int i = 0; i < 5; ++i){
            if(queue.pop() != i + 1){ i = 5; }
        }

        // Assert
        ASSERT_EQ(queue.empty(), true);
        ASSERT_EQ(queue.size(), 0);    
    }
}

TEST(PriorityQueue, push){
    {
        // Arrange
        s21::PriorityQueue<int> queue;

        // Act
        for(int value = 100; value != 0; --value){
            queue.push(value);

            if(queue.front() != value || queue.back() != 100){ value = 0; }
        }

        // Assert
        EXPECT_EQ(queue.empty(), false);
        EXPECT_EQ(queue.size(), 100);
    }
}

TEST(PriorityQueue, clear){
    {
        // Arrange
        s21::PriorityQueue<int> queue{5, 1, 2, 4, 3};

        // Act
        queue.clear();

        // Assert
        EXPECT_EQ(queue.empty(), true);
        EXPECT_EQ(queue.size(), 0);
    }
}