#include "user_inventory/user_inventory.h"

void info_inventory(user_inventories *arg, char *name, int *ids, 
                    FILE *inventories, FILE *logs)
{
    arg->username = name;
    arg->id_items = ids;
    arg->user_inventories = inventories;
    arg->log_inventories = logs;
}
                        
                
int verify_inventory(FILE *fp){
    fseek(fp, 0, SEEK_END);
    int is_empty = ftell(fp);

    return is_empty;

}

void set_inventory_file(FILE *fp, char *username, char *items, 
                        int total_items, int *offset_items)
{      
    int validate;
    validate = verify_inventory(fp);

    if(validate == 0){
        int len = strlen(username);
        fwrite(username, sizeof(char), len, fp);
    }

    int len_item;
    long total_bytes;

    for(int i = 0; i < total_items; i++){
        len_item = strlen(items + offset_items[i]);
        fwrite(&i, sizeof(int), 1, fp);
        long offset = ftell(fp) + 1;
        fwrite(&offset, sizeof(long), 1, fp);
        fwrite(items + offset_items[i], sizeof(char), len_item, fp);

    }

    total_bytes = ftell(fp);
    fwrite(&total_bytes, sizeof(long), 1, fp);

}