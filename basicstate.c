#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to compute the mean (average) of values
double Mean(float *data, int size) {
    double sum = 0.0;

    for (int i = 0; i < size; i++) {
        sum += data[i];
    }

    return sum / size;
}



// Function to compute the standard deviation of values
double StandardDeviation(float *data, int size) {
    double mean = Mean(data, size);
    double sumSquaredDiff = 0.0;

    for (int i = 0; i < size; i++) {
        sumSquaredDiff += pow(data[i] - mean, 2);
    }

    return sqrt(sumSquaredDiff / size);
}

// Function to compute the median of values
double Median(float *data, int size) {
    // Sort the array 
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (data[j] > data[j + 1]) {
                // Swap
                float temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }

    // Calculate the median
    if (size % 2 == 0) {
        return (data[size / 2 - 1] + data[size / 2]) / 2.0;
    } else {
        return data[size / 2];
    }
}

// Function to dynamically allocate memory for the array
float *allocateMemory(int *capacity) {
    // Allocate memory for the array
    float *data = (float *)malloc((*capacity) * sizeof(float));

    if (!data) {
        printf("failed.\n");
        exit(1);
    }

    return data;
}

// Function to read data from the file and populate the array
int ReadDataFromFile(char *fileName, float **data, int *size, int *capacity) {
    FILE *file = fopen(fileName, "r");

    if (!file) {
        printf("Error opening file: %s\n", fileName);
        return 0;
    }

    float value;
    while (fscanf(file, "%f", &value) == 1) {
        // Check if reallocation is needed
        if (*size == *capacity) {
            *capacity *= 2;
            *data = realloc(*data, (*capacity) * sizeof(float));

            if (!(*data)) {
                printf("Memory reallocation failed.\n");
                exit(1);
            }
        }

        // Store the value in the array
        (*data)[*size] = value;
        (*size)++;
    }

    fclose(file);
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    char *fileName = argv[1];
    float *data = NULL;
    int size = 0, capacity = 20;

    // Allocate memory for the array
    data = allocateMemory(&capacity);

    // Read data from the file
    int success = ReadDataFromFile(fileName, &data, &size, &capacity);

    if (!success) {
        printf("Error reading data from file.\n");
        return 1;
    }

    // Compute 
    double mean = Mean(data, size);
    double median = Median(data, size);
    double stdDev = StandardDeviation(data, size);
    printf("Results:\n");
    printf("--------\n");
    printf("Num values: %16d\n", size);
    printf("      mean: %16.3lf\n", mean);
    printf("    median: %16.3lf\n", median);
    printf("    stddev: %16.3lf\n", stdDev);
    printf("Unused array capacity: %3d\n", capacity - size);

    // Free dynamically allocated memory
    free(data);

    return 0;
}
