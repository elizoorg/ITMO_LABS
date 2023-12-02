#include <iostream>
#include <fstream>
#include "Sort.h"
#include <Windows.h>

constexpr int CYCLES = 100000000;
constexpr int LENGTH = 20;
int main()
{
    int arr[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    
    for (auto iter : arr)
        std::cout << iter << " ";
    std::cout << std::endl;
    
    insertionSort(arr, arr + 9, [](int a, int b) { return a < b; });
    //quickSort(arr, arr + 9, [](int a, int b) { return a < b; });
    
    for (auto iter : arr)
        std::cout << iter << " ";
    std::cout << std::endl;
    
    //return 0;

    int a[LENGTH];
    LARGE_INTEGER StartingTime, EndingTime, TotalTime;
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    double PCFreq = double(frequency.QuadPart) / 1000;

    std::ofstream fout("quickSort.txt", std::ios_base::out | std::ios_base::trunc);
    fout << "array_len, time" << std::endl;

    auto comparator = [](int a, int b) { return a < b; };

    for (int arrayLength = 1; arrayLength <= LENGTH; arrayLength++) 
    {
        std::cout.width(4);
        std::cout << arrayLength << " : ";
        TotalTime.QuadPart = 0;
        for (int cycle = 0; cycle < CYCLES; cycle++) 
        {
            for (int i = 0; i < arrayLength; i++)
                a[i] = arrayLength - i;

            QueryPerformanceCounter(&StartingTime);
            quickSort(a, a + arrayLength - 1, comparator);
            QueryPerformanceCounter(&EndingTime);
            if (cycle >= CYCLES * 0.1)
                TotalTime.QuadPart += EndingTime.QuadPart - StartingTime.QuadPart;
        }
        fout << arrayLength << "," << TotalTime.QuadPart / PCFreq / (CYCLES * 0.9) << std::endl;
        std::cout << TotalTime.QuadPart / PCFreq / (CYCLES * 0.9) << "ms\n";
    }
    fout.close();

    fout.open("insertionSort.txt", std::ios_base::out | std::ios_base::trunc);

    fout << "array_len, time" << std::endl;

    for (int arrayLength = 1; arrayLength <= LENGTH; arrayLength++) 
    {
        std::cout.width(4);
        std::cout << arrayLength << " : ";
        TotalTime.QuadPart = 0;
        for (int cycle = 0; cycle < CYCLES; cycle++) 
        {
            for (int i = 0; i < arrayLength; i++)
                a[i] = arrayLength - i;

            QueryPerformanceCounter(&StartingTime);
            insertionSort(a, a + arrayLength - 1, comparator);
            QueryPerformanceCounter(&EndingTime);
            if (cycle >= CYCLES * 0.1)
                TotalTime.QuadPart += EndingTime.QuadPart - StartingTime.QuadPart;
        }
        fout << TotalTime.QuadPart / PCFreq / (CYCLES * 0.9) << std::endl;
        std::cout << TotalTime.QuadPart / PCFreq / (CYCLES * 0.9) << "ms\n";
    }
    fout.close();
}