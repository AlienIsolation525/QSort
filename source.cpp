#include <iostream>
#include "qSort.h"
#include "generateArray.h"
using namespace std;

const long arr_size = 1000000;
QuickSort Sort;
genArray genArr(arr_size);


int main()
{
    Sort.setMT_on();

    // MT sort
    // Generate array
    auto array = genArr.generate_array();
    time_t start, end;
    time(&start);

    // Sort and check result
    Sort.quicksort(array, 0, arr_size);
    Sort.check(array, arr_size);
    Sort.setMT_off();

    time(&end);
    double seconds = difftime(end, start);
    printf("MT sort \nElapsed time: %f seconds\n\n", seconds);

    // Single thread sort
    time(&start);
    Sort.quicksort(array, 0, arr_size);
    Sort.check(array, arr_size);
    time(&end);
    seconds = difftime(end, start);
    printf("Single thread sort \nElapsed time: %f seconds\n", seconds);

    return 0;
}