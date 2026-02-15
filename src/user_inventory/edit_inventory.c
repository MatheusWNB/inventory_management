#include "libs/libs.h"
#include "utils/utils.h"
#include "user_inventory/user_inventory.h"
#include "menu/opcoes.h"

void allocate_inventory(FILE *fp, char *username){
    char *name_items = NULL;
    char *try_realloc_items = NULL;
    char *name_item = NULL;

    int *offsets = NULL;
    int *try_realloc_offsets = NULL;

    int quantidade_itens = 0;
    int quantidade_bytes = strlen(username);
    int offset = 0;
    int id_items = 0;

    char *resposta1 = NULL;
    char *resposta2 = NULL;

    while(true){
        printf("////////// EDITOR DE ESTOQUES //////////\n");
        printf(
            "Qual operação você deseja realizar?\n"
            "(1)Adicionar itens ao meu estoque\n"
            "(2)Visualizar e editar meu estoque\n"
            "(3)Fechar editor\n"
        );

        printf("Sua escolha: ");
        int escolha;
        scanf("%d", &escolha);
        validar_resposta(1, 2, &escolha);
        clearstdin();

        if(escolha == 1){
            loop:
                int contador;
                int i = 0;

                printf("Quantos itens deseja adicionar?: ");
                scanf("%d", &contador);
                clearstdin();

                while(i < contador){
                    printf("Item a ser registrado(max. 20 caracteres por item): ");
                    name_item = getname(20);
                    int len_name = strlen(name_item) + 1;
                    quantidade_bytes += len_name;

                    try_realloc_items = (char *)realloc(name_items, quantidade_bytes + 1);
                    if(try_realloc_items == NULL){
                        system("clear");
                        printf("********** REGISTRO DE ITEM FALHOU **********\n");
                        free(try_realloc_items);
                        break;
                    }
                    //Copia o nome do item para o começo do novo endereço realocado
                    name_items = try_realloc_items;
                    strcpy(name_items + offset, name_item);
                    quantidade_itens++;

                    int *try_realloc_offsets = realloc(offsets, quantidade_itens * sizeof(int));
                    if(try_realloc_offsets == NULL){
                        system("clear");
                        printf("********** REGISTRO DE LEN FALHOU **********\n");
                        free(try_realloc_offsets);
                        break;
                    }
                    //Armazena o offset para o ínicio de cada item
                    offsets = try_realloc_offsets;
                    offsets[id_items] = offset;

                    system("clear");

                    printf("////////// SEUS ITENS //////////\n");
                    for(int i1 = 0; i1 < quantidade_itens; i1++){
                        printf("%d -> %s\n", i1 + 1, name_items + offsets[i1]);
                        printf("--------\n");
                    }
                    //Offset para o ínicio do próximo item
                    offset = quantidade_bytes + 1;
                    i++;
                    id_items++;
                }

            printf("Deseja adicionar mais itens?(s/n): ");
            char *resposta1 = getname(1);
            
            if(strncmp(resposta1, "s", 1) == 0){
                goto loop;

            } else if(strncmp(resposta1, "n", 1) == 0){
                set_inventory_file(fp, username, name_items, quantidade_itens, offsets);

                char nome[20];
                int id;
                long offset;
                char *item = NULL;
                rewind(fp);
                fread(nome, sizeof(char), strlen(username), fp);
                printf("////////// ITENS DE %s //////////\n", nome);
                for(int i = 0; i < quantidade_itens; i++){
                    fread(&id, sizeof(int), 1, fp);
                    fread(&offset, sizeof(long), 1, fp);
                    item = (char *)malloc(strlen(name_items + offsets[i] * sizeof(char)));
                    fread(item, sizeof(char), strlen(name_items + offsets[i]), fp);

                    printf(
                        "ID: %d\n"
                        "Offset: %ld\n"
                        "Item: %s\n",
                        id, offset, item
                    );

                    printf("---------\n");
                    item = NULL;
                }
                free(item);
                item = NULL;
            }
            continue;

        } else if(escolha == 2){
            printf("////////// VISUALIZAR E EDITAR ESTOQUE //////////\n");
            int any;
            int verify = verify_inventory(fp);
            
            if(verify == 0){
                printf("Seu estoque está vazio, deseja adicionar algum item?(s/n)\n");
                while(true){
                    resposta2 = getname(1);

                    if(strncmp(resposta2, "s", 1) == 0){
                        any = 0;
                        goto loop;

                    } else if(strncmp(resposta2, "n", 1) == 0){
                        any = 1;
                        break;
                    } else{
                        printf("********** DIGITE UMA RESPOSTA VÁLIDA (s/n) **********");
                        continue;
                    }
                }
            }
            if(any == 1)
                continue;

            system("clear");
            printf("////////// SEUS ITENS //////////\n");

            for(int i1 = 0; i1 < quantidade_itens; i1++){
                printf("%d -> %s\n", i1 + 1, name_items + offsets[i1]);
                printf("--------\n");
            }

            getchar();
                
        } else if(escolha == 3){
            system("clear"); 
            printf("********** FECHANDO O EDITOR DE ESTOQUE **********\n");

            free(offsets);
            offsets = NULL;

            free(name_item);
            name_item = NULL;

            free(name_items);
            name_items = NULL;

            free(resposta1);
            resposta1 = NULL;

            free(resposta2);
            resposta2 = NULL;

            fclose(fp);
            break;
        }
    }
}


