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

//Essa função obtém o nome que o usuário digitar de maneira mais segura
void getname(char *nome, int max_len){
    #define BUFFER 1024 //Limite máximo de caracteres do buffer
    char buffer_name[BUFFER]; //Buffer temporário para a variável "nome"

    while(true){
        //Obtém o nome do usuário e armazena em buffer
        fgets(buffer_name, BUFFER, stdin); 
        
        //Se buffer_name não for um "enter" ele entra
        if (buffer_name[0] != '\n'){
            size_t len = strlen(buffer_name);

            /*
            Variável nome obtém os caracters do buffer_name
            max_len determina a quantidade de caracteres escritos
            */
            snprintf(nome, max_len + 1, "%s", buffer_name);

            //Se o limite do buffer for ultrapassado limpa o buffer
            if (len > 0 && buffer_name[len - 1] != '\n')
                clearstdin();

            /*
            Se oque o suário digitou for menor que max_len
            limpa quebra de linha
            */
            if (len < (unsigned)(max_len))
                limpar_quebra_linha(nome);
            
            break;
        
        //Loop continua se usuário não digitou nada
        } else {
            system("clear");
            printf("********** DIGITE UM NOME VÁLIDO! **********\n");
            limpar_quebra_linha(buffer_name);
            continue;
        }
    }
}


