#include "libs/libs.h"
#include "menu/opcoes.h"
#include "utils/utils.h"
#include "menu/menu.h"

//Opção "1" o usuário pode editar e mostrar na tela os itens no seu estoque
int print_edit_inventory(int *opcao_escolhida){
    FILE *ptr_arquivo_estoque;
    char nome_arquivo[15]; //Nome original
    char nome_arquivo_format[50]; //Nome formatado para abrir o arquivo no programa
    char abrir_arquivo_format[200]; //Nome formatado para abrir o .txt no sistema

    clearstdin();

    while(true){
        printf("////////// GERENCIAR ESTOQUE ////////// \n");
        printf("Digite o nome do arquivo do seu estoque: ");
        
        //Usuário digita o nome do seu arquivo
        fgets(nome_arquivo, sizeof(nome_arquivo), stdin);
        limpar_quebra_linha(nome_arquivo);

        //Formata o nome do arquivo que o usuário digitou para .txt e tenta abrir o arquivo
        snprintf(nome_arquivo_format, sizeof(nome_arquivo_format), "%s.txt", nome_arquivo);
        ptr_arquivo_estoque = fopen(nome_arquivo_format, "r+"); 
        
        //Se a abertura do arquivo falhou, o usuário decide oque vai fazer
        if (ptr_arquivo_estoque == NULL){
            system("clear");
            printf("ARQUIVO INEXISTENTE!\n");

            while(true){
                int resposta;
                int *ptr_resposta = &resposta;
                int validar;

                printf("Deseja tentar novamente(0) ou criar um novo estoque(1)?: ");
                scanf("%d", ptr_resposta);

                //Valida a resposta do usuário
                validar = validar_resposta(0, 1, ptr_resposta); 

                //Usuário digitou uma opção incorreta, digite a opção novamente
                if(validar == false){
                    continue;

                } else if(validar == true){
                    //Retorna para o inicio da função atual
                    if(*ptr_resposta == 0){
                        clearstdin();
                        break;

                    //Usuário vai para a função de registro de novo estoque
                    } else if(*ptr_resposta == 1){
                        clearstdin();
                        system("clear");
                        *opcao_escolhida = 2;
                        return *opcao_escolhida;
                    }
                }
            }
            continue;
        } 
        //Nome formatado para abrir o .txt no sistema
        snprintf(abrir_arquivo_format, sizeof(nome_arquivo_format), "open %s", nome_arquivo_format);
        //Abre o arquivo .txt
        system(abrir_arquivo_format);
    }

}

int register_inventory(int *opcao_escolhida){
    FILE *ptr_arquivo_estoque;
    char nome_arquivo[15]; //Nome original
    char nome_arquivo_format[50]; //Nome formatado para abrir o arquivo no programa

    while(true){
        printf("////////// CRIAR NOVO ESTOQUE ////////// \n");
        printf("Nome do seu novo estoque (Max. 15 caracteres): ");

        fgets(nome_arquivo, sizeof(nome_arquivo), stdin);
        limpar_quebra_linha(nome_arquivo);

        //Formata o nome do arquivo que o usuário digitou para .txt e tenta abrir o arquivo
        snprintf(nome_arquivo_format, sizeof(nome_arquivo_format), "%s.txt", nome_arquivo);
        ptr_arquivo_estoque = fopen(nome_arquivo_format, "r+");

        //Se a criação do arquivo falhou, o usuário decide oque vai fazer
        if (ptr_arquivo_estoque == NULL){
            printf("Não foi possível criar o novo arquivo.\n");
            
            int validar;
            int resposta;
            int *ptr_resposta = &resposta;

            while(true){
                printf("Deseja tentar novamente(0) ou voltar para o menu principal(1)?: ");
                scanf("%d", ptr_resposta);

                //Valida a resposta do usuário
                validar = validar_resposta(0, 1, ptr_resposta);

                //Usuário digitou uma opção incorreta, digite a opção novamente
                if (validar == false){
                    continue;

                } else if (validar == true){
                    //Retorna para o inicio da função atual
                    if (*ptr_resposta == 0)
                        break;

                    //Usuário retorna para o menu
                    if (*ptr_resposta == 1){
                        *opcao_escolhida = 0;
                        return *opcao_escolhida;
                    }
                }
            }
        }

        clearstdin();
    }
}