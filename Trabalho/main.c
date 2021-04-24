#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Parts{
    char part_num[20];
    char name[300];
    char class[50];
    char stock[50];
    struct _Parts* next;
}Parts;


typedef struct _Parts_Sets{
    char set_num[50];
    char quantity[5];
    char part_num[50];
    struct _Parts_Sets* next;
}Parts_Sets;

typedef struct _sets{
    char set_num[20];
    char name[300];
    char year[50];
    char theme[50];
    struct _sets* next;
}Sets;

//Head Instert
Parts * head_insert_parts(Parts* parts, char *part_num, char *name, char *class, char *stock) {
    Parts *tmp = (Parts*) malloc(sizeof(Parts));

    strcpy(tmp->part_num, part_num);
    strcpy(tmp->name, name);
    strcpy(tmp->class, class);
    strcpy(tmp->stock, stock);
    tmp->next = parts;

    return tmp;
}

Parts_Sets * head_insert_Parts_sets(Parts_Sets * parts_sets, char *set_num, char *quantity, char *part_num) {
    Parts_Sets *tmp = (Parts_Sets*) malloc(sizeof(Parts_Sets));

    strcpy(tmp->part_num, part_num);
    strcpy(tmp->set_num, set_num);
    strcpy(tmp->quantity, quantity);
    tmp->next = parts_sets;

    return tmp;
}

Sets * head_insert_sets(Sets * sets, char *set_num, char *name, char *year, char *theme) {
    Sets *tmp = (Sets*) malloc(sizeof(Sets));

    strcpy(tmp->set_num, set_num);
    strcpy(tmp->name, name);
    strcpy(tmp->year, year);
    strcpy(tmp->theme, theme);
    tmp->next = sets;

    return tmp;
}

//Visiti Lists
void visit_list_rec_Parts(Parts *parts) {
    if (parts) {
        printf("%s %s %s %s",parts->part_num,parts->name,parts->class,parts->stock);
        printf("\n");
        visit_list_rec_Parts(parts->next);
    } else
        printf("\n");
}

void visit_list_rec_Parts_Sets(Parts_Sets * parts_sets) {
    if (parts_sets) {
        printf("%s %s %s",parts_sets->set_num,parts_sets->quantity,parts_sets->part_num);
        printf("\n");
        visit_list_rec_Parts_Sets(parts_sets->next);
    } else
        printf("\n");
}

void visit_list_rec_Sets(Sets * sets) {
    if (sets) {
        printf("%s %s %s %s",sets->set_num,sets->name,sets->year,sets->theme);
        //printf("\n");
        visit_list_rec_Sets(sets->next);
    } else
        printf("\n");
}

//Read files
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
        parts = head_insert_parts(parts, part_num, name, class, stock);
    }
    fclose(file);

    return parts;
}

Parts_Sets * Read_Parts_Sets(Parts_Sets *parts_Sets)
{
    FILE *file;
    file = fopen("../Files/parts_sets.tsv","r");
    while (!feof(file))
    {
        char part_num[300];
        char set_num[300];
        char quantity[300];

        fscanf(file,"%[^\t]\t%[^\t]\t%[^\t]\t",&set_num, &quantity, &part_num);
        parts_Sets = head_insert_Parts_sets(parts_Sets, set_num, quantity, part_num);
    }
    fclose(file);

    return parts_Sets;
}

Sets * Read_Sets(Sets *sets)
{
    FILE *file;
    file = fopen("../Files/sets.tsv","r");
    while (!feof(file))
    {
        char set_num[300];
        char name[300];
        char year[300];
        char theme[300];

        fscanf(file,"%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t",&set_num, &name, &year, &theme);
        sets = head_insert_sets(sets, set_num, name, year, theme);
    }
    fclose(file);

    return sets;
}
int main() {
    Parts_Sets *parts_Sets = NULL;
    Parts *parts = NULL;
    Sets *sets = NULL;
    /*
    parts = ReadParts(parts);
    visit_list_rec_Parts(parts);
    */

    /*
    parts_Sets = Read_Parts_Sets(parts_Sets);
    visit_list_rec_Parts_Sets(parts_Sets);
    */

    sets = Read_Sets(sets);
    visit_list_rec_Sets(sets);
    return 0;
}
