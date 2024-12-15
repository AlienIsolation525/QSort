#pragma once
#include "requestHandler.h"
#include <memory>
#include <future>
class QuickSort
{
public:
    QuickSort();
    void setMT_on();
    void setMT_off();
    void quicksort(int* array, long left, long right);
    void quicksort_mt(int* array, long left, long right, std::shared_ptr<std::promise<void>> promise);
    void check(int* test, int arrsize);
private:
    bool make_thread;
};