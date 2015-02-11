#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>


void quicksort(char *cities[], unsigned int len, char *waynrs[], char *dists[]);
void sortWayNrs(char *waynrs[], unsigned int len);
void swap(char **arg1, char **arg2);

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
    //char temp_list[200];


    //für jedes Element dieses Arrays (char*) eine Zeichenkette allozieren.
    for (int i=0;i<500;i++)
    {
        fileInList[i] = (char*)malloc(200*sizeof(char));
        cities[i] = (char*)malloc(50*sizeof(char));
        waynrs[i] = (char*)malloc(5*sizeof(char));
        dists[i] = (char*)malloc(5*sizeof(char));
        waynrsWithoutDoubles[i] = (char*)malloc(5*sizeof(char));
    }

    //Inhalte aus autobahn.txt werden in das Array kopiert
    for(int i = 0; fgets(temp,200,table); i++)
    {
        strcpy(fileInList[i],temp);
        linecount++;
    }

    //Array waynrsWithoutDoubles mit Startwerten initialisieren
    for(int i = 0; i < 100; i++)
        itoa(15000, waynrsWithoutDoubles[i], 10);

    int skips = 0;  //Diese Variable dient lediglich dazu, nur die wirklich beschriebenen Array-Inhalte auszugeben.

    //Überträgt die Daten aus fileInList in einzelne Arrays (Stadt, Autobahnnummer und Autobahnkilometer werden in je einem Array aus Strings gespeichert)
    for (int i = 0,k = 0; i < linecount; k++)
    {
        //Wenn der Eintrag ein Kreuz ist, dann...
        if(strstr(fileInList[i], "KREUZ"))
        {
            i=i+10;             //Ein Eintrag hat 5 Zeilen, also wird i um 10 erhöht, da ein Kreuz 2 Einträge beansprucht
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

    //Inhalt von waynrs in waynrsWithoutDoubles kopieren
    memcpy(waynrsWithoutDoubles, waynrs, sizeof(waynrs));

    //Autobahnnummern nur einzeln vorkommen lassen
    for(int i = 0; i < 10; i++)
    {
        for(int j = i+1; j < 10; j++)
        {
            //Wurde eine Nummer nochmal gefunden...
            if ((strcmp(waynrsWithoutDoubles[i], waynrsWithoutDoubles[j]) == 0))
                {
                    //...wird diese Array gelöscht
                    memmove(waynrsWithoutDoubles+i, waynrsWithoutDoubles+i+1, sizeof(waynrs));
                }
        }
    }

    printf("F%cr welche Autobahn m%cchten Sie die Ausfahrten anzeigen?\n", ue, oe);

    //Autobahnnummern (ohne Duplikate) sortieren
    sortWayNrs(waynrsWithoutDoubles, sizeof(waynrsWithoutDoubles)/sizeof(*waynrsWithoutDoubles));

    printf("\n");

    //TODO:
    //Die Ausgabe will noch nicht so ganz. Im Debug-Modus läufts einwandfrei...
    for(int i = 0; i < 100; i++)
    {
        if(atoi(waynrsWithoutDoubles[i])>0 && atoi(waynrsWithoutDoubles[i])<1000)
            printf("%d\n", atoi(waynrsWithoutDoubles[i]));
    }

    printf("\n");
    scanf("%s", waynr);
    strcat(waynr, "\n");        //Ein New-Line-Zeichen anhängen, damit später richtig verglichen werden kann (Zeile 152)

    do
    {
        printf("Wonach soll sortiert werden?\n(1) Ausfahrtname\n(2) Autobahnkilometer\n");
        scanf("\n%s", sortWith);
        printf("\n");
    }while(atoi(sortWith) != 1 && atoi(sortWith) != 2);


    //Liste sortieren
    quicksort(cities, sizeof(cities)/sizeof(*cities), waynrs, dists);


    //Sortierte Liste ausgeben
    for(int i=0;i<100;i++)
    {
        if(strcmp(waynrs[i], waynr)==0)
        {
            printf("%s\t%s", strtok(cities[i], "\n"), dists[i]);    //Damit die Autobahnkilometer in der selben Zeile wie die der Stadt stehen wird hier strtok() benutzt
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

    //Einen zufälligen Wert mit dem letzten Element tauschen. % len, damit der Index nicht die Grenzen übersteigt.
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

void sortWayNrs(char *waynrs[], unsigned int len)
{
    unsigned int i, pivot=0;

    if (len <= 1)
        return;

    unsigned int rnd = (unsigned int)rand();
    swap(waynrs+(rnd % len), waynrs+len-1);


    for (i=0;i<len-1;++i)
    {
        if (strcmp(waynrs[i], waynrs[len-1]) < 0)
        {
            swap(waynrs+i, waynrs+pivot);
            pivot++;
        }
    }

    swap(waynrs+pivot, waynrs+len-1);

    sortWayNrs(waynrs, pivot++);
    sortWayNrs(waynrs+pivot, len - pivot);
}
