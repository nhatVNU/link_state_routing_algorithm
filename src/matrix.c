#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Python.h>
#include <numpy/arrayobject.h>
#include "matrix.h"
// #include "graph.h"

/**
 * It reads a matrix from a file
 * 
 * @param size the size of the matrix
 * 
 * @return matrix
 */
int** readMatrixFromFile(int *size)
{
    char filename[256];
    printf("Enter filename: ");
    scanf("%s", filename);
    char path[256] = "testfile/";
    strcat(path, filename);
    FILE *infile = fopen(path, "r");
    fscanf(infile, "%d", size);
    int** matrix = (int **) malloc((*size) * sizeof(int *));
    for(int i = 0; i < (*size); ++i) {
        matrix[i] = (int *) malloc((*size) * sizeof(int));
        for(int j = 0; j < (*size); ++j) {
            fscanf(infile, "%d", &matrix[i][j]);
        }
    }
    fclose(infile);
    return matrix;
}

/**
 * It frees the memory allocated for the matrix
 * 
 * @param matrix The matrix to be freed.
 * @param size The size of the matrix.
 * @return None
 */
void freeMemory(int **matrix, int size)
{
    for(int i = 0; i < size; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

/**
 * Convert 2D C++ array to a NumPy array
 * 
 * @param cppMatrix The input matrix in C++
 * @param size The size of the matrix.
 * 
 * @return NumPy array
 */
PyObject *convertcppMatrix2pyMatrix(int **cppMatrix, int size)
{
    // Create a NumPy array of the same size as the input array
    npy_intp dims[2] = {size, size};
    import_array();
    PyObject *pyArray = PyArray_SimpleNew(2, dims, NPY_INT);
    if(pyArray == NULL){
        printf("Error: failed to allocate memory for NumPy array\n");
        return NULL;
    }
    // Copy the data from the input array to the NumPy array
    int *pyData = (int *)PyArray_DATA((PyArrayObject *)pyArray);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(pyData + i*size + j) = cppMatrix[i][j];
        }
    }

    // Return the NumPy array
    return pyArray;
}