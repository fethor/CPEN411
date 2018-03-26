#include <stdio.h>
#include <string.h>




typedef struct BranchDistance {
	int distance;
	int count;
	struct BranchDistance *pointer;
}BranchDistance;

void printOutput(BranchDistance* ToBeRead);
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
	
*/

/*
//used to intialize so that all of function can use
static struct stat_stat_t* DataPoints

//put into the begininng of main() to intialize the first Data in the stat_stat_t array

struct stat_sdb_t* Data = stat_new();
DataPoints = stat_reg_int(Data, "Zero", "Beginning of Data", 0, 0, "NotImportant");

//using functions provided

struct stat_stat_t* newData;


*/	

/*
//to count for Part 2 (I dont know if they need to be global)
static struct stat_stat_t* DataPoints;
static struct stat_sdb_t* Data;


	Data = stat_new();
	DataPoints = stat_reg_int(Data, "Zero", "Beginning of Data", 0, 0, "NotImportant");

	struct stat_stat_t* Reader = DataPoints;
	
	while(TRUE){
		if (*Reader->name == (char)IMM){
			Reader.stat_variant_t.stat_for_int_t.var = Reader.stat_variant_t.stat_for_int_t.var+1;
			break;
		}
		else{
			if (Reader->next == NULL){
				stat_reg_int(Data, IMM, "Amount of times", 1, 1, NULL);
				break;
			}
			else{
				Reader = Reader->next;
			}
		}
	}

*/

/*
printf("hullo");
	BranchDistance* ReaderData =Zero;

	Data = stat_new();
	
	while(TRUE){
	
		stat_reg_int(Data, ReaderData->distance, "Off and Freq", &ReaderData->count, ReaderData->count, NULL);

		if (ReaderData->pointer == NULL){
			break;
		}
		else{
			ReaderData = ReaderData->pointer;
		}	
	}
	//stat_print_stats(Data,stdout);

*/

/*
	BranchDistance* ReaderData = malloc(sizeof(ReaderData)); // =Zero;
	ReaderData->distance = 0;
	ReaderData->count = 0;
	ReaderData->pointer = NULL;

	while(TRUE){
	
		//stat_reg_int(sdb, ReaderData->distance, "Off and Freq", &ReaderData->count, ReaderData->count, NULL);

		if (ReaderData->pointer == NULL){
			break;
		}
		else{
			ReaderData = ReaderData->pointer;
		}	
	}
*/

/*
//Adding data to stat to make histogram =============================================================
while (TRUE){
	if (Data[i][0] == IMM){
		Data[i][1] = Data[i][1]+1;
		int a;
		for(a = 0 ; a < 500 ; a++){
			printf("%d,%d \n", Data[a][0], Data[a][1]);
		}
		break;
	}
	else{
		if (Data[i+1][0] == 0){
			Data[i+1][0]= IMM;
			Data[i+1][1]= 1;
			
			break;
		}
		else{
			
			i++;
		}
	}

}
*/









		
