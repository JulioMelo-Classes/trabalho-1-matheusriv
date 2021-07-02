/*!
 *  @file OtherFunctions.cpp
 *  @brief General Functions
 *
 *  Source with the auxiliary functions of the Keno Game
 */

#include <iostream>
#include <string>
#include <algorithm>

#include "OtherFunctions.hpp"

void printPayoffTable(std::vector<std::vector<float>> &payoff, int NR, int size) 
{
    std::cout << "\t----------+-----------\n"
              << "\tHits      | Retorno\n"
              << "\t----------+-----------\n";
    // Print Table Content
    for(auto i{0}; i <= NR; i++){
        std::cout << "\t        " << i << " | " << payoff[size-1][i] << "\n";
    }

}

int partition (int *arr, int low, int high) { 
    // pivot 
    int pivot = arr[high]; 
     // Index of smaller element and indicates the right position of pivot found so far
    int i = (low - 1);

    for(int j = low; j <= high - 1; j++) { 
        // If current element is smaller than the pivot 
        if(arr[j] < pivot){ 
            i++; // increment index of smaller element 
            std::swap(arr[i], arr[j]); 
        } 
    } 
    std::swap(arr[i + 1], arr[high]); 
    return (i + 1); 
} 

void quickSortAlgorithm (int *arr, int low, int high) { 
    if(low < high){ 
        /* pi is partitioning index, arr[p] is now 
        at right place */
        int pi = partition(arr, low, high); 

        // Separately sort elements before partition and after partition 
        quickSortAlgorithm(arr, low, pi - 1); 
        quickSortAlgorithm(arr, pi + 1, high); 
    } 
} 

void quickSort (int *arr, int size){
    quickSortAlgorithm(arr, 0, size-1);
}

