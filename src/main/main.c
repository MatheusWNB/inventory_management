#include "libs/libs.h"
#include "menu/menu.h"
#include "menu/opcoes.h"

int main() {
    int opcao_escolhida = print_menu();

    switch(opcao_escolhida){
        case 1:
            system("clear");
            print_edit_menu();
            break;

    }

    return 0;
}