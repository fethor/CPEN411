#include <stdio.h>
#include <string.h>

void printOutput(void);
/*
struct BranchDistance {
	int distance;
	int count;
	struct BranchDistance *pointer;
}branchdistance;
*/
/*
  	while (readPointer->pointer != NULL){
		readPointer = readPointer->pointer;
   		printf("Offset: %d offset of instruction", readPointer->distance);
   		printf("Count: %d count of instruction offset", readPointer->count); 
  		
  	}

*/

/*
		struct BranchDistance* nextPointer = Zero;
		
		
		while ((nextPointer->pointer != NULL) || (&nextPointer == &Zero)){
			nextPointer = nextPointer->pointer;

						if (nextPointer->distance == IMM){
				nextPointer->count = nextPointer->count + 1;
				break;
			}
			else {
								if (nextPointer->pointer == NULL){
					struct BranchDistance* NewData = malloc(sizeof(branchdistance));
					nextPointer->pointer = NewData;
					NewData->distance = IMM;
					NewData->count = 1;
					NewData->pointer = NULL;
					nextPointer = NewData;
				}
				
			}
		}				
		
		
	}
*/