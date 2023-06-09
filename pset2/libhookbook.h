/*
 * Tran Doan
 * CPSC223 PSET3
 * 03/08/23
 * Header file for libhookbook.c -- includes all helper functions for printing and freeing pirates
 */
#ifndef __LIBHOOKBOOK_H__
#define __LIBHOOKBOOK_H__

#include <stdlib.h>
#include "pirate_list.h"
#include "array_list.h"
#include "pirate.h"

/// @brief Take an array list of skills and print out each skill and the number of stars (duplicates) it has
/// @param skills 
/// @param length 
void print_skills(array_list *skills, size_t length);

/// @brief Free ALL pirates in pirates list
/// @param pirates 
/// @param length 
void print_pirates(pirate_list *pirates, size_t length);

/* Free pirates */
void free_all_pirates(pirate_list *pirates, size_t length);

#endif
