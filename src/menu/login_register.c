#include "libs/libs.h"
#include "utils/utils.h"

void register_user(void){
    system("clear");
    char users[5][15] = {
        {"Matheus"}
    };

    char nome_usuario[15];

    FILE *f_users;
    f_users = fopen("usuarios_registrados.txt", "a+");

    printf("////////// REGISTRO DE USUÁRIO //////////\n");
    while(true){
        printf("Crie um nome de usuário[max 15 caracteres]: ");
        getname(nome_usuario, 15);

        for(int i = 0; i < 5; i++){
            printf("%s\n", users[i]);
            printf("%s\n", nome_usuario);
            printf("%d\n", (int)strlen(users[i]));
            printf("%d\n", (int)strlen(nome_usuario));
            if(strlen(users[i]) >= 1){
                printf("oi\n");
                if(strncmp(nome_usuario, users[i], strlen(nome_usuario)) == 0){
                    system("clear");
                    printf("********** USUÁRIO JÁ CADASTRADO! **********\n");
                    break;

                } else {
                    continue;
                }

            } else {
                printf("Usuário cadastrado com sucesso!\n");
                break;
            }
        }


    }
        
}