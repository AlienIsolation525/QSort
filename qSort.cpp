#include "qSort.h"

QuickSort::QuickSort()
{
    setMT_off();
}

void QuickSort::setMT_off()
{
    make_thread = false;
}

void QuickSort::setMT_on()
{
    make_thread = true;
}

void QuickSort::quicksort(int* array, long left, long right)
{
    if (left >= right)
    {
        return;
    }

    long left_bound = left;
    long right_bound = right;
    long middle = array[(left_bound + right_bound) / 2];

    do {
        while (array[left_bound] < middle)
        {
            left_bound++;
        }
        while (array[right_bound] > middle)
        {
            right_bound--;
        }

        if (left_bound <= right_bound)
        {
            std::swap(array[left_bound], array[right_bound]);
            left_bound++;
            right_bound--;
        }
    } while (left_bound <= right_bound);

    auto promise = std::make_shared<std::promise<void>>();
    if (make_thread && (right_bound - left > 10000))
    {
        ReqHandler rh;
        rh.push_task(&QuickSort::quicksort_mt, this, std::ref(array), left, right_bound, promise);
        quicksort(array, left_bound, right);
    }
    else
    {
        quicksort(array, left, right_bound);
        quicksort(array, left_bound, right);
    }
}

void QuickSort::quicksort_mt(int* array, long left, long right, std::shared_ptr<std::promise<void>> promise)
{
    std::future<void> f = std::async(std::launch::async, [&]() { quicksort(array, left, right); });
    f.wait();
    promise->set_value();
}

void QuickSort::check(int* test, int arrsize)
{
    std::cout << "checkin...\n";
    bool flag = true;
    for (long i = 0; i < arrsize - 1; ++i)
    {
        if (test[i] > test[i + 1])
        {
            flag = false;
            break;
        }
    }
    if (flag) std::cout << "quick sort completed succesfully\n";
    else std::cout << "quick sort error\n";
}