#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void quicksort(char *cities[], unsigned int len, char *waynrs[], char *dists[]);
void swap(char **arg1, char **arg2);

void sort_list()
{

    /*
    **************************************Variablen*****************************************
    fileInList              Darstellung der Datei in einem Array
    cities                  Darstellung der St�dtenamen aus der Datei in einem Array
    waynrs                  Darstellung der Autobahnnummern aus der Datei in einem Array
    dists                   Darstellung der Autobahnkilometer aus der Datei in einem Array
    temp                    Zwischenspeicher einer Zeile aus der Datei. Der Inhalt von temp
                            wird sp�ter in fileInList geschrieben
    waynr                   Autobahnnummer, anhand derer die Liste erstellt wird
    sortWith                Ein Zeichen, das angibt, wonach sortiert werden soll
                            (Ausfahrtnamen(1) oder Autobahnkilometer(2))
    waynrsWithoutDoubles    Zur Speicherung der Autobahnnummern, ohne Doppelungen
    ****************************************************************************************
    */

    //Arrays sind f�r 100 Eintr�ge ausgelegt (vorerst)
    char *fileInList[500];
    //char *kreuzeUAusfahrten[100];
    char *cities[100];
    char *waynrs[100];
    char *dists[100];
    char temp[100];
    char waynr[256];
    char sortWith;
    char *waynrsWithoutDoubles[100];


    //Datei �ffnen in read-write-Modus
    FILE *table;
    table = fopen("autobahn.txt", "r+");

    /* �berpr�fen ob �ffnen der Datei erfolgreich war */
    if(table == NULL)
    {
        printf("FEHLER");
    }

    //linecount = Zeilenanzahl der Datei
    int linecount=0;
    //char temp_list[200];


    //f�r jedes Element dieses Arrays (char*) eine Zeichenkette allozieren
    for (int i=0;i<500;i++)
    {
        fileInList[i] = (char*)malloc(200*sizeof(char));
        //kreuzeUAusfahrten[i] = (char*)malloc(8*sizeof(char));
        cities[i] = (char*)malloc(50*sizeof(char));
        waynrs[i] = (char*)malloc(5*sizeof(char));
        dists[i] = (char*)malloc(5*sizeof(char));
        //temp[i] = (char*)malloc(200*sizeof(char));
        waynrsWithoutDoubles[i] = (char*)malloc(5*sizeof(char));
    }

    //Inhalte aus autobahn.txt werden in das Array kopiert
    for(int i = 0; fgets(temp,200,table); i++)
    {

        //if(i%5==0) k++;
        strcpy(fileInList[i],temp);
        //printf("%s", list[i]);
        //printf("%s", fileInList[i]);
        linecount++;
    }

    int skips = 0;  //Diese Variable dient lediglich dazu, nur die wirklich beschriebenen Array-Inhalte auszugeben.

    //�bertr�gt die Daten aus fileInList in einzelne Arrays (Stadt, Autobahnnummer und Autobahnkilometer werden in je einem Array aus Strings gespeichert)
    for (int i = 0,k = 0; i < linecount; k++)
    {
        //Wenn der Eintrag ein Kreuz ist, dann...
        if(strstr(fileInList[i], "KREUZ"))
        {
            i=i+10;             //Ein Eintrag hat 5 Zeilen, also wird i um 10 erh�ht, da ein Kreuz 2 Eintr�ge beansprucht
            k--;                //k verringern, damit in den Arrays (im else-Block) alles an richtiger Stelle steht
            skips+=2;
            continue;
        }
        //sonst Inhalte in die entsprechenden Arrays kopieren
        else
        {
            strcpy(cities[k], fileInList[i+1]);
            strcpy(waynrs[k], fileInList[i+2]);
            strcpy(dists[k], fileInList[i+3]);
            i=i+5;
        }

    }

    //TODO
    //Autobahnnummern nur einzeln vorkommen lassen


    printf("Fuer welche Autobahn moechten Sie die Ausfahrten anzeigen?\n");
    scanf("%s", waynr);
    strcat(waynr, "\n");        //Ein New-Line-Zeichen anh�ngen, damit in der Funktion sort_list() richtig verglichen werden kann.

    printf("Wonach soll sortiert werden?\n(1) Ausfahrtname\(2) Autobahnkilometer");
    scanf("%c", &sortWith);

    //Ausgabe unsortierte Liste, und nur die, die an der gew�nschten Autobahn liegen (waynr)
    for(int i=0;i<linecount/5-skips;i++)
    {
        if(strcmp(waynrs[i], waynr)==0)
        {
            printf("%s", cities[i]);
        }

    }
    printf("\n");

    //Liste sortieren
    quicksort(cities, sizeof(cities)/sizeof(*cities), waynrs, dists);


    //Sortierte Liste ausgeben
    for(int i=100-skips;i<100;i++)
    {
        if(strcmp(waynrs[i], waynr)==0)
        {
            printf("%s", cities[i]);
        }

    }
    printf("\n");

}

void swap(char **arg1, char **arg2)
{
    char *tmp = *arg1;
    *arg1 = *arg2;
    *arg2 = tmp;
}

void quicksort(char *cities[], unsigned int len, char *waynrs[], char *dists[])
{
    unsigned int i, pivot=0;

    if (len <= 1)
        return;

    //Einen zuf�lligen Wert mit dem letzten Element tauschen. % len, damit der Index nicht die Grenzen �bersteigt.
    unsigned int rnd = (unsigned int)rand();
    swap(cities+(rnd % len), cities+len-1);
    swap(waynrs+(rnd % len), waynrs+len-1);
    swap(dists+(rnd % len), dists+len-1);

    // den Pivot-Index auf 0 setzen und die Liste durchlaufen
    for (i=0;i<len-1;++i)
    {
        if (strcmp(cities[i], cities[len-1]) < 0)
        {
            swap(cities+i, cities+pivot);
            swap(waynrs+i, waynrs+pivot);
            swap(dists+i, dists+pivot);
            pivot++;
        }
    }

    // den Pivot-Wert auf seinen Platz tauschen
    swap(cities+pivot, cities+len-1);
    swap(waynrs+pivot, waynrs+len-1);
    swap(dists+pivot, dists+len-1);

    // und so auf den Teillisten weiter verfahren. (Ohne Pivot-Slot)
    quicksort(cities, pivot++, waynrs, dists);
    quicksort(cities+pivot, len - pivot, waynrs+pivot, dists+pivot);
}
