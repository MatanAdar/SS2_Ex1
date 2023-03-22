#include <stdio.h>
#include <stdlib.h>
#include "AdptArray.h"


// I got help from the solution from Moad A test of SS1 course 


typedef struct AdptArray_{

    PElement *ElemArray;
    int size;

    DEL_FUNC DelFunc;
    COPY_FUNC CopyFunc;
    PRINT_FUNC PrintFunc;

}AdptArray, *PAdptArray;


PAdptArray CreateAdptArray(COPY_FUNC CopyFunc, DEL_FUNC DelFunc, PRINT_FUNC PrintFunc){
    PAdptArray new =(PAdptArray)malloc(sizeof(AdptArray));
    if(!new){
        return NULL;
    }
    new ->size =0;
    new -> ElemArray = NULL;
    new -> CopyFunc =CopyFunc;
    new -> DelFunc = DelFunc;
    new -> PrintFunc = PrintFunc;

    return new;
}

void DeleteAdptArray(PAdptArray arr){

    if (!arr){
        return;
    }
    
    int ArrSize= arr->size;

    for(int i=0;i<ArrSize;i++){
        if(arr->ElemArray[i]!=NULL){
            arr->DelFunc(arr->ElemArray[i]);
        }
    }
    free(arr->ElemArray);
    free(arr);

}

Result SetAdptArrayAt(PAdptArray arr, int index, PElement PnewElement){

	if (arr == NULL)
		return FAIL;

    if(PnewElement ==NULL){
        return FAIL;
    }

	if (index >= arr->size)
	{
    // Extend Array
        PElement* newpElemArr = (PElement*)calloc(index+1,sizeof(PElement));
		if (newpElemArr == NULL){
			return FAIL;
        }
        // insert to the new array each pelement from the ElemArray
        for(int i=0; i<arr->size;i++){
            if(arr -> ElemArray[i]!=NULL){
                newpElemArr[i]=arr->ElemArray[i];
            }
        }
        // Free the currect array
		free(arr->ElemArray);
        // Replace the current array with the new array
		arr->ElemArray = newpElemArr;
	}

	// Delete Previous Elem
    if(arr->ElemArray[index]!=NULL){
	    arr->DelFunc((arr->ElemArray[index]));
    }
    // Copy the new element to the array
    arr->ElemArray[index] = arr->CopyFunc(PnewElement);

	// Update Array Size
    if(index >= arr ->size){
        arr -> size = index+1;
    }

	return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray arr, int index){
    
    if(!arr){
        return NULL;
    }

    if(index < 0 || index > arr -> size){
        return NULL;
    }

    if(arr->ElemArray[index]!=NULL){
        return arr ->CopyFunc(arr->ElemArray[index]);
    }
    return NULL;       
}


int GetAdptArraySize(PAdptArray arr){

    if(!arr){
        return -1;
    }
    return arr->size;
}

void PrintDB(PAdptArray arr){

    if(!arr){
        return;
    }

    for(int i=0; i<arr->size; i++){
        if(arr->ElemArray[i]!=NULL){
            arr -> PrintFunc(arr->ElemArray[i]);
        }
    }

}


