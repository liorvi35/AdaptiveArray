/**
 * this file contains implementation for adaptive array
 * Assignment 1, Software Systems 2 course at Ariel University
 * @author Lior Vinman
 * @date 22/03/2023
*/

// including libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AdptArray.h"

/**
 * this structure represents an adaptive array where:
 * length - the size of the array
 * element - the element that will be held inside array
 * copy - copying function of element
 * delete - deleting function of element
 * print - printing function of element
*/
typedef struct AdptArray_
{
    int length;
    PElement *element;
    COPY_FUNC copy;
    DEL_FUNC delete;
    PRINT_FUNC print;
} AdptArray, *PAdptArray;


/**
 * this function create a new empty adaptive array
 * @param copy copy function for the element that will be held in array
 * @param delete delete function for the element that will be held in array
 * @param print print function for the element that will be held in array
 * @return pointer to new created adaptive array if succsessfull, else FAIL(=0)
*/
PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC delete, PRINT_FUNC print)
{
    if(copy == NULL || delete == NULL || print == NULL) // checking for arguments validation
    {
        return FAIL;
    }
    else
    {
        PAdptArray adaptive_array = NULL; // creating new pointer for adaptive array
        adaptive_array = (PAdptArray)calloc(1, sizeof(AdptArray)); // allocating memory for new adaptive array
        if (adaptive_array == NULL) // checking memory allocation
        {
            return FAIL;
        }

        // setting all struct defult fields
        adaptive_array->length = 0;
        adaptive_array->element = NULL;
        adaptive_array->copy = copy;
        adaptive_array->delete = delete;
        adaptive_array->print = print;

        return adaptive_array; // returning the new adaptive array pointer
    }
}

/**
 * this function deletes adaptive array
 * @param arr pointer to adaptive array
*/
void DeleteAdptArray(PAdptArray arr)
{
	if(arr == NULL) // checking for arguments validation
	{
		return;
	}
    else
    {
        int i = 0;
        for(i = 0; i < arr->length; i++) // running over array for elements deletion
        {
            if(arr->element[i] != NULL) // if element exists (i.e. not NULL) delete it using delete function
            {
                arr->delete((arr->element)[i]);
            }
        }
        // freeing all pointers at the end of use
        free(arr->element);
        arr->element = NULL;
        free(arr);
        arr = NULL;
    }
}

/**
 * this function returns element from the adaptive array - standard element getter
 * @param arr pointer to the adaptive array
 * @param i index from where get the element
 * @return the element in position i from arr if succsessfull, else FAIL(=0)
*/
PElement GetAdptArrayAt(PAdptArray arr, int i)
{			
    if(arr == NULL || i < 0 || i >= arr->length) // checking for arguments validation
    {
        return FAIL;
    }
    else
    {
        if((arr->element)[i] != NULL) // checking that element is exists
        {
            return arr->copy((arr->element)[i]); // returning a copy of the element
        }
        return FAIL;
    }	
}

/**
 * this function returns the length of the adaptive array - standard element getter
 * @param arr pointer to the the adaptive array
 * @return the size of the adaptive array if succsessfull, else FAIL(=0)
*/
int GetAdptArraySize(PAdptArray arr)
{
    if(arr == NULL) // checking for arguments validation
    {
        return FAIL;
    }
    else // returning length field
    {
        return arr->length;
    }
}


/**
 * this function prints the adaptive array elements that exists
 * @param arr pointer to the adaptive array
*/
void PrintDB(PAdptArray arr)
{
    if(arr == NULL) // checking for arguments validation
    {
        return;
    }
    else 
    {
        int i = 0;
        for(i = 0; i < arr->length; i++) // printing all elements that exists
        {
            if((arr->element)[i] != NULL)
            {
                arr->print((arr->element)[i]);
            }
        }
    }
}

/**
 * this function adds new element to adaptive array
 * @param arr pointer to adaptive array
 * @param i index to add new element
 * @param e new element to add
 * @return SUCCESS(=1) is element added succsessfully, FAIL(=0) else
*/
Result SetAdptArrayAt(PAdptArray arr, int i, PElement e)
{	
    if(arr == NULL || i < 0 || e == NULL) // checking for arguments validation
    {
        return FAIL;
    }
    else
    {
        if(i >= arr->length) // if index is bigger that the size, the array will increase adaptively
        {
            PElement* element;
            element = (PElement*)calloc((i + 1), sizeof(PElement)); // allocating memmory
            if(element == NULL) // checking memmory allocation
            {
                return FAIL;
            }
            memcpy(element, arr->element, (arr->length) * sizeof(PElement)); // copying old data
            free(arr->element);
            // updating field for new data
            arr-> element = element;
            arr->length = i + 1;
        }
        // deleting and copying element
        if((arr->element)[i] != NULL)
        {
            arr->delete((arr->element)[i]);
        }
        (arr->element)[i] = arr->copy(e);
        return SUCCESS;
    }
}
