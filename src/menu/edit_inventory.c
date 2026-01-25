#include "libs/libs.h"
#include "utils/utils.h"
#include "menu/opcoes.h"

void set_inventory(FILE *fp){
    char *name_itens = NULL;
    char *temp_itens = NULL;
    char *name_item = NULL;

    int *len_names = NULL;
    int *temp_len = NULL;

    int quantidade_itens = 0;
    int quantidade_bytes = 0;
    int offset_bytes = 0;
    int i_anterior = 0;

    printf("////////// EDITOR DE ESTOQUES //////////\n");

    int contador;
    
    loop:
        int i = 0;
        printf("Quantos itens deseja adicionar?: ");
        scanf("%d", &contador);
        clearstdin();

        while(i < contador){
            printf("Item a ser registrado(max. 20 caracteres por item): ");
            name_item = getname(20);
            int len_name = strlen(name_item) + 1;
            quantidade_bytes += len_name;

            temp_itens = (char *)realloc(name_itens, quantidade_bytes + 1);
            if(temp_itens == NULL){
                system("clear");
                printf("********** REGISTRO DE ITEM FALHOU **********\n");
                free(temp_itens);
                break;
            }

            //Copia o nome do item para o começo do novo endereço realocado
            name_itens = temp_itens;
            strcpy(name_itens + offset_bytes, name_item);
            quantidade_itens++;

            int *temp_len = realloc(len_names, quantidade_itens * sizeof(int));
            if(temp_len == NULL){
                system("clear");
                printf("********** REGISTRO DE LEN FALHOU **********\n");
                free(temp_len);
                break;
            }

            //Armazena o offset para o ínicio de cada item
            len_names = temp_len;
            len_names[i_anterior] = offset_bytes;

            system("clear");

            printf("////////// SEUS ITENS //////////\n");
            for(int i1 = 0; i1 < quantidade_itens; i1++){
                printf("%d -> %s\n", i1 + 1, name_itens + len_names[i1]);
                printf("--------\n");
            }

            //Offset para o ínicio do próximo item
            offset_bytes = quantidade_bytes + 1;
            i++;
            i_anterior++;
        }

    printf("Deseja adicionar mais itens?(s/n): ");
    char *resposta = getname(1);
    
    if(strncmp(resposta, "s", 1) == 0){
        goto loop;
    } else if(strncmp(resposta, "n", 1) == 0){
        fprintf(fp, "////////// SEUS ITENS //////////\n");
        for(int i1 = 0; i1 < quantidade_itens; i1++){
            fprintf(fp,
                "%d -> %s\n"
                "---------\n", i1 + 1, name_itens + len_names[i1]
            );
        }

        free(len_names);
        free(name_item);
        free(name_itens);

        fclose(fp);
    }
}


