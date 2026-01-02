#include "libs/libs.h"
#include "menu/opcoes.h"
#include "utils/utils.h"

//Opção "1" o usuário pode editar e mostrar na tela os itens no seu estoque
void print_edit_menu(void){
    FILE *ptr_arquivo_estoque;
    char nome_arquivo[30]; //Nome original
    char nome_arquivo_format[50]; //Nome formatado para abrir o arquivo no programa
    char abrir_arquivo_format[200]; //Nome formatado para abrir o .txt no sistema

    clearstdin();

    while(true){
        printf("Digite o nome do arquivo do seu estoque: ");
        
        //Usuário digita o nome do seu arquivo
        fgets(nome_arquivo, 20, stdin);
        limpar_quebra_linha(nome_arquivo);

        //Nome formatado para abrir o arquivo no programa
        snprintf(nome_arquivo_format, sizeof(nome_arquivo_format), "%s.txt", nome_arquivo);

        ptr_arquivo_estoque = fopen(nome_arquivo_format, "a+"); 
        
        fprintf(
            ptr_arquivo_estoque,
            "Meu nome é matheus\n"
        );

        fclose(ptr_arquivo_estoque);
        
        ptr_arquivo_estoque = fopen(nome_arquivo_format, "a+");

        //Se a abertura do arquivo falhou, o loop continua
        if (ptr_arquivo_estoque == NULL){
            system("clear");
            printf("Arquivo inexistente, tente novamente!\n");
            continue;
        } 

        //Nome formatado para abrir o .txt no sistema
        snprintf(abrir_arquivo_format, sizeof(nome_arquivo_format), "open %s", nome_arquivo_format);
        //Abre o arquivo .txt
        system(abrir_arquivo_format);
    }

}