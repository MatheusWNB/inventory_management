#include "libs/libs.h"
#include "utils/utils.h"

void get_names(FILE *fp, long *array_offsets, int *lens, int total_names){
    long offset;
    int len;
    int id;
    char nome[15];

    for(int i = 0; i < total_names; i++){
        fread(&id, sizeof(int), 1, fp);
        fread(&lens[i], sizeof(int), 1, fp);
        fread(&array_offsets[i], sizeof(long), 1, fp);
        fread(nome, sizeof(char), lens[i], fp);

        printf(
            "Id: %d\n"
            "Nome: %s\n"
            "Len: %d\n"
            "Offset: %ld\n",
            id, nome, lens[i], array_offsets[i]
        );

        memset(nome, 0, lens[i]);
    }
}

int equal_name(FILE *fp, char *username, long *array_offsets, int *lens, int total_names){
    int validate = true;
    char nome[15];

    for(int i = 0; i < total_names; i++){
        fseek(fp, array_offsets[i], SEEK_SET);
        fread(nome, sizeof(char), lens[i], fp);
            
        if(strncmp(username, nome, strlen(username)) == 0){
            system("clear");
            printf("********** USUÁRIO JÁ CADASTRADO! **********\n");
            validate = true;
            break;

        } else{
            validate = false;
            memset(nome, 0, lens[i]);
        }
    }
    return validate;
}

char *register_user(void){
    char *nome_usuario = NULL;
    long *array_offsets = NULL; 
    int *lens = NULL;
    int total_names = 0;
    int i;
    long num_bytes;

    FILE *f_users;
    f_users = fopen("usuarios_registrados.bin", "r+b");

    int validate = verify_inventory(f_users);

    if(validate != 0){
        rewind(f_users);
        fread(&total_names, sizeof(int), 1, f_users);

        long *try_realloc = (long *) malloc(sizeof(long) * total_names);
        int *try_realloc1 = (int *) malloc(sizeof(int) * total_names);

        if(try_realloc == NULL || try_realloc1 == NULL){
            printf("********* REALLOC FALHOU **********");
            free(try_realloc);
            free(try_realloc1);
        }

        array_offsets = try_realloc;
        lens = try_realloc1;

        get_names(f_users, array_offsets, lens, total_names);
    }

    printf("////////// REGISTRO DE USUÁRIO //////////\n");

    while(true){
        printf("Crie um nome de usuário[max 15 caracteres]: ");
        //Obtém o nome que o usuário digitar
        nome_usuario = getname(15);

        if(total_names != 0){
            int validate = equal_name(f_users, nome_usuario, array_offsets, lens, total_names);

            if(validate == true)
                continue;
        }
        break;
    }

    // system("clear");
    int len = strlen(nome_usuario);

    rewind(f_users);
    total_names++;
    fwrite(&total_names, sizeof(int), 1, f_users);

    fseek(f_users, 0, SEEK_END);

    fwrite(&total_names, sizeof(int), 1, f_users);
    fwrite(&len, sizeof(int), 1, f_users);

    num_bytes = ftell(f_users) + sizeof(long);
    fwrite(&num_bytes, sizeof(long), 1, f_users);

    printf("offset %ld\n", ftell(f_users));
    fwrite(nome_usuario, sizeof(char), len, f_users);

    printf("********** USUÁRIO CADASTRADO COM SUCESSO! **********\n");

    fclose(f_users);
    return nome_usuario;
}
