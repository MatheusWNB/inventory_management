#include "libs/libs.h"
#include "utils/utils.h"
#include "menu/opcoes.h"

void edit_inventory(FILE *fp){

    printf("////////// EDITOR DE ESTOQUES //////////\n");
    printf("Quais itens você gostaria de registrar no seu estoque? (max. 100 por estoque): \n");

    int i = 0;
    int quantidade_bytes;
    char *ptr_itens = NULL;
    char *nome_item = NULL;
    
    while(i < 100){
        printf("Item a ser registrado(max. 20 caracteres por item): ");
        getname(nome_item, 20);
        int len_name = strlen(nome_item);
        quantidade_bytes += len_name+1;

        printf("oi\n");
        char *temp = (char *)realloc(ptr_itens, quantidade_bytes);

        if(temp == NULL){
            system("clear");
            printf("********** REGISTRO DE ITEM FALHOU **********\n");
            free(temp);
            break;
        }
        
        printf("oi");
        strcpy(ptr_itens, nome_item);
        i++;
        printf("%s\n", ptr_itens);
    }

}


