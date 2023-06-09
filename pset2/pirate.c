/*
 * Tran Doan
 * CPSC223 PSET3
 * 03/08/23
 * Include pirate defintion and everything that pertain to creating and editing of pirates.
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pirate.h"
#include "array_list.h"

#define MAX_LEN 65 /* Max length of pirate name */

/* 
 * Make and return a pirate pointer with the appropriate space malloc-ed and "(None)" filled
 * DOES NOT insert anything in besides pirate's name. 
 */
pirate *make_pirate(char *p_name) {
    pirate *p = malloc(sizeof(pirate));
    p->name = malloc(sizeof(char) * MAX_LEN);
    strcpy(p->name, p_name);
    p->title = malloc(sizeof(char) * MAX_LEN); 
    strcpy(p->title, "(None)");
    p->captain = NULL;
    p->vessel = malloc(sizeof(char) * MAX_LEN);
    strcpy(p->vessel, "(None)");
    p->treasure = 0;
    p->port = malloc(sizeof(char) * MAX_LEN);
    strcpy(p->port, "(None)");
    p->skills = array_list_create(); // Function will return an array list pointer with an array_list malloc-ed
    return p;
}


/* Insert skill into skills_lst by malloc-ing a new string named skill_to_insert */
void insert_skill(array_list *skills_lst, char *skill) {
    char *skill_to_insert = malloc(sizeof(char) * MAX_LEN);
    strcpy(skill_to_insert, skill);
    if (array_list_insert(skills_lst, skill_to_insert, array_list_length(skills_lst)) == NULL) {
    }
}

/* Insert p_title to pirate p */
void insert_title(pirate *p, char *p_title) {
    strcpy(p->title, p_title);
}

/* Point p->captain to to pirate c */
void insert_captain(pirate *p, pirate *c) {
    p->captain = c;
}

/* Insert p_vessel to pirate p */
void insert_vessel(pirate *p, char *p_vessel) {
    strcpy(p->vessel, p_vessel);
}

/* Insert p_treasure to pirate p */
void insert_treasure(pirate *p, int p_treasure) {
    p->treasure = p_treasure;
}

/* Insert p_port to pirate p */
void insert_port(pirate *p, char *p_port) {
    strcpy(p->port, p_port);
}

/* 
 * Free the fields of pirate and pirate ptr. 
 * Does not free pirate->captain because they're pirates and will be freed regardless.
 */
void free_pirate(pirate *p) {
    free(p->name);
    free(p->title);
    free(p->vessel);
    free(p->port);
    array_list_destroy(p->skills);
    free(p);
}
