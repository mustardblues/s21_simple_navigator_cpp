// copyright 2024 stranger

#include <gtest/gtest.h>

#include "./../../../src/containers/stack/stack.hpp"

TEST(Stack, init){
    {
        // Arrange
        s21::Stack<int> stack;

        // Assert
        ASSERT_EQ(stack.empty(), true);
        ASSERT_EQ(stack.size(), 0);
    }

    {
        // Arrange
        s21::Stack<int> stack{1, 2, 3, 4, 5};

        // Assert
        ASSERT_EQ(stack.empty(), false);
        ASSERT_EQ(stack.size(), 5);
    }
}

TEST(Stack, top){
    {
        // Arrange
        s21::Stack<int> stack{1, 2, 3, 4, 5};

        // Assert
        ASSERT_EQ(stack.top(), 5);
    }
}

TEST(Stack, pop){
    {
        // Arrange
        s21::Stack<int> stack;

        // Assert
        ASSERT_EQ(stack.pop(), 0);
        ASSERT_EQ(stack.empty(), true);
        ASSERT_EQ(stack.size(), 0);
    }

    {
        // Arrange
        s21::Stack<int> stack{1, 2, 3, 4, 5};

        // Act
        for(int i = 0; i < 5; ++i){
            if(stack.pop() != 5 - i){ i = 5; }
        }

        // Assert
        ASSERT_EQ(stack.empty(), true);
        ASSERT_EQ(stack.size(), 0);
    }
}

TEST(Stack, push){
    {
        // Arrange
        s21::Stack<int> stack;

        // Act
        for(int value = 0; value < 100; ++value){
            stack.push(value);

            if(stack.top() != value){ value = 100; }
        }

        // Assert
        EXPECT_EQ(stack.empty(), false);
        EXPECT_EQ(stack.size(), 100);
    }
}

TEST(Stack, clear){
    {
        // Arrange
        s21::Stack<int> stack{1, 2, 3, 4, 5};

        // Act
        stack.clear();

        // Assert
        EXPECT_EQ(stack.empty(), true);
        EXPECT_EQ(stack.size(), 0);
    }
}