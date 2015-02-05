#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** fileInList;
char** kreuzeUAusfahrten;
char** cities;
char** waynrs;
char** dists;
char** temp;

void quicksort(int first,int last);

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
    temp = (char**)malloc(200*sizeof(char*));


    //für jedes Element dieses Arrays (char*) eine Zeichenkette allozieren
    for (int i=0;i<500;i++)
    {
        fileInList[i] = (char*)malloc(200*sizeof(char));
        kreuzeUAusfahrten[i] = (char*)malloc(8*sizeof(char));
        cities[i] = (char*)malloc(50*sizeof(char));
        waynrs[i] = (char*)malloc(5*sizeof(char));
        dists[i] = (char*)malloc(5*sizeof(char));
        temp[i] = (char*)malloc(200*sizeof(char));
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


    //Überträgt die Daten aus fileInList in einzelne Arrays (Stadt, Autobahnnummer und Autobahnkilometer werden in je einem Array aus Strings gespeichert)
    for (int i = 0,k = 0; k < linecount/5; k++)
    {
        strcpy(kreuzeUAusfahrten[k], fileInList[i]);
        strcpy(cities[k], fileInList[i+1]);
        strcpy(waynrs[k], fileInList[i+2]);
        strcpy(dists[k], fileInList[i+3]);
        i=i+5;
    }
    //Ausgabe unsortierte Liste
    for(int i=0;i<linecount/5;i++)
    {
        printf("%s", cities[i]);
    }
    printf("\n");

    //Liste sortieren
    quicksort(0, linecount/5-1);


    FILE *sorted_list;
    sorted_list = fopen("sorted_list.txt", "w+");

    //Ausgabe sortierte Liste

    for(int i=0;i<linecount/5;i++)
    {
        printf("%s", cities[i]);
        fprintf(sorted_list, "%s\n", cities[i]);
    }
    fclose(sorted_list);
}

void quicksort(int first,int last){
    int pivot,j,i = 0;

    if(first<last){
        pivot=first;
        i=first;
        j=last;

        while(i<j){
            while(strcmp(cities[i],cities[pivot])<=0&&i<last)
                i++;
            while(strcmp(cities[j],cities[pivot])>0)
                j--;
            if(i<j){
                //Städte tauschen
                strcpy(temp[i],cities[i]);
                strcpy(cities[i],cities[j]);
                strcpy(cities[j],temp[i]);

                //Kreuze/Ausfahrten tauschen
                strcpy(temp[i],kreuzeUAusfahrten[i]);
                strcpy(kreuzeUAusfahrten[i],kreuzeUAusfahrten[j]);
                strcpy(kreuzeUAusfahrten[j],temp[i]);

                //Autobahnnummern tauschen
                strcpy(temp[i],waynrs[i]);
                strcpy(waynrs[i],waynrs[j]);
                strcpy(waynrs[j],temp[i]);

                //Autobahnkilometer tauschen
                strcpy(temp[i],dists[i]);
                strcpy(dists[i],dists[j]);
                strcpy(dists[j],temp[i]);
            }
        }

        //Städte tauschen
        strcpy(temp[i],cities[pivot]);
        strcpy(cities[pivot],cities[j]);
        strcpy(cities[j],temp[i]);

        //Kreuz/Ausfahrt tauschen
        strcpy(temp[i],kreuzeUAusfahrten[pivot]);
        strcpy(kreuzeUAusfahrten[pivot],kreuzeUAusfahrten[j]);
        strcpy(kreuzeUAusfahrten[j],temp[i]);

        //Autobahnnummern tauschen
        strcpy(temp[i],waynrs[pivot]);
        strcpy(waynrs[pivot],waynrs[j]);
        strcpy(waynrs[j],temp[i]);


        //Autobahnkilometer tauschen
        strcpy(temp[i],dists[pivot]);
        strcpy(dists[pivot],dists[j]);
        strcpy(dists[j],temp[i]);


        quicksort(first,j-1);
        quicksort(j+1,last);
    }
}
