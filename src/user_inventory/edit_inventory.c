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
    int quantidade_bytes = 0;
    int offset = 0;
    int id_items = 0;
    int saved_ids;
    int contador;
    char *resposta = NULL;

    fseek(fp, ftell(fp) - sizeof(int), SEEK_END);
    fread(&quantidade_itens, sizeof(int), 1, fp);

    if(quantidade_itens != 0)
        get_inventory(fp, &name_items, &quantidade_itens, &offsets, &id_items,
                    &quantidade_bytes, &offset);

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
        validar_resposta(1, 2, escolha);
        clearstdin();

        if(escolha == 1){
            saved_ids = id_items;

            loop:
                printf("Quantos itens deseja adicionar?: ");
                scanf("%d", &contador);
                clearstdin();

                for(int i = 0; i < contador; i++){
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

                    try_realloc_offsets = realloc(offsets, quantidade_itens * sizeof(int));
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
                    id_items++;
                }

            printf("Deseja adicionar mais itens?(s/n): ");
            free_heap(resposta);
            resposta = getname(1);
            
            if(strncmp(resposta, "s", 1) == 0){
                goto loop;

            } else if(strncmp(resposta, "n", 1) == 0){
                int id;
                long offset;
                char item[20];
                int len_item;

                set_inventory_file(fp, name_items, quantidade_itens, offsets, saved_ids, username);

                rewind(fp);
                fseek(fp, ftell(fp) + sizeof(int), SEEK_SET);
                fseek(fp, ftell(fp) + strlen(username), SEEK_SET);
                printf("////////// ITENS DE %s //////////\n", username);
                fread(&quantidade_itens, sizeof(int), 1, fp);

                for(int i = 0; i < quantidade_itens; i++){
                    memset(item, 0, 20);
                    fread(&id, sizeof(int), 1, fp);
                    fread(&len_item, sizeof(int), 1, fp);
                    fread(&offset, sizeof(long), 1, fp);
                    fread(item, sizeof(char), len_item, fp);

                    printf(
                        "ID: %d\n"
                        "Offset: %ld\n"
                        "Item: %s\n",
                        id, offset, item
                    );

                    printf("---------\n");
                }
            }
            continue;

        } else if(escolha == 2){
            printf("////////// VISUALIZAR E EDITAR ESTOQUE //////////\n");
            int any;
            int verify = verify_inventory(fp);
            
            if(verify == 0){
                printf("Seu estoque está vazio, deseja adicionar algum item?(s/n)\n");
                while(true){
                    free_heap(resposta);
                    resposta = getname(1);

                    if(strncmp(resposta, "s", 1) == 0){
                        any = 0;
                        goto loop;

                    } else if(strncmp(resposta, "n", 1) == 0){
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
            free(name_item);
            free(name_items);

            fclose(fp);
            break;
        }
    }
}


