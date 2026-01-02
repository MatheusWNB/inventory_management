#include "libs/libs.h"
#include "utils/utils.h"

//Função para limpar o buffer da entrada padrão
void clearstdin(void){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
