/* -------------------------------------------------------------------------------------------------
Elsemann, Andreas       and.elsemann.14@dhbw-mosbach.de         Kurs INF14B Wintersemester 2014/2015
Latreider, Linda        lin.latreider.14@dhbw-mosbach.de        Kurs INF14B Wintersemester 2014/2015
Schick, Andreas         and.schick.14@dhbw-mosbach.de           Kurs INF14B Wintersemester 2014/2015
Scholz, Oliver          oli.scholz.14@dhbw-mosbach.de           Kurs INF14B Wintersemester 2014/2015

DHBW Mosbach
Lohrtalweg 10
74821 Mosbach
www.dhbw-mosbach.de
------------------------------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------------------------------
v0_3_2
func_change()           Überprüfung auf vorhandenen Eintrag verbessert
func_add_interchange()  Überprüfung auf vorhandenen Eintrag verbessert
func_add_exit()         Überprüfung auf vorhandenen Eintrag verbessert
------------------------------------------------------------------------------------------------- */


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
#include <memory.h>
#include <conio.h>


#define AE (unsigned char)142
#define ae (unsigned char)132
#define OE (unsigned char)153
#define oe (unsigned char)148
#define UE (unsigned char)154
#define ue (unsigned char)129
#define ss (unsigned char)225


/* Funktionsdeklarationen */

/* ----- main.c --------------- */
int main(int firstCall, char *argv[]);

/* ----- list_functions.c ----- */
void func_add_interchange();
void func_add_exit();
void func_add(int backup_empty);
void func_cancel(char cancel_string[256], FILE* tempdat);
void func_delete();
void func_change();
int func_list(FILE *table);
int func_number(char verify[256]);

/* ----- list_sort.c ---------- */
void quicksort(char *cities[], int left, int right, char *waynrs[], char *dists[], int sortWith);
void sort_list();
void sortWayNrs(char *waynrs[], int left, int right);
void swap(char **arg1, char **arg2);


/* ---------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------- */


//Gibt das Menü zum Auswählen der Autobahn und des Sortier-Kriteriums aus und gibt eine sortierte Liste aus
void sort_list()
{

    /*
    **************************************Variablen*****************************************
    fileInList              Darstellung der Datei in einem Array
    cities                  Darstellung der Städtenamen aus der Datei in einem Array
    waynrs                  Darstellung der Autobahnnummern aus der Datei in einem Array
    dists                   Darstellung der Autobahnkilometer aus der Datei in einem Array
    temp                    Zwischenspeicher einer Zeile aus der Datei. Der Inhalt von temp
                            wird später in fileInList geschrieben
    waynr                   Autobahnnummer, anhand derer die Liste erstellt wird
    sortWith                Ein Zeichen, das angibt, wonach sortiert werden soll
                            (Ausfahrtnamen(1) oder Autobahnkilometer(2))
    waynrsWithoutDoubles    Zur Speicherung der Autobahnnummern, ohne Doppelungen
    ****************************************************************************************
    */

    //Arrays sind für 100 Einträge ausgelegt (vorerst)
    char *fileInList[500];
    //char *kreuzeUAusfahrten[100];
    char *cities[100];
    char *waynrs[100];
    char *dists[100];
    char temp[100];
    char waynr[256];
    char sortWith[256];
    char *waynrsWithoutDoubles[100];


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

    //für jedes Element dieses Arrays (char*) eine Zeichenkette allokieren.
    for (int i=0;i<500;i++)
    {
        fileInList[i] = (char*)malloc(200*sizeof(char));
        cities[i] = (char*)malloc(50*sizeof(char));
        waynrs[i] = (char*)malloc(5*sizeof(char));
        dists[i] = (char*)malloc(5*sizeof(char));
        waynrsWithoutDoubles[i] = (char*)malloc(5*sizeof(char));
    }

    //Inhalte aus autobahn.txt werden in das Array fileInList kopiert
    for(int i = 0; fgets(temp,200,table); i++)
    {
        strcpy(fileInList[i],temp);
        linecount++;
    }

    int entriesCount = 0, skips = 0;  //Diese Variablen dienen lediglich dazu, nur die wirklich beschriebenen Array-Inhalte auszugeben.

    //Überträgt die Daten aus fileInList in einzelne Arrays (Stadt, Autobahnnummer und Autobahnkilometer werden in je einem Array aus Strings gespeichert)
    for (int i = 0,k = 0; i < linecount; k++)
    {
        //Wenn der Eintrag ein Kreuz ist, dann...
        if(strstr(fileInList[i], "KREUZ"))
        {
            i=i+10;             //Ein Eintrag hat 5 Zeilen, also wird i um 10 erhöht, da ein Kreuz 2 Einträge beansprucht
            k--;                //k verringern, damit in den Arrays (im else-Block) alles an richtiger Stelle steht
            continue;
        }
        //sonst Inhalte in die entsprechenden Arrays kopieren
        else
        {
            strcpy(cities[k], fileInList[i+1]);
            strcpy(waynrs[k], fileInList[i+2]);
            strcpy(dists[k], fileInList[i+3]);
            i=i+5;
            entriesCount++;
        }
    }

    //Inhalt von waynrs in waynrsWithoutDoubles kopieren
    for(int i = 0; i < entriesCount; i++)
        strcpy(waynrsWithoutDoubles[i], waynrs[i]);


    entriesCount--;
    //Autobahnnummern nur einzeln vorkommen lassen
    for(int i = 0; i < entriesCount+1; i++)
    {
        for(int j = i+1; j < entriesCount+1;)
        {
            //Wurde eine Nummer nochmal gefunden...
            if ((strcmp(waynrsWithoutDoubles[i], waynrsWithoutDoubles[j]) == 0))
                {
                    //...wird diese aus dem Array gelöscht
                    for(int k = j; k < entriesCount+1; k++)
                    {
                        strcpy(waynrsWithoutDoubles[k], waynrsWithoutDoubles[k+1]);
                    }
                    //memmove(waynrsWithoutDoubles+j, waynrsWithoutDoubles+j+1, sizeof(waynrsWithoutDoubles));
                    skips++;
                    entriesCount--;
                }
            else j++;
        }
    }
    printf("R%cckehr zum Hauptmen%c jederzeit mit der Eingabe von 'cancel' m%cglich!\n\n", ue, ue, oe);
    printf("F%cr welche Autobahn m%cchten Sie die Ausfahrten anzeigen?\nGeben Sie 0 ein, um alle Autobahnen auszuw%chlen\n\n", ue, oe, ae);

    //Autobahnnummern (ohne Duplikate) sortieren
    sortWayNrs(waynrsWithoutDoubles, 0, entriesCount);

    //TODO:
    //Die Ausgabe will noch nicht so ganz. Im Debug-Modus läufts einwandfrei...
    for(int i = 0; i <= entriesCount; i++)
    {
            printf("%s", waynrsWithoutDoubles[i]);
    }

    printf("\n");
    int isWaynrValid = 0;
    do
    {
        do
        {
            scanf("%s", waynr);
            printf("\n");
            func_cancel(waynr, NULL);
        }while(func_number(waynr)==1);

        for(int i = 0; i <= entriesCount; i++)
        {
            if(atoi(waynr)==atoi(waynrsWithoutDoubles[i]) || atoi(waynr)==0) isWaynrValid=1;
        }

        if(isWaynrValid==0) printf("Bitte geben Sie eine g%cltige Autobahnnummer ein\n", ue);

        //if(func_number(waynr) == 1) isWaynrValid=0;

    }while(isWaynrValid==0);

    printf("\n");
    strcat(waynr, "\n");        //Ein New-Line-Zeichen anhängen, damit später richtig verglichen werden kann

    do
    {
        if(atoi(waynr)==0)
        {
            printf("Wonach soll sortiert werden?\n(1) Ausfahrtname\n(2) Autobahnnummer\n\n");
            scanf("%s", sortWith);
            func_cancel(sortWith, NULL);
            if(atoi(sortWith)==2)
            {
                itoa(3, sortWith, 10);
            }
        }
        else
        {
            printf("Wonach soll sortiert werden?\n(1) Ausfahrtname\n(2) Autobahnkilometer\n\n");
            scanf("%s", sortWith);
            func_cancel(sortWith, NULL);
        }
        printf("\n");
    }while(atoi(sortWith) != 1 && atoi(sortWith) != 2 && !(atoi(waynr)==0 && atoi(sortWith)==3));

    //Liste sortieren
    quicksort(cities, 0, entriesCount+skips, waynrs, dists, atoi(sortWith));

    //Sortierte Liste ausgeben
    for(int i=0;i<entriesCount+skips+1;i++)
    {
        if(atoi(waynr)==0)
        {
            cities[i][0]=toupper(cities[i][0]);         //Den ersten Buchstaben der Stadt zu einem Großbuchstaben machen
            printf("%s", strtok(cities[i], "\n"));      //Damit die Autobahnkilometer in der selben Zeile wie die der Stadt stehen wird hier strtok() benutzt
            if(strlen(cities[i]) >= 16) printf("\t");
            else if(strlen(cities[i])>=8) printf("\t\t");
            else printf("\t\t\t");
            printf("A%s", strtok(waynrs[i],"\n"));
            printf("\t%s", dists[i]);
        }
        else if(strcmp(waynrs[i], waynr)==0)
        {
            cities[i][0]=toupper(cities[i][0]);
            printf("%s", strtok(cities[i], "\n"));
            if(strlen(cities[i]) >= 16) printf("\t");
            else if(strlen(cities[i])>=8) printf("\t\t");
            else printf("\t\t\t");
            printf("%s", dists[i]);
        }
    }
    printf("\n\nDr%ccken Sie eine beliebige Taste um fortzufahren\n",ue);


    getch();
    printf("\n");

    main(0, NULL);
}

//Tauscht zwei Strings
void swap(char **arg1, char **arg2)
{
    char *tmp = *arg1;
    *arg1 = *arg2;
    *arg2 = tmp;
}

//Sortiert (je nach Wert der Variablen sortWith) die Ausfahrtnamen/Autobahnnummern/Autobahnkilometer und analog dazu
//auch die anderen Arrays (um die Einträge nicht zu vermischen), die übergeben werden, mithilfe des Quicksort-Algorithmus
void quicksort(char *cities[], int left, int right, char *waynrs[], char *dists[], int sortWith)
{
    int i=left, j = right, pivot=right;


    //Sortieren nach Ausfahrtnahmen
    if (sortWith == 1)
    {
        do
        {
            while(strcmp(cities[i], cities[pivot])<0) i++;
            while(strcmp(cities[j], cities[pivot])>0) j--;
            if(i<=j)
            {
                swap(cities+i, cities+j);
                swap(waynrs+i, waynrs+j);
                swap(dists+i, dists+j);
                i++;
                j--;
            }
        }while (i<=j);

        if(left<j) quicksort(cities, left, j, waynrs, dists, sortWith);
        if(i<right) quicksort(cities, i, right, waynrs, dists, sortWith);
    }
    //Sortieren nach Autobahnkilometern
    else if (sortWith == 2)
    {
        do
        {
            while(atoi(dists[i])<atoi(dists[pivot])) i++;
            while(atoi(dists[j])>atoi(dists[pivot])) j--;
            if(i<=j)
            {
                swap(cities+i, cities+j);
                swap(waynrs+i, waynrs+j);
                swap(dists+i, dists+j);
                i++;
                j--;
            }
        }while (i<=j);

        if(left<j) quicksort(cities, left, j, waynrs, dists, sortWith);
        if(i<right) quicksort(cities, i, right, waynrs, dists, sortWith);
    }
    //Sortieren nach Autobahnnummern
    else if (sortWith == 3)
    {
        do
        {
            while(atoi(waynrs[i])<atoi(waynrs[pivot])) i++;
            while(atoi(waynrs[j])>atoi(waynrs[pivot])) j--;
            if(i<=j)
            {
                swap(cities+i, cities+j);
                swap(waynrs+i, waynrs+j);
                swap(dists+i, dists+j);
                i++;
                j--;
            }
        }while (i<=j);

        if(left<j) quicksort(cities, left, j, waynrs, dists, sortWith);
        if(i<right) quicksort(cities, i, right, waynrs, dists, sortWith);
    }
}

//Sortiert NUR die Autobahnnnummern
void sortWayNrs(char *waynrs[], int left, int right)
{
    int i=left, j = right, pivot=(left+right)/2;
    do
    {
        while(atoi(waynrs[i])<atoi(waynrs[pivot])) i++;
        while(atoi(waynrs[j])>atoi(waynrs[pivot])) j--;
        if(i<=j)
        {
            swap(waynrs+i, waynrs+j);
            i++;
            j--;
        }
    }while (i<=j);

    if(left<j) sortWayNrs(waynrs, left, j);
    if(i<right) sortWayNrs(waynrs, i, right);
}
