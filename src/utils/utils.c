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
        printf("Por favor, digite uma opção válida!\n");
        validacao = false;
    }

    if (*resposta_usuario >= a && *resposta_usuario <= b)
        validacao = true;

    return validacao;
    
}

