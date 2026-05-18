#include "libs/libs.h"
#include "menu/menu.h"
#include "menu/opcoes.h"
#include "utils/utils.h"
#include "menu/login_register.h"

int main() {
    int opcao_escolhida = 0;
    char *name = NULL;
    
    printf(
        "Olá, seja bem-vindo ao gerenciador de estoque!\n"
        "Para iniciarmos digite os seus dados de login(0) ou crie uma nova conta(1):\n"
    );

    scanf("%d", &opcao_escolhida);
    clearstdin();

    name = login_register(opcao_escolhida);
    putchar('\n');

    //Primeira validação de escolha do usuário
    opcao_escolhida = print_menu();

    /* 
    Esse while gerencia todo o fluxo de escolhas conforme a necessidade
    do usuário.
    
    Conforme a necessidade do usuário dentro das funções,
    ele poderá retornar para o menu de escolhas ou outras opções.

    Se a função retorna "opcao_escolhida == 0"
    O menu principal de escolhas é chamado.

    Se a função retorna "opcao_escolhida != 0"
    A função chamada dependerá do valor digitado pelo usuário
    */

    while(true){
        switch(opcao_escolhida){
            /*
            Chama a função para abrir e editar os arquivos
            existentes do usuário
            */
            case 1:
                system("clear");
                opcao_escolhida = print_inventory(name);

                if(opcao_escolhida != 0)
                    validar_resposta(1, 3, opcao_escolhida);

                else if(opcao_escolhida == 0)
                    opcao_escolhida = print_menu();

                break;

            //Chama a função para registrar um novo estoque
            case 2:
                system("clear");
                opcao_escolhida = register_inventory(name);

                if(opcao_escolhida != 0)
                    validar_resposta(1, 3, opcao_escolhida);

                else if(opcao_escolhida == 0)
                    opcao_escolhida = print_menu();

                break;
            }
        }
    return 0;
}