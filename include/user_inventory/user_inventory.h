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

void set_inventory_file(FILE *fp, char *items, 
    int total_items, int *offset_items, int ids, char *username);

void allocate_inventory(FILE *fp, char *username);

void get_inventory(FILE *fp, char *items, int *total_items, 
    int *offset_items, int *ids);

#endif

