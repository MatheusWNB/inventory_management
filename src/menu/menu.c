#include "libs/libs.h"
#include "menu/menu.h"
#include "utils/utils.h"
#include "menu/login_register.h"

int print_menu(){
    int validar;
    int opcao_escolhida;

    while(true){
        printf(
            "///////// MENU //////////\n"
            "(1) Visualizar e editar estoques registrados\n"
            "(2) Registrar um novo estoque\n"
            "(3) Visualizar e editar os seus dados\n"
        );

        printf("Selecione uma opção: ");
        scanf("%d", &opcao_escolhida);

        validar = validar_resposta(1, 3, opcao_escolhida);

        if(validar == false)
            continue;

        //A opção que o usuário escolheu é retornada para a main
        clearstdin();
        return opcao_escolhida;
    }
}