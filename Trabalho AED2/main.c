#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Parts{
    char part_num[100];
    char name[500];
    char class[500];
    char stock[300];
    struct _Parts* next;
    struct _Parts* previous;
}Parts;

typedef struct _Parts_Sets{
    char set_num[50];
    char quantity[50];
    char part_num[50];
    struct _Parts_Sets* next;
    struct _Parts_Sets* previous;
}Parts_Sets;

typedef struct _sets{
    char set_num[500];
    char name[500];
    char year[50];
    char theme[500];
    struct _sets* next;
    struct _sets* previous;
}Sets;

typedef struct {
    char set_num[500];
    char name[500];
    char year[50];
    char theme[500];
}Aux_Sets;

typedef struct {
    char part_num[100];
    char name[500];
    char class[500];
    char stock[300];
}Aux_Parts;

typedef struct {
    char set_num[50];
    char quantity[50];
    char part_num[50];
}Aux_Parts_Sets;




//PARTS------------------------------------------------------------------------------------------
Parts * head_insert_Parts(Parts* lst, char part_num[], char name[], char class[], char stock[])
{
    Parts *new = (Parts*) malloc(sizeof(Parts));

    strcpy(new->part_num,part_num);
    strcpy(new->name,name);
    strcpy(new->class,class);
    strcpy(new->stock,stock);
    new->next = lst;
    if (new->next)
        new->next->previous = new;
    new->previous = NULL;

    return new;
}

void listar_Parts(Parts *lst) {
        for ( ; lst ; lst = lst->next ) {
            printf("%s %s %s %s\n", lst->part_num, lst->name, lst->class, lst->stock);
        }
} 






//Sets------------------------------------------------------------------------------------------
Sets * head_insert_Sets(Sets * lst, char set_num[], char name[], char year[], char theme[]) 
{
    Sets *new = (Sets*) malloc(sizeof(Sets));

    strcpy(new->set_num,set_num); 
    strcpy(new->name,name); 
    strcpy(new->year,year); 
    strcpy(new->theme,theme); 
    new->next = lst;
    if (new->next)
        new->next->previous = new;
    new->previous = NULL;

    return new;
}

void listar_Sets(Sets *lst) {
        for ( ; lst ; lst = lst->next ) {
            printf("%s %s %s %s\n",lst->set_num, lst->name, lst->year, lst->theme);
        }
} 





//Parts_Sets------------------------------------------------------------------------------------------
Parts_Sets * head_insert_PartsSets(Parts_Sets * lst, char set_num[], char quantity[], char part_num[]) 
{
    Parts_Sets *new = (Parts_Sets*) malloc(sizeof(Parts_Sets));

    strcpy(new->set_num,set_num); 
    strcpy(new->quantity,quantity); 
    strcpy(new->part_num,part_num); 
    new->next = lst;
    if (new->next)
        new->next->previous = new;
    new->previous = NULL;

    return new;
}

void listar_Parts_Sets(Parts_Sets *lst) {
        for ( ; lst ; lst = lst->next ) {
            printf("%s %s %s\n",lst->set_num, lst->set_num, lst->quantity, lst->part_num);
        }
} 

//Read files
Parts * Read_Parts(Parts *parts)
{
    FILE *file;
    int i=0;
    file = fopen("Ficheiros/parts.tsv","r");
    while (!feof(file))
    {
        char string[1000];
        char part_num[1000], name[1000], class[1000], stock[1000];

        fgets(string,1000,file);
        if(i > 0)
        {
            sscanf(string,"%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t",&part_num, &name, &class, &stock);
            strtok(stock,"\n");
            //printf("%s",string);
            parts = head_insert_Parts(parts, part_num, name, class, stock);
        }
        i++;
    }
    fclose(file);

    return parts;
}

Parts_Sets * Read_Parts_Sets(Parts_Sets *parts_Sets)
{
    FILE *file;
    int i=0;
    file = fopen("Ficheiros/parts_sets.tsv","r");
    while (!feof(file))
    {
        char string[1000];
        char part_num[50], set_num[50], quantity[50];
        fgets(string,1000,file);
        if(i > 0)
        {
            sscanf(string,"%[^\t]\t%[^\t]\t%[^\t]\t",&set_num, &quantity, &part_num);
            strtok(part_num,"\n");
            //printf("%s",string);
            parts_Sets = head_insert_PartsSets(parts_Sets, set_num, quantity, part_num);
        }
        i++;
    }
    fclose(file);

    return parts_Sets;
}

Sets * Read_Sets(Sets *sets)
{
    FILE *file;
    int i=0;
    file = fopen("Ficheiros/sets.tsv","r");
    while (!feof(file))
    {
        char string[1000];
        char set_num[1000], name[1000], year[1000], theme[1000];

        fgets(string,1000,file);
        if(i > 0)
        {
            sscanf(string,"%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t",&set_num,&name,&year,&theme);
            strtok(theme,"\n");
            //printf("%s",string);
            sets = head_insert_Sets(sets, set_num, name, year, theme);
        }
        i++;
    }
    fclose(file);

    return sets;
}

Sets * Set_by_theme(Sets *lst)
{
    char tema[100];
    int cont = 0,cont1=0;
    Aux_Sets aux_sets[100],auxx;
    Sets *aux = lst;

    for(int i = 0; i < 100;i++)
    {
        strcpy(aux_sets[i].set_num,"-");
    }

    printf("Diga o tema -> ");
    fflush(stdin);
    gets(tema);

    
    
    for ( ; aux ; aux = aux->next ) {
        if(strcmp(aux->theme,tema) == 0){
            strcpy(aux_sets[cont].set_num,aux->set_num);
            strcpy(aux_sets[cont].name,aux->name);
            strcpy(aux_sets[cont].year,aux->year);
            strcpy(aux_sets[cont].theme,aux->theme);
            cont++;
        }
    }
    
    for(int x = 0; x < 100; x++)
    {
        if(!(strcmp(aux_sets[x].set_num,"-") == 0)){
            for(int j = 0; j < 100; j++)
            {   
                if(!(strcmp(aux_sets[j].set_num,"-") == 0))
                {
                    int year1 = atoi(aux_sets[x].year);
                    int year2 = atoi(aux_sets[j].year);
                    if( year1 < year2)
                    {
                        auxx = aux_sets[x];
                        aux_sets[x] = aux_sets[j];
                        aux_sets[j] = auxx;
                    }
                }
            }
        }
    }
 
    if(cont == 0)
    {
        printf("NADA");
    }
    else
    {
        for(int i = 0; i < 100;i++)
        {
            if(!(strcmp(aux_sets[i].set_num,"-") == 0))
                printf("%s | %s | %s | %s\n",aux_sets[i].year, aux_sets[i].set_num, aux_sets[i].name, aux_sets[i].theme);
        }
    }
    return lst;
}

void Parts_of_Sets(Parts_Sets *parts_sets)
{
    char conjunto[500];
    int cont=0;
    Aux_Parts_Sets aux_parts_sets[100];
    Parts_Sets *aux = parts_sets;

    for(int i=0;i<100;i++)
    {
        strcpy(aux_parts_sets[i].set_num,"-");
    }

    printf("Diga o Numero do conjunto ->");
    fflush(stdin);
    gets(conjunto);

    for ( ; aux ; aux = aux->next ) {
        if(strcmp(aux->set_num,conjunto) == 0){
            strcpy(aux_parts_sets[cont].set_num,aux->set_num);
            strcpy(aux_parts_sets[cont].quantity,aux->quantity);
            strcpy(aux_parts_sets[cont].part_num,aux->part_num);
            cont++;
        }
    }

    if(cont == 0)
    {
        printf("Nada");
    }
    else
    {
        for (int i = 0; i < 100; i++)
        {
            if(!(strcmp(aux_parts_sets[i].set_num,"-")==0))
            {
                printf("%s | %s | %s\n",aux_parts_sets[i].set_num,aux_parts_sets[i].quantity,aux_parts_sets[i].part_num);
            }
        }
        
    }
}

void parts_needed(Parts_Sets *parts_sets,Parts *parts)
{
    char conjunto[500];
    int cont=0;
    Aux_Parts_Sets aux_parts_sets[100];

    for(int i=0;i<100;i++)
    {
        strcpy(aux_parts_sets[i].set_num,"-");
    }

    printf("Diga o Numero do conjunto ->");
    fflush(stdin);
    gets(conjunto);

    for ( ; parts_sets ; parts_sets = parts_sets->next ) {
        if(strcmp(parts_sets->set_num,conjunto) == 0){
            strcpy(aux_parts_sets[cont].set_num,parts_sets->set_num);
            strcpy(aux_parts_sets[cont].quantity,parts_sets->quantity);
            strcpy(aux_parts_sets[cont].part_num,parts_sets->part_num);
            cont++;
        }
    }

    if(cont == 0)
    {
        printf("Nada");
    }
    else
    {
        for (int x = 0; x < 100; x++)
        {
            if(!(strcmp(aux_parts_sets[x].set_num,"-")==0))
            {
                Parts *aux = parts;
                for ( ; aux ; aux = aux->next ) {
                    if(strcmp(aux_parts_sets[x].part_num,aux->part_num) == 0)
                    {
                        printf("%s | %s | %s | %s\n",aux->part_num,aux->name,aux->class,aux->stock);
                    }
                } 
            }
        }   
    }
}

void Total_Stock(Parts *parts)
{
    Parts *aux = parts;
    int cont = 0,cont1 = 0;

    for ( ; aux ; aux = aux->next ) {
        int stock = atoi(aux->stock);
        if(stock>0)
        {
            cont++;
        }
    }

    printf("O total de pecas em stock e de %d\n\n",cont);
}

void Total_Parts_Sets(Parts_Sets *parts_sets)
{
    char conjunto[100];
    Parts_Sets *aux_parts_sets = parts_sets;
    int cont=0;

    printf("\n\nDiga o Numero do conjunto ->");
    fflush(stdin);
    gets(conjunto);

    for ( ; aux_parts_sets ; aux_parts_sets = aux_parts_sets->next ) {
        if(strcmp(aux_parts_sets->set_num,conjunto) == 0){
            cont++;
        }
    }

    printf("O total de pecas neste conjunto e de %d.\n\n",cont);
}

int main() {
    Parts_Sets *parts_sets = NULL;
    Parts *parts = NULL;
    Sets *sets = NULL;
    int op = 0,op1 = 0;
    char tema[100];

    sets = Read_Sets(sets);
    parts_sets = Read_Parts_Sets(parts_sets);
    parts = Read_Parts(parts);

    do
    {
        printf("\n1 - Listar");
        printf("\n2 - Conjuntos por ano");
        printf("\n3 - Pecas de um conjunto");
        printf("\n4 - Pecas Necessarias");
        printf("\n5 - Total Stock");
        printf("\n6 - Total de pecas de um conjunto");
        printf("\n0 - Sair");
        printf("\nOpcao-> ");
        scanf("%d",&op);
        switch (op)
        {
            case 1:
            do
            {
                printf("\n\n1 - Parts");
                printf("\n2 - Sets");
                printf("\n3 - Parts_Sets");
                printf("\n0 - Voltar");
                printf("\nOpcao-> ");
                scanf("%d",&op1);
                switch(op1)
                {
                    case 1: listar_Parts(parts); break;
                    case 2: listar_Sets(sets); break;
                    case 3: listar_Parts_Sets(parts_sets); break;
                }
            } while (op1 < 1 && op1 > 3 || op1 != 0);
            printf("\n");
            break;
            case 2: sets = Set_by_theme(sets); break; 
            case 3: Parts_of_Sets(parts_sets); break; 
            case 4: parts_needed(parts_sets,parts); break;   
            case 5: Total_Stock(parts); break;   
            case 6: Total_Parts_Sets(parts_sets); break;   
            case 0: printf("Adeus"); break;
        }

    } while (op < 1 && op > 3 || op != 0);
    
    return 0;
}