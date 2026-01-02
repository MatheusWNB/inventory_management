#include "libs/libs.h"
#include "menu/opcoes.h"
#include "utils/utils.h"

void print_edit_menu(void){
    FILE *arquivo_estoque;
    char nome_arquivo_estoque[20];

    while(true){
        printf("Digite o nome do arquivo do seu estoque: ");
        
        clearstdin();
        fgets(nome_arquivo_estoque, 20, stdin);

        arquivo_estoque = fopen(("home/matheuswnb/c_tests/%s", nome_arquivo_estoque), "r+");

        if (arquivo_estoque == NULL){
            system("clear");
            printf("Arquivo inexistente, tente novamente!\n");
            continue;
        } 

        system(("open home/matheuswnb/c_tests/%s", nome_arquivo_estoque));
    }

}