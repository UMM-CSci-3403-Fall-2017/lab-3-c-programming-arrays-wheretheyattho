#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "mergesort.h"


void mergeRanges(int toSort[], int low, int mid, int high){
  int a, b, c, length;
        length = high - low;
        int *result = (int*) calloc(length, sizeof(int));
        a = low;
        b = mid;
        c = 0;
      
        while((a < mid) && (b < high)){
                if(toSort[a] < toSort[b]){
                        result[c] = toSort[a];
                        ++a;
                } else {
                        result[c] = toSort[b];
                        ++b;
                }
                ++c;
        }

        while(a < mid){
                result[c] = toSort[a];
                ++c;
                ++a;
        }

        while(b < high){
                result[c] = toSort[b];
                ++c;
                ++b;
        }

        
        for(int i = 0; i < length; ++i){
	  toSort[i + low] = result[i];
        }

	free(result);
}

void mergesortRange(int toSort[], int start, int end){
	int rangeSize = end - start;
	
	if(rangeSize > 1){
		int midPoint = (start + end) / 2;
		mergesortRange(toSort, start, midPoint);
		mergesortRange(toSort, midPoint, end);
		mergeRanges(toSort, start, midPoint, end);
	}
}

void mergesort(int size, int toSort[]){
	mergesortRange(toSort, 0, size);
}
