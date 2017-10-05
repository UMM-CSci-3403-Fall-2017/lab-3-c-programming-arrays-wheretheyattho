#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "mergesort.h"
#include "array_merge.h"



//Merge arrays of different lengths into one sorted array
//with no duplicates
int* array_merge(int num_arrays, int* sizes, int** values)
{
	//Count elements from all input arrays
	int totalSize = 0;
	for(int i = 0; i < num_arrays; i++)
	{
		totalSize += sizes[i];
	}
	
	//Allocate space to hold all of the values
	//in order to sort
	int *holderArray = (int*)calloc(totalSize, sizeof(int));
	int holderCtr = 0;
	int holderSize = 0;

	//Count number of items that arent duplicates and only add those ones
	//to the holder array
	for(int i = 0; i < num_arrays; i++)
	{
		for(int j = 0; j < sizes[i]; j++)
		{
			//If selected value is in the array already, skip it
			bool inArray = false;
			for(int t = 0; t < holderCtr; t++)
			{
				if( holderArray[t] == values[i][j] )
				{
					inArray = true;
					break;
				}
			}

			if(!inArray)
			{
				holderArray[holderCtr] = values[i][j];
				holderCtr++;
				holderSize++;
			}
			
		}
	}
	//Sort the array
	mergesort(holderSize, holderArray);	

	//Create a new array of the size of non-duplicate elements in holderArray
	//with 1 extra space for number of items in array.
	int *returnArray = (int*)calloc(holderSize + 1, sizeof(int));
	returnArray[0] = holderSize;

	//copy over values from holderArray into returnArray
	for(int i = 1; i < holderSize + 1; i++)
	{
		returnArray[i] = holderArray[i - 1];
	}
	//clean up extra memory
	free(holderArray);
	return returnArray;
}


void mergeRanges(int values[], int low, int mid, int high){
  int a, b, c, length;
        length = high - low;
        int *result = (int*) calloc(length, sizeof(int));
        a = low;
        b = mid;
        c = 0;
      
        while((a < mid) && (b < high)){
                if(values[a] < values[b]){
                        result[c] = values[a];
                        ++a;
                } else {
                        result[c] = values[b];
                        ++b;
                }
                ++c;
        }

        while(a < mid){
                result[c] = values[a];
                ++c;
                ++a;
        }

        while(b < high){
                result[c] = values[b];
                ++c;
                ++b;
        }

        
        for(int i = 0; i < length; ++i){
	  values[i + low] = result[i];
        }

	free(result);
}

void mergesortRange(int values[], int start, int end){
	int rangeSize = end - start;
	
	if(rangeSize > 1){
		int midPoint = (start + end) / 2;
		mergesortRange(values, start, midPoint);
		mergesortRange(values, midPoint, end);
		mergeRanges(values, start, midPoint, end);
	}
}

void mergesort(int size, int values[]){
	mergesortRange(values, 0, size);
}
