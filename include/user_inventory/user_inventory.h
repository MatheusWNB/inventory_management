#ifndef USER_INVENTORY_H
#define USER_INVENTORY_H

#include "libs/libs.h"
#include "utils/utils.h"

typedef struct {
    char *username;
    int *id_items;
    FILE *user_inventories;
    FILE *log_inventories;
}user_inventories;

void info_inventory(user_inventories *arg, char *name, int *ids, 
    FILE *inventories, FILE *logs);

int verify_inventory(FILE *fp);

void set_inventory_file(FILE *fp, char *username, char *items, 
    int total_items, int *offset_items);

void allocate_inventory(FILE *fp, char *username);


#endif

