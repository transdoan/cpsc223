/*
 * Tran Doan
 * CPSC223 PSET3
 * 03/10/23
 * Include array list definition. This is just like pirate_list, but for char* (skill strings).
 * List insert is just shorter because we want to insert skill at the last index (i.e length).
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "array_list.h"

#define INITIAL_CAPACITY 25
#define RESIZE_FACTOR 2

void array_list_expand_if_necessary(array_list* skills_list);
void array_list_contract_if_necessary(array_list* skills_list);

/* Prototypes */
struct array_lists {
    char **array; /* Array of char pointers */
    size_t length;
    size_t capacity;
};

/*
 * Allocate memory for a new array_list and return a pointer to it.
 */
array_list *array_list_create() {

    /* Allocate space for our array_list that is pointed to by skills_list*/
    array_list *skills_list = malloc(sizeof(array_list));
    if (skills_list == NULL) {
        return NULL; 
    }
    
    /* skills is an array of pointers pointing to char items, so malloc space for those pointers */
    skills_list->array = malloc(sizeof(char *) * INITIAL_CAPACITY);
    if (skills_list->array == NULL) {
        return NULL; 
    }

    /* Set length to 0 (denotes empty array), and capacity to init cap */
    skills_list->length = 0;
    skills_list->capacity = INITIAL_CAPACITY;
    return skills_list; /* Return ptr to newly created array_list */
}

/* Count how many occurences of a skill in skills_lst */
int array_list_count_of(array_list *skills_list, char *skill) {
    int count = 0;
    /* Walk through skills_list list to find char with p_name */
    for (size_t i = 0; i < skills_list->length; i++) {
        if (strcmp(skill, skills_list->array[i]) == 0) {
            count = count + 1; // Found p_name char
        }
    }
    return count;
}

/*
 * Return the index of the skill with the same name as p, or a value greater than or equal to the length of the list if there is no skill in the list with a matching name.
 */
size_t array_list_index_of(array_list *skills_list, char *skill) {

    /* Walk through skills_list list to find char with p_name */
    for (size_t i = 0; i < skills_list->length; i++) {
        if (strcmp(skill, skills_list->array[i]) == 0) {
            return i; // Found p_name char
        }
    }
    
    /* Did not find a p_name char, thus return index at which char p can be added */
    return skills_list->length;
}

/*
 * Insert skill at the last index (lenght)
 * If the skill was inserted into the list, return NULL
 */
char *array_list_insert(array_list *skills_list, char *skill, size_t idx) {

    /* Handles inserting when list is NOT EMPTY */
    if (skills_list->length > 0) {

        array_list_expand_if_necessary(skills_list); /* Expand skills_list accordingly to fit p in */ 
       
        /* Walk through skills_list shift everything at and right of idx by an index of 1, then insert p at index idx */
        for (size_t i = skills_list->length - 1; i >= idx; i--) {
            skills_list->array[i + 1] = skills_list->array[i];
        }

        /* Insert p at idx, which is hopefully empty because we moved everything */
        skills_list->array[idx] = skill; 
        skills_list->length = skills_list->length + 1;
    } else { 
        /* Handles when list is EMPTY by appending not inserting */
        skills_list->array[idx] = skill; 
        skills_list->length = skills_list->length + 1;
    }
    return NULL;
}


/*
 * Remove the skill from the list with the same name as skill, and return a skillointer to it.
 * If there is no skill in the list with the same name as skill, return NULL
 */
char *array_list_remove(array_list *skills_list, char *skill) {

    if (skills_list->length > 0) {
        /* For checking what index char p is "at" */
        size_t idx = array_list_index_of(skills_list, skill); 
            
        /* If char isn't in the list (i.e idx == skills_list->length, an unoccupied index), return NULL */
        if (idx == skills_list->length) {
            return NULL; 
        }

        /* Make a char pointer to store and return the char that will be removed */
        char *removed_skill = array_list_access(skills_list, idx);
        if (removed_skill == NULL) {
            return NULL;
        }

        /* Start at idx, move the next char (char[i + 1]) to the current char (char[i]) unti you reach the value before the final one
        *  This will overwrite the char at idx that we'd like to remove */
        for (size_t i = idx; i < skills_list->length - 1; i++) {
            skills_list->array[i] = skills_list->array[i + 1];
        }

        /* Decrease length accordingly, then contract skills_list list accordingly */
        skills_list->length = skills_list->length - 1;
        array_list_contract_if_necessary(skills_list);
        return removed_skill; /* Return ptr of char removed */
    } else {
        return NULL; /* Empty list, can't remove anything */
    }
}


/* Return a pointer to the char pointed to by index idx in the list, or NULL if idx is not a valid index (i.e., it is >= the length of the list) */
char *array_list_access(array_list *skills_list, size_t idx) {
    
    /* Check if idx is valid, or actually exists */
    if (idx >= skills_list->length) {
        return NULL;
    } else {
        return skills_list->array[idx];
    }
}


/* Sort the list of skills_list in alphabetical order by name using insertion sort */
void array_list_sort(array_list *skills_list) {

    char *temp = NULL; /* j will be the index we will use to sort */
    
    /* Assume first element is sorted, so we start with index 1, not 0 
    *  These nested loops will compare current char (char[j]) to previous char (char[i]) */
    for (size_t i = 0; i < skills_list->length; i++) {
        for (size_t j = i + 1; j < skills_list->length; j++) {
            /* If current char is less than previous char (i.e strcmp returns int < 0), then swap them */
            if (strcmp(skills_list->array[j], skills_list->array[i]) < 0) {
                /* Stores previous char so it doesn't get lost when its position is swapped to current char */
                temp = skills_list->array[i]; 
                skills_list->array[i] = skills_list->array[j]; /* Swap */
                skills_list->array[j] = temp; 
            }
        }
    }
}

/* Return the number of skills_list in the list */
size_t array_list_length(array_list *skills_list) {
    return skills_list->length;
}

/* Free all memory associated with the array_list, but leave the memory associated with the skills_list in the list */
void array_list_destroy(array_list *skills_list) {
    for (size_t i = 0; i < skills_list->length; i++) {
        free(skills_list->array[i]);
    }
    free(skills_list->array);
    free(skills_list);
}

/* Exapnds list */
void array_list_expand_if_necessary(array_list* skills_list) {
    /* Checks if length is equal to capacity, then reallocs skills with capacity * 2 skills_list size space */
    if (skills_list->length >= skills_list->capacity) {
		skills_list->capacity = skills_list->capacity * RESIZE_FACTOR; // Increase capacity by factor of 2
        skills_list->array = realloc(skills_list->array, sizeof(char *) * skills_list->capacity); // Realloc new-capacity-sized space for skills
        fprintf(stderr, "Expand to %zu\n", skills_list->capacity); // Notify stderr of change in skills size
	}
}

/*
* Check if the actual number of skills_list in the array is "too small"; if it is, decrease the capacity of the array by a factor of RESIZE_FACTOR.
* If the array capacity was changed, print to stderr the string "Contract to " followed by the new capacity of the list. Here is a possible print statement:
*
*     fprintf(stderr, Contract to %zu\n, new_capacity);
*
* If the capacity was not changed, do nothing.
*
* The capacity of the array must never fall below INITIAL_CAPACITY!
*/
void array_list_contract_if_necessary(array_list* skills_list) {
    if (skills_list->length <= (skills_list->capacity / (RESIZE_FACTOR * RESIZE_FACTOR))) {
        if (skills_list->capacity > INITIAL_CAPACITY) {
            skills_list->capacity = skills_list->capacity / RESIZE_FACTOR; // Dec capacity by factor of 2
            skills_list->array = realloc(skills_list->array, sizeof(char *) * skills_list->capacity); // Shrink skills
            fprintf(stderr, "Contract to %zu\n", skills_list->capacity); // Notify stderr of change in skills size
        }
	}
}

