#include "libs/libs.h"
#include "utils/utils.h"
#include "menu/opcoes.h"

void edit_inventory(FILE *fp){

    printf("////////// EDITOR DE ESTOQUES //////////\n");
    printf("Quais itens você gostaria de registrar no seu estoque? (max. 100 por estoque): \n");

    int i = 0;
    int quantidade_bytes;
    char *ptr_itens;
    
    while(i < 100){
        char nome_item[15];    
        printf("Item a ser registrado(max. 15 caracteres por item): ");
        getname(nome_item, 15);
        int len_name = strlen(nome_item);

        if(i == 0)
            ptr_itens = malloc(len_name* sizeof(char));
        else
            ptr_itens = realloc(ptr_itens, quantidade_bytes);

        strcpy(ptr_itens[len_name + 1], nome_item);
        quantidade_bytes = quantidade_bytes + len_name;
        i++;
        printf("%s\n", ptr_itens);
    }

}

    // while(true){
    //     scanf("%d", &quantidade_itens);
    //     int validacao = validar_resposta(1, 100, &quantidade_itens);

    //     if(validacao == false)
    //         continue;
    //     else if(validacao == true)
    //         buffer_itens += quantidade_itens;

    //     break;
    // }

