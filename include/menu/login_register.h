#ifndef LOGIN_REGISTER_H
#define LOGIN_REGISTER_H

void login(void);

char *register_user(void);

void get_names(FILE *fp, long*array_offsets, int *lens, int total_names);

int equal_name(FILE *fp, char *username, long *array_offsets, int *lens, int total_names);

#endif