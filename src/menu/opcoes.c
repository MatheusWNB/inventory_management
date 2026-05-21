#include "libs/libs.h"
#include "menu/opcoes.h"
#include "utils/utils.h"
#include "user_inventory/user_inventory.h"
#include "menu/menu.h"

int print_inventory(char *nome){
    FILE *fileptr = NULL;
    char *nome_arquivo = NULL;

    char *nome_arquivo_format = NULL; //Nome formatado para abrir o arquivo no programa
    char format_txt[] = "%s.bin";
    int len_format_txt = strlen(format_txt);

    int opcao_escolhida;

    while(true){
        printf("////////// GERENCIAR ESTOQUE ////////// \n");
        printf("Digite o nome do arquivo do seu estoque: ");
        
        nome_arquivo = getname(15);
        int len_nome_arquivo = strlen(nome_arquivo);
        int total_len = len_nome_arquivo + len_format_txt;
        nome_arquivo_format = alloc_mem(total_len);

        //Formata o nome do arquivo que o usuário digitou para .txt e tenta abrir o arquivo
        snprintf(nome_arquivo_format, total_len + 1, format_txt, nome_arquivo);
        fileptr = fopen(nome_arquivo_format, "r+b");

        //Se a abertura do arquivo falhou, o usuário decide oque vai fazer
        if (fileptr == NULL){
            system("clear");
            printf("ARQUIVO INEXISTENTE!\n");

            while(true){
                int resposta;
                int validar;

                printf("Deseja tentar novamente(0) ou criar um novo estoque(1)?: ");
                scanf("%d", &resposta);
                validar = validar_resposta(0, 1, resposta); 

                if(validar == false){
                    continue;

                } else if(validar == true){
                    //Retorna para o inicio da função atual
                    if(resposta == 0){
                        clearstdin();
                        break;

                    //Usuário vai para a função de registro de novo estoque
                    } else if(resposta == 1){
                        clearstdin();
                        system("clear");
                        opcao_escolhida = 2;
                        return opcao_escolhida;
                    }
                }
            }
            continue;
        }

        int len_name;
        fread(&len_name, sizeof(int), 1, fileptr);

        char name_in_file[15];
        fread(name_in_file, sizeof(char), len_name, fileptr);
        name_in_file[1] = '\0';
        
        if(strncmp(name_in_file, nome, 15) == 1){
            system("clear");
            printf("********** VOCÊ NÃO TEM PERMISSÃO PARA ACESSAR ESSE ARQUIVO! **********");
            break;
        }
        
        system("clear");
        printf("%d\n", len_name);
        printf("%s\n", name_in_file);
        allocate_inventory(fileptr, nome);
        break;
    }
    
    free(nome_arquivo);
    free(nome_arquivo_format);

    return opcao_escolhida = 0;
}

int register_inventory(char *nome){
    FILE *fileptr = NULL;
    char *nome_arquivo = NULL;

    char *nome_arquivo_format = NULL; //Nome formatado para abrir o arquivo no programa
    char format_txt[] = "%s.bin";
    int len_format_txt = strlen(format_txt);

    int opcao_escolhida, len_nome_arquivo, total_len;
    
    while(true){
        printf("////////// CRIAR NOVO ESTOQUE ////////// \n");
        printf("Nome do seu novo estoque (Max. 15 caracteres): ");

        //Usuário digita o nome do seu arquivo
        nome_arquivo = getname(15);
        len_nome_arquivo = strlen(nome_arquivo);
        total_len = len_nome_arquivo + len_format_txt;

        nome_arquivo_format = alloc_mem(total_len);

        //Formata o nome do arquivo que o usuário digitou para .bin e tenta abrir o arquivo
        snprintf(nome_arquivo_format, total_len + 1, format_txt, nome_arquivo);
        fileptr = fopen(nome_arquivo_format, "a+b");

        //Se a criação do arquivo falhou, o usuário decide oque vai fazer
        if(fileptr == NULL){
            int validar;
            int resposta;

            printf("Não foi possível criar o novo arquivo.\n");

            while(true){
                printf("Deseja tentar novamente(0) ou voltar para o menu principal(1)?: ");
                scanf("%d", &resposta);
                clearstdin();

                validar = validar_resposta(0, 1, resposta);

                if (validar == false){
                    continue;

                } else if (validar == true){
                    //Retorna para o inicio da função atual
                    if (resposta == 0)
                        break;

                    //Usuário retorna para o menu
                    else if(resposta == 1)
                        return opcao_escolhida = 0;
                }
            }
        }

        system("clear");
        printf("O seu arquivo foi criado com sucesso!\n");
        printf("Aperte 'ENTER' para ser redirecionado ao menu de edição de estoque: ");
        getchar(); 

        int len_name = strlen(nome);
        fwrite(&len_name, sizeof(int), 1, fileptr);
        fwrite(nome, sizeof(char), len_name, fileptr);
        int total = 0;
        fwrite(&total, sizeof(int), 1, fileptr);

        fclose(fileptr);
        free(nome_arquivo);
        free(nome_arquivo_format);

        return opcao_escolhida = 1;
    }
}