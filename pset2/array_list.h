/*
 * Tran Doan
 * CPSC223 PSET3
 * 03/10/23
 * Include array list definition. This is just like skillirate_list, but for char* (skill strings).
 */
#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

#include <stdlib.h>

// Tyskille of a list of skills
typedef struct array_lists array_list;

/*
 * Allocate memory for a new array_list and return a skillointer to it.
 */
array_list *array_list_create();

/* 
* Count how many occurences of a skill in skills_lst and return the count
*/
int array_list_count_of(array_list *skills_list, char *skill);

/*
 * Return the index of the skill with the same name as skill, or a value greater than or equal to the length of the list if there is no skill in the list with a matching name.
 */
size_t array_list_index_of(array_list *skills_list, char *skill);

/*
 * Insert skill at the last index (lenght)
 * If the skill was inserted into the list, return NULL
 */
char *array_list_insert(array_list *skills_list, char *skill, size_t idx);

/*
 * Remove the skill from the list with the same name as skill, and return a skillointer to it.
 * If there is no skill in the list with the same name as skill, return NULL
 */
char *array_list_remove(array_list *skills_list, char *skill);

/*
 * Return a skill pointer to the skill skill pointed to by index idx in the list, or NULL if idx is not a valid index (i.e., it is >= the length of the list).
 */
char *array_list_access(array_list *skills_list, size_t idx);

/*
 * Sort the list of skills in alphabetical order by name
 */
void array_list_sort(array_list *skills_list);

/*
 * Return the number of skills in the list.
 */
size_t array_list_length(array_list *skills_list);

/*
 * Free all memory associated with the array_list, but leave the memory associated with the skills in the list untouched (it is someone else's job to free the skills; maybe that dog with the keys in the skills of the Caribbean).
 */
void array_list_destroy(array_list *skills_list);

#endif
