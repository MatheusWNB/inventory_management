#include "libs/libs.h"
#include "menu/menu.h"
#include "menu/opcoes.h"
#include "utils/utils.h"

int main() {
    int opcao_escolhida = 0;
    int *ptr_opcao_escolhida = &opcao_escolhida;
    int validar;

    getname2();

    //Primeira validação de escolha do usuário
    *ptr_opcao_escolhida = print_menu(ptr_opcao_escolhida);

    /* 
    Esse while gerencia todo o fluxo de escolhas conforme a necessidade
    do usuário.
    
    O while principal funciona da seguinte maneira:
    O usuário chama a primeira função, todas as escolhas 
    serão armazenadas na variável "opcao_escolhida", que será 
    referenciada em todas as funções pelo ponteiro "ptr_opcao_escolhida".

    Conforme a necessidade do usuário dentro das funções,
    ele poderá retornar para o menu de escolhas ou outras opções.

    Se a função retorna "*ptr_opcao_escolhida == 0"
    O menu principal de escolhas é chamado.

    Se a função retorna "*ptr_opcao_escolhida != 0"
    A função chamada dependerá do valor digitado pelo usuário
    */

    while(true){
        switch(*ptr_opcao_escolhida){
            /*
            Chama a função para abrir e editar os arquivos
            existentes do usuário
            */
            case 1:
                system("clear");
                print_inventory(ptr_opcao_escolhida);

                if (*ptr_opcao_escolhida != 0){
                    validar = validar_resposta(1, 3, ptr_opcao_escolhida);
                    continue;

                } else if (*ptr_opcao_escolhida == 0){
                    *ptr_opcao_escolhida = print_menu(ptr_opcao_escolhida);
                    continue;
                }

            //Chama a função para registrar um novo estoque
            case 2:
                system("clear");
                register_inventory(ptr_opcao_escolhida);

                if (*ptr_opcao_escolhida != 0){
                    validar = validar_resposta(1, 3, ptr_opcao_escolhida);
                    continue;

                } else if (*ptr_opcao_escolhida == 0){
                    *ptr_opcao_escolhida = print_menu(ptr_opcao_escolhida);
                    continue;
                }

            }
        }

    return 0;
}