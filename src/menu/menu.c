#include "libs.h"
#include "menu.h"

int print_menu(void){
    int resposta;

    printf(
        "Olá, seja bem-vindo ao gerenciador de estoque!\n"
        "Para iniciarmos digite os seus dados de login ou crie uma nova conta:\n"
    );

    //
    // Sistema de validação básico de login (Vou implementar)
    //

    //Usuário seleciona uma opção do menu e a resposta é validada
    while(true){
        printf(
            "///////// MENU //////////\n"
            "(1) Visualizar e editar estoques registrados\n"
            "(2) Registrar um novo estoque\n"
            "(3) Visualizar e editar os seus dados\n"
        );

        printf("Selecione uma opção: ");
        scanf("%d", &resposta);

        if (resposta < 1 || resposta > 3){
            system("clear");
            printf("Por favor, digite uma opção válida!");
            continue;
        }

        //A opção que o usuário escolheu é retornada para a main
        return resposta;
    }
    
    

}