#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <math.h>

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

typedef struct _Aux_Parts{
    char part_num[100];
    int cont;
    struct _Aux_Parts* next;
}Aux_Parts;

typedef struct _list {
    Aux_Parts* first;
    Aux_Parts* last;
} List_Parts;

typedef struct _list_Parts {
    Parts* first;
    Parts* last;
} List_Parts_Parts;

typedef struct _list_Parts_Sets {
    Parts_Sets* first;
    Parts_Sets* last;
} List_Parts_Sets;

typedef struct _list_Sets {
    Sets* first;
    Sets* last;
} List_Sets;

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
    Parts *aux = lst;
    int cont = 0;
    system("cls || clear");
    for ( ; aux ; aux = aux->next ) {
        cont++;
        printf("%s %s %s %s\n", aux->part_num, aux->name, aux->class, aux->stock);
    }
    printf("%d ",cont);
    system("pause");
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
    Sets *aux = lst;
    int cont = 0;
    system("cls || clear");
    for ( ; aux ; aux = aux->next ) {
        cont++;
        printf("%s %s %s %s\n",aux->set_num, aux->name, aux->year, aux->theme);
    }
    printf("%d ",cont);
    system("pause");
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
    Parts_Sets *aux = lst;
    int cont=0;
    system("cls || clear");
    for ( ; aux ; aux = aux->next ) {
        cont++;
        printf("%s %s %s\n",aux->set_num, aux->set_num, aux->quantity, aux->part_num);
    }
    printf("-----> %d\n",cont);
    system("pause");
} 

//Read files
Parts * Read_Parts(Parts *parts,List_Parts_Parts* list)
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
            tail_insert_AUX_Parts(parts,list);
        }
        i++;
    }
    fclose(file);

    return parts;
}

Parts_Sets * Read_Parts_Sets(Parts_Sets *parts_Sets,List_Parts_Parts* list)
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
            tail_insert_Parts_Sets(parts_Sets,list);
        }
        i++;
    }
    fclose(file);

    return parts_Sets;
}

Sets * Read_Sets(Sets *sets,List_Sets *list)
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
            tail_insert_AUX_Sets(sets, list);
        }
        i++;
    }
    fclose(file);
    return sets;
    
}

Sets * Set_by_theme(Sets *lst)
{
    system("cls || clear");
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
    system("pause");
    return lst;
}

void Parts_of_Sets(Parts_Sets *parts_sets)
{
    system("cls || clear");
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
    system("pause");
}

void parts_needed(Parts_Sets *parts_sets,Parts *parts)
{
    system("cls || clear");
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
    system("pause");
}

void Total_Stock(Parts *parts)
{
    system("cls || clear");
    Parts *aux = parts;
    int cont = 0,stock = 0;

    for ( ; aux ; aux = aux->next ) {
        stock = atoi(aux->stock);
        if(stock > 0)
        {
            cont++;
        }
        stock = 0;
    }

    printf("O total de pecas em stock e de %d\n\n",cont);
    system("pause");
}

void Total_Parts_Sets(Parts_Sets *parts_sets)
{
    system("cls || clear");
    char conjunto[100];
    Parts_Sets *aux_parts_sets = parts_sets;
    int cont=0;

    printf("Diga o Numero do conjunto ->");
    fflush(stdin);
    gets(conjunto);

    for ( ; aux_parts_sets ; aux_parts_sets = aux_parts_sets->next ) {
        if(strcmp(aux_parts_sets->set_num,conjunto) == 0){
            cont++;
        }
    }

    printf("O total de pecas neste conjunto e de %d.\n\n",cont);
    system("pause");
}

Aux_Parts* new_aux_parts(int cont,char part_num[]) {
    Aux_Parts* c = (Aux_Parts*) malloc(sizeof(Aux_Parts));
    assert(c);

    c->cont = cont;
    strcpy(c->part_num,part_num);
    c->next = NULL;
    return c;
}

List_Parts* new_list() {
    List_Parts* list = (List_Parts*) malloc(sizeof(List_Parts));
    assert(list);

    list->first = list->last = NULL;
    return list;
}

List_Parts_Sets* new_list_Parts_Sets() {
    List_Parts_Sets* list = (List_Parts_Sets*) malloc(sizeof(List_Parts_Sets));
    assert(list);

    list->first = list->last = NULL;
    return list;
}

List_Parts_Parts* new_list_Parts() {
    List_Parts_Parts* list = (List_Parts_Parts*) malloc(sizeof(List_Parts_Parts));
    assert(list);

    list->first = list->last = NULL;
    return list;
}

List_Sets* new_list_Sets() {
    List_Sets* list = (List_Sets*) malloc(sizeof(List_Sets));
    assert(list);

    list->first = list->last = NULL;
    return list;
}

void tail_insert_AUX(Aux_Parts* lst,List_Parts* list) 
{
    assert(lst);

    lst->next = list->first;
    list->first = lst;
  
    if (!list->last) {
        list->last = lst;
    }  
}

void tail_insert_Parts_Sets(Parts_Sets* lst,List_Parts_Sets* list) 
{
    assert(lst);

    lst->next = list->first;
    list->first = lst;
  
    if (!list->last) {
        list->last = lst;
    }  
}

void tail_insert_AUX_Parts(Parts* lst,List_Parts_Parts* list) 
{
    assert(lst);

    lst->next = list->first;
    list->first = lst;
  
    if (!list->last) {
        list->last = lst;
    }
}

void tail_insert_AUX_Sets(Sets* lst,List_Sets* list) 
{
    assert(lst);

    lst->next = list->first;
    list->first = lst;
  
    if (!list->last) {
        list->last = lst;
    }
}

void Part_mais_utilizada(Parts_Sets *parts_sets,Parts *parts)
{
    system("cls || clear");
    Parts_Sets *aux = parts_sets;
    Aux_Parts *AUX_parts = NULL;
    List_Parts *list = new_list();
    int cont=0,contmax = 0;
    char peca[500];
    int i=0;

    for(;aux; aux = aux->next)
    {
        i=0;
        if(AUX_parts)
        {
            for(AUX_parts = list->first;AUX_parts;AUX_parts = AUX_parts->next)
            {
                if(strcmp(aux->part_num,AUX_parts->part_num)==0)
                {
                    i = 1;
                    cont = AUX_parts->cont;
                    //printf("%s %s || %d | ",AUX_parts->part_num,aux->part_num,cont);
                    cont++;
                    AUX_parts->cont = cont;
                    //printf("%d\n",cont);
                    //system("pause");
                    break;
                }
            }
        }

        if(i == 0)
        {
            AUX_parts = new_aux_parts(1,aux->part_num); 
            tail_insert_AUX(AUX_parts,list);
        }   
    }

    for (AUX_parts = list->first; AUX_parts ; AUX_parts = AUX_parts->next) 
    {
        if(AUX_parts->cont > contmax)
        {
            strcpy(peca,AUX_parts->part_num);
            contmax = AUX_parts->cont;
        }
    }
   
    char part_num[100];
    char name[500];
    char class[500];
    char stock[300];
    Parts *auxP = NULL;
    for (auxP = parts;auxP;auxP = auxP->next) 
    {
        if(strcmp(auxP->part_num,peca)==0)
        {
            strcpy(name,auxP->name);
            strcpy(class,auxP->class);
            strcpy(stock,auxP->stock);
        }
    }
    
    printf("Num_Part -> %s \nName -> %s \nClass -> %s\nStock -> %s\nCont -> %d\n",peca,name,class,stock,contmax);
    system("pause");

}

Parts* Alterar_Stock(Parts *parts,List_Parts_Parts *list)
{
    Parts *aux = parts;
    char num_part[500];
    int stock=0,stock_ant=0;
    int cont=0;
    
    system("cls || clear");
    printf("Diga o Numero da Part -> ");
    fflush(stdin);
    gets(num_part);
    printf("Quanto stock quer adicionar-> ");
    scanf("%d",&stock);

    for(;aux;aux = aux->next)
    {
        if(strcmp(aux->part_num,num_part) == 0)
        {
            cont++;
            parts = aux;
            itoa(stock, parts->stock, 10);
        }
    }

    if(cont == 0)
    {
        printf("Nao existe essa parte\n\n");
    }
    
    parts = list->first;
    system("pause");
    return parts;

}

Parts * RemoverClass(Parts *parts,List_Parts_Parts *list)
{
    Parts * aux_next = NULL;
    Parts * aux_previous = NULL;
    char class[500];
    int cont=0;

    system("cls || clear");
    printf("Diga o nome da Class -> ");
    fflush(stdin);
    gets(class);

    for(;parts;parts = parts->next)
    {
        if(strcmp(parts->class,class)==0)
        {
            aux_next = parts->next;
            aux_previous = parts->previous;

            parts->previous->next = aux_next;
            parts->next->previous = aux_previous; 
            free(parts);
        }
    }
    parts = list->first;

    system("pause");
}

Sets * RemoverTheme(Sets *sets,List_Sets *list)
{
    Sets * aux_next = NULL;
    Sets * aux_previous = NULL;
    char theme[500];
    int cont=0;

    system("cls || clear");
    printf("Diga o nome do Theme -> ");
    fflush(stdin);
    gets(theme);

    for(;sets;sets = sets->next)
    {
        if(strcmp(sets->theme,theme)==0)
        {
            aux_next = sets->next;
            aux_previous = sets->previous;

            sets->previous->next = aux_next;
            sets->next->previous = aux_previous;
            free(sets);    
        }
    }
    sets = list->first;
    system("pause");
    return sets;
}

Parts * AdicionarStock(Parts *parts,Parts_Sets *parts_sets, List_Parts_Parts *list_parts,List_Parts_Sets *list_parts_sets)
{
    char set_num[500];
    int cont=0,quantidade=0,stock = 0;
    Aux_Parts* aux = NULL;
    List_Parts * list_aux = new_list();

    Parts * aux_parts = NULL;
    List_Parts_Parts * aux_list_parts = new_list_Parts();

    system("cls || clear");
    printf("Diga o numero do Set -> ");
    fflush(stdin);
    gets(set_num);
    printf("Diga a quantidade que quer -> ");
    scanf("%d",&quantidade);

    for(;parts_sets;parts_sets = parts_sets->next)
    {
        if(strcmp(parts_sets->set_num,set_num)==0)
        {
            cont++;
            aux = new_aux_parts(1,parts_sets->part_num);
            tail_insert_AUX(aux,list_aux);
        }
    }

    if(!(cont == 0))
    {
        parts_sets = list_parts_sets->first;

        for(;aux;aux = aux->next)
        {   
            parts = list_parts->first;
            for(;parts;parts = parts->next)
            {
                if(strcmp(parts->part_num,aux->part_num)==0)
                {
                    aux_parts = head_insert_Parts(aux_parts, parts->part_num, parts->name,parts->class,parts->stock);
                    tail_insert_AUX_Parts(aux_parts,aux_list_parts);
                    break;
                }
            }
        }

        aux = list_aux->first;
        parts = list_parts->first;

        for(;aux;aux = aux->next)
        {   
            parts = list_parts->first;
            for(;parts;parts = parts->next)
            {
                if(strcmp(parts->part_num,aux->part_num)==0)
                {
                    stock = atoi(parts->stock);
                    int quantidade_som = quantidade + stock;
                    itoa(quantidade_som, parts->stock, 10);
                    quantidade_som = 0;
                    break;
                }
            }
        }
        parts = list_parts->first;
        aux = list_aux->first;
        printf("\nStock Agora ->\n");
        for(;parts;parts = parts->next)
        {
            aux = list_aux->first;
            for(;aux;aux = aux->next)
            {
                if(strcmp(aux->part_num,parts->part_num)==0)
                {
                    printf("%s | %s\n",parts->part_num,parts->stock);
                }
            }
        }
    }
    else
    {
        printf("Esse numero de Set nao existe\n");
    }

    printf("\n");
    system("pause");
    return parts;
    
}

int main() {
    Parts_Sets *parts_sets = NULL;
    Parts *parts = NULL;
    Sets *sets = NULL;
    int op = 0,op1 = 0;
    char tema[100];
    List_Parts_Parts *list_parts = new_list_Parts();
    List_Parts_Sets *list_parts_sets = new_list_Parts_Sets();
    List_Sets *list_sets = new_list_Sets(); 

    sets = Read_Sets(sets,list_sets);
    parts_sets = Read_Parts_Sets(parts_sets,list_parts_sets);
    parts = Read_Parts(parts,list_parts);

    do
    {
        system("cls || clear");
        printf("1 - Listar");
        printf("\n2 - Conjuntos por ano");
        printf("\n3 - Pecas de um conjunto");
        printf("\n4 - Pecas Necessarias");
        printf("\n5 - Total Stock");
        printf("\n6 - Total de pecas de um conjunto");
        printf("\n7 - Peca mais utilizada");
        printf("\n----------------------");
        printf("\n8 - Alterar Stock");
        printf("\n9 - Adicionar Stock Set");
        printf("\n10 - Remover Class");
        printf("\n11 - Remover Theme");
        printf("\n0 - Sair");
        printf("\nOpcao-> ");
        scanf("%d",&op);
        switch (op)
        {
            case 1:
            do
            {
                system("cls || clear");
                printf("1 - Parts");
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
            case 7: Part_mais_utilizada(parts_sets,parts); break;
            case 8: parts = Alterar_Stock(parts,list_parts); break;
            case 9: parts = AdicionarStock(parts,parts_sets,list_parts,list_parts_sets); break;
            case 10: parts = RemoverClass(parts,list_parts); break;
            case 11: sets = RemoverTheme(sets,list_sets); break;
            case 0: printf("Ate a proxima"); break;
        }
    } while (op < 1 && op > 10 || op != 0);
    
    return 0;
}