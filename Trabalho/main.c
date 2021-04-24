#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SEPARADOR -14
#define SEPARADORNAME -50
#define SEPARADORID -6

typedef struct {
    char part_num[20];
    char name[100];
    char class[50];
    char stock[50];
}Parts;

void ReadParts()
{
    FILE *file;
    Parts p;

    file = fopen("../Files/parts.tsv","r");
    int x=0;
    while (!feof(file))
    {
        fscanf(file,"%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t",&p.part_num, &p.name, &p.class, &p.stock);
        printf("%s | %s | %s | %s\n",p.part_num,p.name,p.class,p.stock);
    }

    printf("\n");
    fclose(file);
}


int main() {
    ReadParts();
    return 0;
}
