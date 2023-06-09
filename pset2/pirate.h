#ifndef __PIRATE_H__
#define __PIRATE_H__

#include <stdlib.h>

#include "array_list.h"

// Type of a pirate.
typedef struct pirate {
    char *name;
    char *title;
    struct pirate *captain;
    char *vessel;
    int treasure;
    char *port;
    array_list *skills;
} pirate; 

/// @brief Make (and malloc) a pirate pointer
/// @param p_name 
/// @return pirate * that points to a malloc-ed pirate
pirate *make_pirate(char *p_name);

void insert_skill(array_list *skills_lst, char *skill);

void insert_title(pirate *p, char *p_title);
void insert_captain(pirate *p, pirate *c);
void insert_vessel(pirate *p, char *p_vessel);
void insert_treasure(pirate *p, int p_treasure);
void insert_port(pirate *p, char *p_port);

/// @brief Free pirate pointer and pirate
/// @param p 
void free_pirate(pirate *p);

#endif
