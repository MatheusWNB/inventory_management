#include "libs/libs.h"
#include "utils/utils.h"

//Função para limpar o buffer da entrada padrão
void clearstdin(void){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

//Limpa a quebra de linha do fgets
void limpar_quebra_linha(char *nome){
    nome[strcspn(nome, "\n")] = '\0';
}

/*
Retorna a validação da resposta do usuário com base em um intervalo de números inteiros
False = Usuário digitou uma opção fora do intervalo válido
True = Resposta do usuário é validada
*/
int validar_resposta(int a, int b, int *resposta_usuario){
    int validacao;

    if (*resposta_usuario < a || *resposta_usuario > b){
        system("clear");
        printf("********** DIGITE UMA OPÇÃO VÁLIDA! **********\n");
        validacao = false;
    }

    if (*resposta_usuario >= a && *resposta_usuario <= b)
        validacao = true;
    
    return validacao;
}

//Essa função obtém o nome que o usuário digitar de maneira mais segura
void getname(char *nome, int max_len){
    char *temp_nome = NULL;
    int tamanho = 0;
    int try_again = true;
    char c;

    loop:
        while((c = getchar()) != '\n'){
            try_again = false;

            if(tamanho >= max_len)
                break;

            char *temp = realloc(temp_nome, tamanho + 2);

            if(temp == NULL){
                printf("Realloc falhou\n");
                free(temp_nome);
                break;
            }

            temp_nome = temp;
            temp_nome[tamanho] = c;
            tamanho++;
        }

    if(try_again == true){
        system("clear");
        printf("********** DIGITE UM NOME VÁLIDO! **********\n");
        goto loop;
    }

    strcpy(nome, temp_nome);
    free(temp_nome);
    temp_nome = NULL;

    if(tamanho >= max_len)
        clearstdin();

}


