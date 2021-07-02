/*!
 *  @file HelperFunctions.hpp
 *  @brief Headers of other functions
 *
 *  Header with the auxiliary functions of the Keno Game 
 */

#ifndef OtherFunctions_hpp
#define OtherFunctions_hpp

#include <string>

/*! This function takes last element as pivot, places the pivot element at its correct position in sorted array, and places all smaller (smaller than pivot) to left of pivot and all greater elements to right of pivot 
    @param arr Array to be divided, 
    @param low Starting index, 
    @param high Ending index  
    @return True if the number is inside the array; false otherwise */
int partition (int *arr, int low, int high);

/*! The main function that implements QuickSort 
    @param arr Array to be sorted, 
    @param low Starting index, 
    @param high Ending index  */
void quickSortAlgorithm(int *arr, int low, int high);

/*! The quickSort friendly function to be called
    @param arr The vector to be sorted
    @param size The vector's size */
void quickSort(int *arr, int size);


#endif //OtherFunctions_hpp