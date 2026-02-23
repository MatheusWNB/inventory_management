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
void set_inventory_file(FILE *fp, char *items, 
                        int total_items, int *offset_items, int ids)
{      
    int len_item;
    fseek(fp, 0, SEEK_END);

    fwrite(total_items, sizeof(int), 1, fp);

    for(int i = ids; i < total_items; i++){
        len_item = strlen(items + offset_items[i]);

        fwrite(&i, sizeof(int), 1, fp);
        fwrite(&len_item, sizeof(int), 1, fp);

        /*Armazena a posição do primeiro caractere do
        item a ser escrito no arquivo*/
        long offset = ftell(fp) + sizeof(long);
        fwrite(&offset, sizeof(long), 1, fp);

        fwrite(items + offset_items[i], sizeof(char), len_item, fp);

    }
}

void get_inventory(FILE *fp, char *items, int *total_items, 
                    int *offset_items, int *ids)
{   
    char *try_realloc_items = NULL;
    int *try_realloc_offsets = NULL;
    char item[20];
    int len_name;
    int qtd_bytes = 0;
    int len_item;
    int offset;
    
    fread(&len_name, sizeof(int), 1, fp);
    fseek(fp, len_name, SEEK_SET);

    fread(total_items, sizeof(int), 1, fp);

    try_realloc_offsets = (int)realloc(fp, sizeof(int) * (*total_items));

    if(try_realloc_offsets == NULL){
        printf("REALLOC FALHOU\n");
        exit(1);
    }

    offset_items = try_realloc_offsets;

    for(int i = 0; i <= total_items; i++){
        
        fread(ids, sizeof(int), 1, fp);
        fread(&len_item, sizeof(int), 1, fp);
        qtd_bytes = len_item + 1;

        try_realloc_items = (char *)realloc(fp, qtd_bytes);

        if(try_realloc_items == NULL){
            printf("REALLOC FALHOU\n");
            exit(1);
        }

        items = try_realloc_items;
        seek(fp, ftell(fp) + sizeof(long), SEEK_SET);
        fread(item, sizeof(char), len_item, fp);
        item[len_item] = '\0';
        items = item;

        offset_items[i] = qtd_bytes + 1;

    }
}