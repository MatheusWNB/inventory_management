#include "libs/libs.h"
#include "utils/utils.h"

//Registra um novo usuário
void register_user(void){
    system("clear");
    char users[5][15] = {
        {"Matheus"}
    };

    char *nome_usuario = NULL;

    //Usuários serão registrados nesse arquivo (vou implementar)
    FILE *f_users;
    f_users = fopen("usuarios_registrados.txt", "a+");

    printf("////////// REGISTRO DE USUÁRIO //////////\n");

    int loop = true;
    while(loop){
        printf("Crie um nome de usuário[max 15 caracteres]: ");
        //Obtém o nome que o usuário digitar
        nome_usuario = getname(15);

        //Verifica se o nome de usuário já existe
        for(int i = 0; i < 5; i++){
            
            //Se tiver pelo menos um usuário ele valida
            if(strlen(users[i]) >= 1){
                //Se o usuário já existe pede o nome novamente
                if(strncmp(nome_usuario, users[i], 15) == 0){
                    system("clear");
                    printf("********** USUÁRIO JÁ CADASTRADO! **********\n");
                    break;

                } else {
                    continue;
                }

            } else {
                system("clear");
                printf("********** USUÁRIO CADASTRADO COM SUCESSO! **********\n");
                loop = false;
                break;
            }
        }
    }
}