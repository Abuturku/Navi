#include <stdio.h>
#include <stdlib.h>



char** fileInList;
char** kreuzeUAusfahrten;
char** cities;
char** waynrs;
char** dists;

void quicksort(char** list,int first,int last);

void sort_list()
{
    //Datei öffnen in read-write-Modus
    FILE *table;
    table = fopen("autobahn.txt", "r+");

    /* Überprüfen ob Öffnen der Datei erfolgreich war */
    if(table == NULL)
    {
        printf("FEHLER");
    }

    //linecount = Zeilenanzahl der Datei
    int linecount=0;
    char temp_list[200];

    //Array aus Zeigern auf Arrays aus Zeichen (char**) allozieren
    fileInList = (char**)malloc(500*sizeof(char*));
    kreuzeUAusfahrten = (char**)malloc(200*sizeof(char*));
    cities = (char**)malloc(200*sizeof(char*));
    waynrs = (char**)malloc(200*sizeof(char*));
    dists = (char**)malloc(200*sizeof(char*));


    //für jedes Element dieses Arrays (char*) eine Zeichenkette allozieren
    for (int i=0;i<500;i++)
    {
        fileInList[i] = (char*)malloc(200*sizeof(char));
        kreuzeUAusfahrten[i] = (char*)malloc(8*sizeof(char));
        cities[i] = (char*)malloc(50*sizeof(char));
        waynrs[i] = (char*)malloc(5*sizeof(char));
        dists[i] = (char*)malloc(5*sizeof(char));
    }

    //Inhalte aus autobahn.txt werden in das Array kopiert
    for(int i = 0; fgets(temp_list,200,table); i++)
    {

        //if(i%5==0) k++;
        strcpy(fileInList[i],temp_list);
        //printf("%s", list[i]);
        printf("%s", fileInList[i]);
        linecount++;
    }


    //Überträgt die Daten aus fileInList in einzelne Arrays
    for (int i = 0,k = 0; k < linecount/5; k++)
    {
        strcpy(kreuzeUAusfahrten[k], fileInList[i]);
        strcpy(cities[k], fileInList[i+1]);
        strcpy(waynrs[k], fileInList[i+2]);
        strcpy(dists[k], fileInList[i+3]);
        i=i+5;
    }

    for(int i=0;i<linecount/5;i++)
    {
        printf("%s", cities[i]);
    }

    quicksort(cities, 0, linecount/5);

    for(int i=0;i<linecount/5;i++)
    {
        printf("%s", cities[i]);
    }

}

void quicksort(char** list,int first,int last){
    int pivot,j,i = 0;
    char** temp = (char**)malloc(200*sizeof(char*));


    if(first<last){
        pivot=first;
        i=first;
        j=last;

        while(i<j){
            while(strcmp(list[i],list[pivot])<=0&&i<last)
                i++;
            while(strcmp(list[j],list[pivot])>0)
                j--;
            temp[i]=(char*)malloc(50*sizeof(char));
            if(i<j){
                strcpy(temp[i],list[i]);
                strcpy(list[i],list[j]);
                strcpy(list[j],temp[i]);
            }
        }
        temp[i]=(char*)malloc(50*sizeof(char));
        strcpy(temp[i],list[pivot]);
        strcpy(list[pivot],list[j]);
        strcpy(list[j],temp[i]);
        quicksort(list,first,j-1);
        quicksort(list,j+1,last);
    }
}
