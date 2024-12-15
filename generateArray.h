#pragma once
#include <chrono>
#include <iostream>


class genArray {

public :
	genArray(int arrSize) {
        this->size = arrSize;
	}
	~genArray() {
		delete[] arr;
	}

    int* generate_array() {
        time_t start, end;
        int* arr;
        // Filling array with random numbers
        time(&start);

        arr = new int[size];
        for (int i=0; i < size; i++)
            arr[i] = (rand() % 100) + 1;

        time(&end);
        double seconds = difftime(end, start);
        printf("Generating array \nElapsed time: %f seconds\n", seconds);

        return arr;

    }

private:
	int* arr;
	int size;
};