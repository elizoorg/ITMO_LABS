#pragma once

#include <iostream>

constexpr int SORTING_ALGORITHM_CHANGE_BREAKPOINT = 10;

template<typename T>
void notCustomSwap(T* a, T* b) 
{
    T tmp(std::move(*a));
    *a = std::move(*b);
    *b = std::move(tmp);
}

template<typename T, typename Comparator>
void insertionSort(T* first, T* last, Comparator cmp) 
{
    for (T* cur = first + 1; cur <= last; cur++)
    {
        T* spot = cur;
        T tmp = std::move(*cur);
        while (spot > first && cmp(tmp, *(spot - 1))) 
        {
            *spot = std::move(*(spot - 1));
            spot--;
        }
        *spot = std::move(tmp);
    }
}

template<typename T, typename Comparator>
T* getPivot(T* first, T* last, Comparator cmp)
{
    T* middle = first + (last - first) / 2;
    if (cmp(*first, *last))
    {
        if (cmp(*middle, *first))
            return first;
        else if (cmp(*middle, *last))
            return middle;
        else
            return last;
    }
    else
    {
        if (cmp(*first, *middle))
            return first;
        else if (cmp(*last, *middle))
            return middle;
        else
            return last;
    }
}

template<typename T, typename Comparator>
T* partition(T* first, T* last, T* pivot, Comparator cmp) 
{
    notCustomSwap(last, pivot);
    pivot = last;
    last--;
    do
    {
        while (cmp(*first, *pivot))
            first++;

        while (cmp(*pivot, *last))
            last--;

        if (first < last) 
            notCustomSwap(first, last);
    } while (first < last);

    notCustomSwap(first, pivot);

    return first;
}

template<typename T, typename Comparator>
void quickSort(T* first, T* last, Comparator cmp)
{
    if (last <= first)
        return;

    T* pivot = partition(first, last, getPivot(first, last, cmp), cmp);

    quickSort(first, pivot - 1, cmp);
    quickSort(pivot + 1, last, cmp);
}

template<typename T, typename Comparator>
void sort(T* first, T* last, Comparator cmp) 
{
    if (first >= last)
        return;

    if (last - first > SORTING_ALGORITHM_CHANGE_BREAKPOINT)
    {
        T* pivot = partition(first, last, getPivot(first, last, cmp), cmp);

        quickSort(first, pivot - 1, cmp);
        quickSort(pivot + 1, last, cmp);
    }
    else
        insertionSort(first, last, cmp);
}