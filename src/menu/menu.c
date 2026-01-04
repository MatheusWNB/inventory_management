#include "libs/libs.h"
#include "menu/menu.h"
#include "utils/utils.h"

int print_menu(int *opcao_escolhida){

    printf(
        "Olá, seja bem-vindo ao gerenciador de estoque!\n"
        "Para iniciarmos digite os seus dados de login ou crie uma nova conta:\n"
    );

    /*
    Sistema de validação básico de login (Vou implementar)
    */

    putchar('\n');
    //Usuário seleciona uma opção do menu e a resposta é validada
    while(true){
        int validar;

        printf(
            "///////// MENU //////////\n"
            "(1) Visualizar e editar estoques registrados\n"
            "(2) Registrar um novo estoque\n"
            "(3) Visualizar e editar os seus dados\n"
        );

        printf("Selecione uma opção: ");
        scanf("%d", opcao_escolhida);

        //Valida a resposta do usuário
        validar = validar_resposta(1, 3, opcao_escolhida);

        if (validar == false){
            continue;
        }

        //A opção que o usuário escolheu é retornada para a main
        clearstdin();
        return *opcao_escolhida;
    }
    
    

}