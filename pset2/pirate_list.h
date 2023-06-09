/*
 * Tran Doan
 * CPSC223 PSET3
 * 03/09/23
 * Includes all implementation and functions necessary to creating, accessing, and manipulating pirate lists
 */
#ifndef __PIRATE_LIST_H__
#define __PIRATE_LIST_H__

#include <stdlib.h>
#include "pirate.h"

// Type of a list of pirates
typedef struct implementation pirate_list;

/*
 * Allocate memory for a new pirate_list and return a pointer to it.
 */
pirate_list *list_create();

/*
 * Return the index of the pirate with the same name as p, or a value greater than or equal to the length of the list if there is no pirate in the list with a matching name.
 */
size_t list_index_of(pirate_list *pirates, pirate *p);

/*
 * Only if there is no pirate in the list with the same name as p, insert pirate p into the list at index idx by copying the pointer, shifting the latter part of the list one “slot” to the right.
 * If there is a pirate in the list with the same name as p, do nothing, and return a pointer to the pirate that was not inserted.
 * If the pirate was inserted into the list, return NULL
 */
pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx);

/*
 * Remove the pirate from the list with the same name as p, and return a pointer to it.
 * If there is no pirate in the list with the same name as p, return NULL
 */
pirate *list_remove(pirate_list *pirates, pirate *p);

/*
 * Return a pointer to the pirate pointed to by index idx in the list, or NULL if idx is not a valid index (i.e., it is >= the length of the list).
 */
pirate *list_access(pirate_list *pirates, size_t idx);

/*
 * Sort the list of pirates in the order defined by the added argument value called "filter_by"
 */
void list_sort(pirate_list *pirates, int filter_by);

/*
 * Return the number of pirates in the list.
 */
size_t list_length(pirate_list *pirates);

/*
 * Free all memory associated with the pirate_list, but leave the memory associated with the pirates in the list untouched (it is someone else's job to free the pirates; maybe that dog with the keys in the Pirates of the Caribbean).
 */
void list_destroy(pirate_list *pirates);

#endif
