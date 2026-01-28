#include "libs/libs.h"
#include "menu/opcoes.h"
#include "utils/utils.h"
#include "menu/menu.h"

//Opção "1" o usuário pode editar e mostrar na tela os itens no seu estoque
int print_inventory(int *opcao_escolhida){
    FILE *ptr_arquivo_estoque = NULL;
    char *nome_arquivo = NULL;//Nome original
    int len_nome_arquivo;

    char *nome_arquivo_format = NULL; //Nome formatado para abrir o arquivo no programa
    char *abrir_arquivo_format = NULL; //Nome formatado para abrir o .txt no sistema

    char format_txt[7] = "%s.txt";
    int len_format_txt = strlen(format_txt);
    char format_open_txt[8] = "open %s";
    int len_format_open = strlen(format_open_txt);

    int total_len;

    while(true){
        printf("////////// GERENCIAR ESTOQUE ////////// \n");
        printf("Digite o nome do arquivo do seu estoque: ");
        
        //Usuário digita o nome do seu arquivo
        nome_arquivo = getname(15);
        len_nome_arquivo = strlen(nome_arquivo);
        
        nome_arquivo_format = alloc_mem(total_len);

        //Formata o nome do arquivo que o usuário digitou para .txt e tenta abrir o arquivo
        snprintf(nome_arquivo_format, total_len + 1, format_txt, nome_arquivo);
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
        system("clear");
        set_inventory(ptr_arquivo_estoque);

        //Nome formatado para abrir o .txt no sistema
        total_len = total_len + len_format_open;
        abrir_arquivo_format = alloc_mem(total_len);

        snprintf(abrir_arquivo_format, total_len, format_open_txt, nome_arquivo_format);
        system(abrir_arquivo_format);
    }
}

//Opção "2" o usuário pode registrar novos estoques
int register_inventory(int *opcao_escolhida){
    FILE *ptr_arquivo_estoque = NULL;
    char *nome_arquivo = NULL; //Nome original
    char *nome_arquivo_format = NULL; //Nome formatado para abrir o arquivo no programa

    char format_txt[7] = "%s.txt";
    int len_format_txt = strlen(format_txt);

    int total_len;

    while(true){
        printf("////////// CRIAR NOVO ESTOQUE ////////// \n");
        printf("Nome do seu novo estoque (Max. 15 caracteres): ");

        //Usuário digita o nome do seu arquivo
        nome_arquivo = getname(15);
        int len_nome_arquivo = strlen(nome_arquivo);
        total_len = len_nome_arquivo + len_format_txt;

        nome_arquivo_format = alloc_mem(total_len);

        //Formata o nome do arquivo que o usuário digitou para .txt e tenta abrir o arquivo
        snprintf(nome_arquivo_format, total_len + 1, format_txt, nome_arquivo);
        ptr_arquivo_estoque = fopen(nome_arquivo_format, "a+");

        //Se a criação do arquivo falhou, o usuário decide oque vai fazer
        if (ptr_arquivo_estoque == NULL){
            printf("Não foi possível criar o novo arquivo.\n");
            
            int validar;
            int resposta;
            int *ptr_resposta = &resposta;

            while(true){
                printf("Deseja tentar novamente(0) ou voltar para o menu principal(1)?: ");
                scanf("%d", ptr_resposta);
                clearstdin();

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
        system("clear");
        printf("O seu arquivo foi criado com sucesso!\n");
        printf("Aperte 'ENTER' para ser redirecionado ao menu de edição de estoque: ");
        getchar();
    
        fclose(ptr_arquivo_estoque);
        free(nome_arquivo);
    
        return *opcao_escolhida = 1;
    }
}