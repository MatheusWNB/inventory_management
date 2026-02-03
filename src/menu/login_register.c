#include "libs/libs.h"
#include "utils/utils.h"

char *register_user(void){
    char *nome_usuario = NULL;
    long *array_offsets = NULL;
    int *lens = NULL;
    long *try_realloc = NULL;
    int *try_realloc1 = NULL;
    int total_names = 0;
    int i;
    int id = 1;
    long num_bytes;

    //Usuários serão registrados nesse arquivo (vou implementar)
    FILE *f_users;
    f_users = fopen("usuarios_registrados.bin", "r+b");

    int validate = verify_inventory(f_users);

    if(validate != 0){
        long offset;
        int len;

        rewind(f_users);
        fread(&total_names, sizeof(int), 1, f_users);

        for(i = 0; i < total_names; i++){
            try_realloc = (long *) realloc(array_offsets, sizeof(long) * total_names);
            try_realloc1 = (int *) realloc(lens, sizeof(int) * total_names);

            if(try_realloc == NULL || try_realloc1 == NULL){
                printf("********* REALLOC FALHOU **********");
                free(try_realloc);
                free(try_realloc1);
                break;
            }
            array_offsets = try_realloc;
            lens = try_realloc1;
            
            fread(&id, sizeof(int), 1, f_users);
            fread(&len, sizeof(int), 1, f_users);
            fread(&offset, sizeof(long), 1, f_users);

            array_offsets[i] = offset;

            num_bytes = ftell(f_users);
            fseek(f_users, num_bytes + len + 1, SEEK_SET);

            printf(
                "Id: %d\n"
                "Len: %d\n"
                "Offset: %ld\n",
                id, len, offset
            );
        }
    }

    printf("////////// REGISTRO DE USUÁRIO //////////\n");
    int loop = true;
    while(loop){
        printf("Crie um nome de usuário[max 15 caracteres]: ");
        //Obtém o nome que o usuário digitar
        nome_usuario = getname(15);

        for(i = 0; i < total_names; i++){
            char *nome = NULL;
            int validate;

            fseek(f_users, array_offsets[i], SEEK_SET);
            fread(nome, sizeof(char), lens[i], f_users);
        
            if(strncmp(nome_usuario, nome, strlen(nome_usuario)) == 0){
                system("clear");
                printf("********** USUÁRIO JÁ CADASTRADO! **********\n");
                break;
            }
        }

        loop = false;
    }
    system("clear");

    if(total_names == 0)
        fwrite(&total_names + 1, sizeof(int), 1, f_users);

    int len = strlen(nome_usuario);

    fwrite(&id, sizeof(int), 1, f_users);
    fwrite(&len, sizeof(int), 1, f_users);

    num_bytes = ftell(f_users) + 1;
    fwrite(&num_bytes, sizeof(long), 1, f_users);

    fwrite(nome_usuario, sizeof(char), strlen(nome_usuario), f_users);

    printf("********** USUÁRIO CADASTRADO COM SUCESSO! **********\n");

    fclose(f_users);
    return nome_usuario;
}
