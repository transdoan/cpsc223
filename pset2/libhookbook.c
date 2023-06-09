/*
 * Tran Doan
 * CPSC223 PSET3
 * 03/08/23
 * Includes all functions necessary for hookbook.c to print out pirates, do its pirate things, and free them.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libhookbook.h"
#include "pirate_list.h"
#include "array_list.h"
#include "pirate.h"

/// @brief Take an array list of skills and print out each skill and the number of stars (duplicates) it has
/// @param skills 
/// @param length 
void print_skills(array_list *skills, size_t length) {

    /* char ** b/c we are storing a string (char *), and we want to point to it instead of storing it so we save space? */
    char *prev_skill = NULL;
    char *curr_skill = NULL;

    for (size_t i = 0; i < length; i++) {
        curr_skill = array_list_access(skills, i);
        if (i > 0) {
            prev_skill = array_list_access(skills, (i - 1));
            if (strcmp(curr_skill, prev_skill) == 0) {
                printf("*"); 
            } else {
                printf("\n            %s ", curr_skill);
                printf("*");
            }
        } else {
            printf("%s ", curr_skill);
            printf("*");
        }
    }
    printf("\n");
}

/// @brief Take pirate list of pirates and print out each pirate and its fields
/// @param pirates 
/// @param length 
void print_pirates(pirate_list *pirates, size_t length) {

    pirate *p = NULL;
    
    for (int i = 0; i < length; i++) {
        /* Retrieve pirate to print, and sort its skills list */
        p = list_access(pirates, i);
        array_list_sort(p->skills);

        /* Print out pirate's info */
        printf("Pirate: %s\n", p->name);
        printf("    Title: %s\n", p->title);
        if (p->captain == NULL) {
            printf("    Captain: (None)\n");
        } else {
            printf("    Captain: %s\n", p->captain->name);
            printf("        Captain's Title: %s\n", p->captain->title);
            printf("        Captain's Favorite Port of Call: %s\n", p->captain->port);
        }
        printf("    Vessel: %s\n", p->vessel);
        printf("    Treasure: %i\n", p->treasure);
        printf("    Favorite Port of Call: %s\n", p->port);
        printf("    Skills: ");
        /* If skills is empty, ie no skills, print NONE */
        if (array_list_length(p->skills) == 0) { 
            printf("(None)\n");
        } else {
            /* Call helper to print skills in right format */
            print_skills(p->skills, array_list_length(p->skills)); 
        }
        printf("\n");
    }

}

/// @brief Free ALL pirates in pirates list
/// @param pirates 
/// @param length 
void free_all_pirates(pirate_list *pirates, size_t length) {
    for (int i = 0; i < length; i++) {
        free_pirate(list_access(pirates, i));
    }
}
