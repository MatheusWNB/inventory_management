#include "user_inventory/user_inventory.h"
#include "utils/utils.h"

/*
Essa struct armazenará todos as informações
referentes ao inventário que o usuário abrir
*/
void info_inventory(user_inventories *arg, char *name, int *ids, 
                    FILE *inventories, FILE *logs)
{
    arg->username = name;
    arg->id_items = ids;
    arg->user_inventories = inventories;
    arg->log_inventories = logs;
}
                        
/*
Essa função armazena no arquivo de estoque do usuário
todos os itens que foram adicionados em allocate_inventory
*/
void set_inventory_file(FILE *fp, char *username, char *items, 
                        int total_items, int *offset_items)
{      
    int validate;
    validate = verify_inventory(fp);
    
    int len_item;
    long total_bytes;

    for(int i = 0; i < total_items; i++){
        len_item = strlen(items + offset_items[i]);

        fwrite(&i, sizeof(int), 1, fp);

        /*Armazena a posição do primeiro caractere do
        item a ser escrito no arquivo*/
        long offset = ftell(fp) + 1;
        fwrite(&offset, sizeof(long), 1, fp);

        fwrite(items + offset_items[i], sizeof(char), len_item, fp);

    }
    total_bytes = ftell(fp);
    fwrite(&total_bytes, sizeof(long), 1, fp);

}