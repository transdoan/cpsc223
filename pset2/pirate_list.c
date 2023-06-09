/*
 * Tran Doan
 * CPSC223 PSET3
 * 03/09/23
 * Includes all implementation and functions necessary to creating, accessing, and manipulating pirate lists
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pirate_list.h"
#include "pirate.h"

#define INITIAL_CAPACITY 25
#define RESIZE_FACTOR 2

void list_expand_if_necessary(pirate_list* pirates);
void list_contract_if_necessary(pirate_list* pirates);

struct implementation {
    pirate **pirate_arr; /* Array of pirate pointers */
    size_t length;
    size_t capacity;
};

/*
 * Allocate memory for a new pirate_list and return a pointer to it.
 */
pirate_list *list_create() {

    /* Allocate space for our pirate_list that is pointed to by pirates*/
    pirate_list *pirates = malloc(sizeof(pirate_list));
    if (pirates == NULL) {
        return NULL; 
    }
    
    /* Pirate_arr is an array of pointers pointing to pirate items, so malloc space for those pointers */
    pirates->pirate_arr = malloc(sizeof(pirate *) * INITIAL_CAPACITY);
    if (pirates->pirate_arr == NULL) {
        return NULL; 
    }

    /* Set length to 0 (denotes empty array), and capacity to init cap */
    pirates->length = 0;
    pirates->capacity = INITIAL_CAPACITY;
    return pirates; /* Return ptr to newly created pirate_list */
}

/*
 * Return the index of the pirate with the same name as p, or a value greater than or equal to the length of the list if there is no pirate in the list with a matching name.
 */
size_t list_index_of(pirate_list *pirates, pirate *p) {

    /* Walk through pirates list to find pirate with p_name */
    for (size_t i = 0; i < pirates->length; i++) {
        if (strcmp(p->name, pirates->pirate_arr[i]->name) == 0) {
            return i; // Found p_name pirate
        }
    }
    
    /* Did not find a p_name pirate, thus return index at which pirate p can be added */
    return pirates->length;
}

/*
 * Only if there is no pirate in the list with the same name as p, insert pirate p into the list at index idx by copying the pointer, shifting the latter part of the list one “slot” to the right.
 * If there is a pirate in the list with the same name as p, do nothing, and return a pointer to the pirate that was not inserted.
 * If the pirate was inserted into the list, return NULL
 */
pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx) {

    /* Handles inserting when list is NOT EMPTY */
    if (pirates->length > 0) {
        /* If pirate is already in the list, return ptr to pirate that wasn't inserted */
        if (list_index_of(pirates, p) != pirates->length) {
            return p; 
        }

        list_expand_if_necessary(pirates); /* Expand pirates accordingly to fit p in */ 
       
        /* Walk through pirates shift everything at and right of idx by an index of 1, then insert p at index idx */
        for (size_t i = pirates->length - 1; i >= idx; i--) {
            pirates->pirate_arr[i + 1] = pirates->pirate_arr[i];
        }

        /* Insert p at idx, which is hopefully empty because we moved everything */
        pirates->pirate_arr[idx] = p; 
        pirates->length = pirates->length + 1;
    } else { 
    /* Handles when list is EMPTY by appending not inserting */
        pirates->pirate_arr[idx] = p; 
        pirates->length = pirates->length + 1;
    }
    return NULL;
}


 /* 
  * Remove the pirate from the list with the same name as p, and return a pointer to it.
  * If there is no pirate in the list with the same name as p, return NULL 
  */
pirate *list_remove(pirate_list *pirates, pirate *p) {

    if (pirates->length > 0) {
        /* For checking what index pirate p is "at" */
        size_t idx = list_index_of(pirates, p); 
            
        /* If pirate isn't in the list (i.e idx == pirates->length, an unoccupied index), return NULL */
        if (idx == pirates->length) {
            return NULL; 
        }

        /* Make a pirate pointer to store and return the pirate that will be removed */
        pirate *removed_pirate = list_access(pirates, idx);
        if (removed_pirate == NULL) {
            return NULL;
        }

        /* Start at idx, move the next pirate (pirate[i + 1]) to the current pirate (pirate[i]) unti you reach the value before the final one
        *  This will overwrite the pirate at idx that we'd like to remove */
        for (size_t i = idx; i < pirates->length - 1; i++) {
            pirates->pirate_arr[i] = pirates->pirate_arr[i + 1];
        }

        /* Decrease length accordingly, then contract pirates list accordingly */
        pirates->length = pirates->length - 1;
        list_contract_if_necessary(pirates);
        return removed_pirate; /* Return ptr of pirate removed */
    } else {
        return NULL; /* Empty list, can't remove anything */
    }
}

/*
 * Return a pointer to the pirate pointed to by index idx in the list, or NULL if idx is not a valid index (i.e., it is >= the length of the list).
 */
pirate *list_access(pirate_list *pirates, size_t idx) {
    
    /* Check if idx is valid, or actually exists */
    if (idx >= pirates->length) {
        return NULL;
    } else {
        return pirates->pirate_arr[idx];
    }
}


/*
 * Sort the list of pirates in the order defined by the inputted value "filter_by"
 */
void list_sort(pirate_list *pirates, int filter_by) {

    pirate *temp = NULL; /* j will be the index we will use to sort */
    
    /* SORT BY NAME ALPHABETICAL ORDER */
    if (filter_by == 1) {
        /* Assume first element is sorted, so we start with index 1, not 0 
         * These nested loops will compare current pirate (pirate[j]) to previous pirate (pirate[i]) */
        for (size_t i = 0; i < pirates->length; i++) {
            for (size_t j = i + 1; j < pirates->length; j++) {
                /* If current pirate is less than previous pirate (i.e strcmp returns int < 0), then swap them */
                if (strcmp(pirates->pirate_arr[j]->name, pirates->pirate_arr[i]->name) < 0) {
                    /* Stores previous pirate so it doesn't get lost when its position is swapped to current pirate */
                    temp = pirates->pirate_arr[i]; 
                    pirates->pirate_arr[i] = pirates->pirate_arr[j]; /* Swap */
                    pirates->pirate_arr[j] = temp; 
                }
            }
        }
    /* SORT BY VESSEL ALPHABETICAL ORDER */
    } else if (filter_by == 2) {
        for (size_t i = 0; i < pirates->length; i++) {
            for (size_t j = i + 1; j < pirates->length; j++) {
                /* If current pirate's vessel is less than previous pirate's vessel (i.e strcmp returns int < 0), then swap them */
                if (strcmp(pirates->pirate_arr[j]->vessel, pirates->pirate_arr[i]->vessel) < 0) {
                    /* Stores previous pirate so it doesn't get lost when its position is swapped to current pirate */
                    temp = pirates->pirate_arr[i]; 
                    pirates->pirate_arr[i] = pirates->pirate_arr[j]; /* Swap */
                    pirates->pirate_arr[j] = temp; 
                }
            }
        }
    /* SORT BY TREASURE IN DECREASING ORDER */
    } else if (filter_by == 3) {
        for (size_t i = 0; i < pirates->length; i++) {
            for (size_t j = i + 1; j < pirates->length; j++) {
                /* Check if current pirate's treasure is greater than previous, if yes then swap */
                if (pirates->pirate_arr[j]->treasure > pirates->pirate_arr[i]->treasure) {
                    temp = pirates->pirate_arr[i]; 
                    pirates->pirate_arr[i] = pirates->pirate_arr[j]; /* Swap */
                    pirates->pirate_arr[j] = temp; 
                }
            }
        }
    }
}


/*
 * Return the number of pirates in the list.
 */
size_t list_length(pirate_list *pirates) {
    return pirates->length;
}

/*
 * Free all memory associated with the pirate_list, but leave the memory associated with the pirates in the list untouched (it is someone else's job to free the pirates; maybe that dog with the keys in the Pirates of the Caribbean).
 */
void list_destroy(pirate_list *pirates) {
    free(pirates->pirate_arr);
    free(pirates);
}


void list_expand_if_necessary(pirate_list* pirates) {
    /* Checks if length is equal to capacity, then reallocs pirate_arr with capacity * 2 pirates size space */
    if (pirates->length >= pirates->capacity) {
		pirates->capacity = pirates->capacity * RESIZE_FACTOR; // Increase capacity by factor of 2
        pirates->pirate_arr = realloc(pirates->pirate_arr, sizeof(pirate *) * pirates->capacity); // Realloc new-capacity-sized space for pirate_arr
        fprintf(stderr, "Expand to %zu\n", pirates->capacity); // Notify stderr of change in pirate_arr size
	}
}


/*
* Check if the actual number of pirates in the array is "too small"; if it is, decrease the capacity of the array by a factor of RESIZE_FACTOR.
* If the array capacity was changed, print to stderr the string "Contract to " followed by the new capacity of the list.
* If the capacity was not changed, do nothing.
* The capacity of the array never fall below INITIAL_CAPACITY!
*/
void list_contract_if_necessary(pirate_list* pirates) {
    if (pirates->length <= (pirates->capacity / (RESIZE_FACTOR * RESIZE_FACTOR))) {
        if (pirates->capacity > INITIAL_CAPACITY) {
            pirates->capacity = pirates->capacity / RESIZE_FACTOR; // Dec capacity by factor of 2
            pirates->pirate_arr = realloc(pirates->pirate_arr, sizeof(pirate *) * pirates->capacity); // Shrink pirate_arr
            fprintf(stderr, "Contract to %zu\n", pirates->capacity); // Notify stderr of change in pirate_arr size
        }
	}
}

