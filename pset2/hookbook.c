/*
 * Tran Doan
 * CPSC223 PSET3
 * 03/12/23
 * Include main.c file, which takes in a pirate profile file and pirate pairs file and a sorting filter.
 * Returns a sorted list of pirates and their profile information.
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "libhookbook.h"
#include "array_list.h"
#include "pirate_list.h"
#include "pirate.h"

#define VALUE_MAX_LEN 65 /* 64 chars + 1 string terminator */
#define LABEL_MAX_LEN 9

typedef enum states {
    FIND_FIRST_PIRATE,
    FOUND_PIRATE
} states;

int main (int argc, char *argv[]) {

    /* Checks for the correct number of arguments */
    if (argc < 4) { 
        fprintf(stderr, "Invalid arguments\n");
        exit(1);  
    }

    int filter; /* Var to keep track of what type of filter user wants to sort by */

    /* Check for the correct sort values (i.e -n, -v, or -t) */
    if (strcmp(argv[3], "-n") == 0) { 
        filter = 1;
    } else if (strcmp(argv[3], "-v") == 0) {
        filter = 2;
    } else if (strcmp(argv[3], "-t") == 0) {
        filter = 3;
    } else {
        fprintf(stderr, "Invalid argument: %s\n", argv[3]);
        exit(1);  
    }

    /* Open file with pirate info (argv[1]) and file with pirate pairs (argv[2]) */
    FILE *pirate_file; 
    pirate_file = fopen(argv[1], "r");
    FILE *pairs_file;
    pairs_file = fopen(argv[2], "r");
    if (pirate_file == NULL && pairs_file == NULL) {
        fprintf(stderr, "Invalid filename: %s\n", argv[1]);
        exit(1);
    } else if (pirate_file == NULL) {
        fprintf(stderr, "Invalid filename: %s\n", argv[1]);
        exit(1);
    } else if (pairs_file == NULL) {
        fprintf(stderr, "Invalid filename: %s\n", argv[2]);
        exit(1);
    }

    /* Create our list of pirates */
    pirate_list *pirates_lst = list_create();
    if (pirates_lst == NULL) {
        exit(1);
    }

    pirate *p = NULL; /* Pirate buffer */
    
    /* Buffers to store <label> and <name> read from pirate_file */
    char *label = malloc(sizeof(char) * LABEL_MAX_LEN); 
    char *prev_label = malloc(sizeof(char) * LABEL_MAX_LEN);
    char *value = malloc(sizeof(char) * VALUE_MAX_LEN);
    char *prev_value = malloc(sizeof(char) * VALUE_MAX_LEN);

    /* Set initial state for our state machine */
    states current_state = FIND_FIRST_PIRATE;

    /* 
     * Read in a line formatted like "<label>:<value>" 
     * %*[^\n] consumes any excess chars over 64
     * %*c consumes the final char of the line, which is \n 
     */
    while (fscanf(pirate_file, " %8[^:\n]:%64[^\n]%*[^\n]%*c", label, value) != EOF) {
        /* 
         * Cases for duplicate skills and empty labels:
         * If fscanf read in an emtpy <value>, then value will not be updated, thus prev_value == value 
         * First if checks whether value is unique from prev_value -> if yes then its not an empty <value> 
         */
        if (strcmp(value, prev_value) != 0) {
            strncpy(prev_value, value, VALUE_MAX_LEN);
            strncpy(prev_label, label, LABEL_MAX_LEN);
        /* This case is primarily to account for skills b/c repeated labels 
        * (i.e prev_label == label) indicates that repeated values with same label r ok */
        } else if (strcmp(label, prev_label) == 0) {
            strncpy(prev_value, value, VALUE_MAX_LEN);
            strncpy(prev_label, label, LABEL_MAX_LEN);
        /* Case is for actual empty values because the previous label was different than current label */
        } else {
            strcpy(value, "(None)");
        }

        /* FSM: Manage what value belongs to what pirate as we go through  */
        switch (current_state) {

            /* Case only for the first pirate found */
            case FIND_FIRST_PIRATE: 
                if (strcmp(label, "name") == 0) {   
                    if (strlen(value) != 0) {
                        /* Make pirate profile with string stored in value, that hopefully is p's name */
                        p = make_pirate(value); /* p is a pirate pointer, and make_pirate returns a pirate pointer */
                    } else {
                        p = make_pirate("(None)");
                    }
                    list_insert(pirates_lst, p, list_length(pirates_lst));
                    current_state = FOUND_PIRATE;
                }
                break;

            /* Once pirate is found, insert all following information into the pirate struct, which is pointed to by p */
            case FOUND_PIRATE:
                if (strcmp(label, "title") == 0) {
                    if (strlen(value) == 0) {
                        insert_title(p, "(None)");
                    } else {   
                        insert_title(p, value);
                    }
                } else if (strcmp(label, "vessel") == 0) {
                    if (strlen(value) == 0) {
                        insert_vessel(p, "(None)");
                    } else {   
                        insert_vessel(p, value);
                    }
                } else if (strcmp(label, "treasure") == 0) {
                    if (strlen(value) == 0) {
                        insert_treasure(p, 0);
                    } else {   
                        insert_treasure(p, atoi(value));
                    }
                } else if (strcmp(label, "port") == 0) {
                    if (strlen(value) == 0) {
                        insert_port(p, "(None)");
                    } else {   
                        insert_port(p, value);
                    }
                } else if (strcmp(label, "skill") == 0) {
                    if (strlen(value) == 0) {
                        insert_skill(p->skills, "(None)");
                    } else {
                        insert_skill(p->skills, value);
                    }
                } else if (strcmp(label, "name") == 0) {   
                    if (strlen(value) == 0) {
                        p = make_pirate("(None)");
                    } else {
                        /* Make pirate profile with string stored in value, that hopefully is p's name */
                        p = make_pirate(value); /* p is a pirate pointer, and make_pirate returns a pirate pointer */
                    }
                    list_insert(pirates_lst, p, list_length(pirates_lst));
                    current_state = FOUND_PIRATE;
                }
                break;
        }
    }
    /* Close file and free buffer */
    free(value); 
    free(prev_value);
    free(label);
    free(prev_label);
    fclose(pirate_file); 

    /* Buffers for reading in pirate-captain pair names */
    char *pir = malloc(sizeof(char) * VALUE_MAX_LEN); 
    char *cap = malloc(sizeof(char) * VALUE_MAX_LEN);

    /* Read in pirate pairs */
    while (fscanf(pairs_file, " %64[^/]/%64[^\n]", pir, cap) != EOF) {
        /* Temps used to find what indexes pirate and captain are */
        pirate *p_temp = make_pirate(pir);
        pirate *c_temp = make_pirate(cap);
        size_t p_index = list_index_of(pirates_lst, p_temp);
        size_t c_index = list_index_of(pirates_lst, c_temp);

        /* With the indexes of pir and cap, insert the captain into pirate */
        insert_captain(list_access(pirates_lst, p_index), list_access(pirates_lst, c_index));

        free_pirate(p_temp);
        free_pirate(c_temp);
    }
    free(pir); 
    free(cap);
    fclose(pairs_file);

    /* Sort pirates list by filter set (i.e -n or -v or -t)*/
    list_sort(pirates_lst, filter); 

    /* Print out all pirate names using helper function */
    print_pirates(pirates_lst, list_length(pirates_lst)); 

    /* Free all pirates and destroy pirate list */
    free_all_pirates(pirates_lst, list_length(pirates_lst));
    list_destroy(pirates_lst);
}

