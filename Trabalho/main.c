#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SEPARADOR -14
#define SEPARADORNAME -50
#define SEPARADORID -6

typedef struct _Parts{
    char part_num[20];
    char name[300];
    char class[50];
    char stock[50];
    struct _Parts* next;
}Parts;

Parts * head_insert(Parts* parts, char *part_num, char *name, char *class, char *stock) {
    Parts *tmp = (Parts*) malloc(sizeof(Parts));

    strcpy(tmp->part_num, part_num);
    strcpy(tmp->name, name);
    strcpy(tmp->class, class);
    strcpy(tmp->stock, stock);
    tmp->next = parts;

    return tmp;
}

Parts * ReadParts(Parts *parts)
{
    FILE *file;
    file = fopen("../Files/parts.tsv","r");
    while (!feof(file))
    {
        char part_num[300];
        char name[300];
        char class[300];
        char stock[300];

        fscanf(file,"%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t",&part_num, &name, &class, &stock);
        printf("olA   ");
        parts = head_insert(parts, part_num, name, class, stock);
    }
    printf("\n");
    fclose(file);

    return parts;
}

void visit_list_rec(Parts *parts) {
    if (parts) {
        printf("%s %s %s %s",parts->part_num,parts->name,parts->class,parts->stock);
        printf("\n");
        visit_list_rec(parts->next);
    } else
        printf("\n");
}
int main() {
    Parts *parts = NULL;
    parts = ReadParts(parts);
    visit_list_rec(parts);
    return 0;
}
