#include "pch.h"
#include "../LR3/Sort.h"
#include <gtest/gtest.h>


TEST(QuickSortTests, RegularTest)
{
    int arr[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

    quickSort(arr, arr + 9, [](int a, int b) { return a < b; });

    for (int i = 0; i < 10; i++)
        ASSERT_EQ(arr[i], i);
}

TEST(QuickSortTests, OneElement)
{
    int arr[1] = { 1 };

    quickSort(arr, arr, [](int a, int b) { return a < b; });

    ASSERT_EQ(arr[0], 1);
}

TEST(QuickSortTests, WrongBoundaries)
{
    int arr[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

    quickSort(arr + 9, arr, [](int a, int b) { return a < b; });

    for (int i = 0; i < 10; i++)
        ASSERT_EQ(arr[i], 9 - i);
}

TEST(InsertionSortTests, RegularTest)
{
    int arr[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

    insertionSort(arr, arr + 9, [](int a, int b) { return a < b; });

    for (int i = 0; i < 10; i++)
        ASSERT_EQ(arr[i], i);
}

TEST(InsertionSortTests, OneElement)
{
    int arr[1] = { 1 };

    insertionSort(arr, arr, [](int a, int b) { return a < b; });

    ASSERT_EQ(arr[0], 1);
}

TEST(InsertionSortTests, WrongBoundaries)
{
    int arr[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

    insertionSort(arr + 9, arr, [](int a, int b) { return a < b; });

    for (int i = 0; i < 10; i++)
        ASSERT_EQ(arr[i], 9 - i);
}

TEST(SortTests, RegularTest)
{
    int arr[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

    sort(arr, arr + 9, [](int a, int b) { return a < b; });

    for (int i = 0; i < 10; i++)
        ASSERT_EQ(arr[i], i);
}

TEST(SortTests, OneElement)
{
    int arr[1] = { 1 };

    sort(arr, arr, [](int a, int b) { return a < b; });

    ASSERT_EQ(arr[0], 1);
}

TEST(SortTests, WrongBoundaries)
{
    int arr[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

    sort(arr + 9, arr, [](int a, int b) { return a < b; });

    for (int i = 0; i < 10; i++)
        ASSERT_EQ(arr[i], 9 - i);
}