#include "libs/libs.h"
#include "utils/utils.h"
#include "menu/opcoes.h"

void edit_inventory(FILE *fp){
    int i = 0;
    int quantidade_bytes = 0;
    int offset_bytes = 0;
    char *ptr_itens = NULL;
    char *nome_item = NULL;
    int *len_names = NULL;
    int quantidade_itens = 0;

    printf("////////// EDITOR DE ESTOQUES //////////\n");
    printf("Quais itens você gostaria de registrar no seu estoque? (max. 100 por estoque): \n");

    while(i < 100){
        printf("Item a ser registrado(max. 20 caracteres por item): ");
        nome_item = getname(20);
        int len_name = strlen(nome_item) + 1;
        quantidade_bytes += len_name;

        char *temp = (char *)realloc(ptr_itens, quantidade_bytes + 1);
        if(temp == NULL){
            system("clear");
            printf("********** REGISTRO DE ITEM FALHOU **********\n");
            free(temp);
            break;
        }

        //Copia o nome do item para o começo do novo endereço realocado
        ptr_itens = temp;
        strcpy(ptr_itens + offset_bytes, nome_item);
        quantidade_itens++;

        int *temp_array = realloc(len_names, quantidade_itens * sizeof(int));
        if(temp_array == NULL){
            system("clear");
            printf("********** REGISTRO DE LEN FALHOU **********\n");
            free(temp_array);
            break;
        }

        //Armazena o offset para o ínicio de cada item
        len_names = temp_array;
        len_names[i] = offset_bytes;

        system("clear");

        printf("////////// SEUS ITENS //////////\n");
        for(int i1 = 0; i1 < quantidade_itens; i1++){
            printf("%d -> %s\n", i1 + 1, ptr_itens + len_names[i1]);
            printf("--------\n");
        }

        //Offset para o ínicio do próximo item
        offset_bytes = quantidade_bytes + 1;
        i++;
    }
}


