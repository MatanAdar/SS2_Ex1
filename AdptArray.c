#include <stdio.h>
#include <stdlib.h>
#include "AdptArray.h"


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

   PElement* newpElemArr;
	if (arr == NULL)
		return FAIL;

    if(PnewElement ==NULL){
        return FAIL;
    }

	if (index >= arr->size)
	{
// Extend Array
        newpElemArr = (PElement*)calloc(index+1,sizeof(PElement));
		if (newpElemArr == NULL){
			return FAIL;
        }
        for(int i=0; i<arr->size;i++){
            if(arr -> ElemArray[i]!=NULL){
                newpElemArr[i]=arr->ElemArray[i];
            }
        }
		free(arr->ElemArray);
		arr->ElemArray = newpElemArr;
	}

	// // Delete Previous Elem
    if(arr->ElemArray[index]!=NULL){
	    arr->DelFunc((arr->ElemArray[index]));
    }
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

    for(int i=0;i< arr->size; i++){
        if(arr->ElemArray[i]!=NULL){
            arr -> PrintFunc(arr->ElemArray[i]);
        }
    }

}


