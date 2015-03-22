#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <ctype.h>

/* Definitionen zur Ausgabe von Umlauten */
#define AE (unsigned char)142
#define ae (unsigned char)132
#define OE (unsigned char)153
#define oe (unsigned char)148
#define UE (unsigned char)154
#define ue (unsigned char)129
#define ss (unsigned char)225

bool way_found = 0;
char global_start[255],
     global_dest[255],
     stop[255];
int strecke=0;


void find_path()
{

    int start_nr = 0;
    int start_km = 0;
    int dest_nr = 0;
    int dest_km = 0;
    int temp=0;

    char  start[255],
          destination[255],
          compare[255];


    bool first,
         start_found,
         dest_found ;

    first=1;
    start_found=0;
    dest_found=0;

    printf("\n\n");

    /* Öffnen der Datei mit Modus "a+" (APPEND+READ) = Neue Einträge werden an der Dateiende angehängt */
    FILE *table;
    table = fopen("autobahn.txt", "a+");

    /* Überprüfen ob Öffnen der Datei erfolgreich war */
    if(table == NULL)
    {
        printf("Fehler beim %cffnen der Datei!", oe);
        func_cancel("cancel");
    }
    do
    {
        if (first==1)
        {
            printf("Bitte geben Sie den Namen des Startortes ein: ");
        }
        else
        {
            printf("Stadt nicht gefunden. Bitte geben Sie einen anderen Namen ein: ");

        }
        first = 0;
        scanf("%s", start);
        strcat(start,"\n");
        printf("\n");
        func_cancel(start);
        /* Umwandlung des Namens in einen String bestehend aus Kleinbuchstaben */
        for(int i = 0; start[i]; i++)
        {
            start[i] = tolower(start[i]);
        }

        while(fgets(compare, 255, table))
        {

            /* Sollte der Stadtname nicht vorhandensein, wird nach einem neuen Namen gefragt*/
            if(strcmp(compare,start)==0)
            {
                start_found = 1;
            }




        }
        rewind(table);
    }
    while (start_found == 0);

    rewind(table);
    first = 1;

    do
    {
        if (first==1)
        {
            printf("Bitte geben Sie den Namen des Zielortes ein: ");
        }
        else
        {
            printf("Stadt nicht gefunden. Bitte geben Sie eine andere Stadt ein: ");
        }
        first = 0;
        scanf("%s", destination);
        strcat(destination,"\n");
        printf("\n");
        func_cancel(destination);

        /* Umwandlung des Namens in einen String bestehend aus Kleinbuchstaben */
        for(int i = 0; destination[i]; i++)
        {
            destination[i] = tolower(destination[i]);
        }

        while(fgets(compare, 255, table))
        {
            if(strcmp(compare,destination)==0)
            {
                dest_found=1;
            }




        }
        rewind(table);
    }
    while (dest_found == 0);
    rewind(table);

    strcpy(global_start, start);    //für den Start der Route später
    strcpy(global_dest, destination);    //für den Start der Route später



    start_nr = getnumber(start);

    start_km = getkm(start,start_nr);
    dest_nr = getnumber(destination);
    dest_km = getkm(destination,dest_nr);

    if (start_nr == dest_nr)
    {
        way_found=1;
        printf("einfach die Autobahn fuer %d km langfahren. \n", getDistanz(start_km,dest_km));
    }
    else
    {
        find_cross_by_nr(dest_nr,start_nr,start); //Start und Ziel vertauscht, da durch die Rekursion der Weg rückwärts ausgegeben wird

        if (way_found==1)
        {
            temp = (getDistanz(dest_km,(getkm(stop, dest_nr))));
            strecke=strecke+temp;
            printf("Zum Schluss fahren Sie noch %dkm auf der A%d zum Ziel %s \n Die Gesamtstrecke betraegt %dkm. \n\n", temp, dest_nr,destination, strecke);
        }

        if (way_found==0){
            strtok(start,"\n");
         printf("es gibt keinen Weg von %s zu %s \n", start, destination);
        }
    }
     
     main();
}


    void find_cross_by_nr(int start_nr, int dest_nr, char start[255])
    {

        char 	compare[255]= {},
                              name[255]= {};
        int 	cross_nr1=0,
                cross_nr2=0,
                distanz=0;

        FILE *table;
        table = fopen("autobahn.txt", "a+");
        rewind(table);


        while (fgets(compare, 255, table))
        {

            for(int i=0; i<sizeof(name); i++)       //leeren des Namens String
            {
                name[i] = '\0';
            }
            if(strcmp(compare,"KREUZ\n")==0)
            {
                fgets(compare, 255, table);     //Name des Kreuzes
                strcat(name,compare);
                fgets(compare, 255, table);     //Nummer des Kreuzes
                cross_nr1 = atoi(compare);




                if ((cross_nr1== start_nr)&& (strcmp(name,start)!=0))
                {
                    fgets(compare, 255, table);    //KM
                    fgets(compare, 255, table);    //leer
                    fgets(compare, 255, table);   //KREUZ
                    fgets(compare, 255, table);   //Name
                    if(strcmp(compare,name)==0)   	// wenn es nicht den gleichen Namen hat, rufe stattdessen getnumber mit dem namen des Kreuzes auf, so wird die 2te AUtobahnNr bestimmt
                    {
                        fgets(compare, 255, table); //NR
                        cross_nr2 = atoi(compare);
                    }
                    else
                    {
                        cross_nr2=getnumber(name);
                    }

                    if (cross_nr2==dest_nr)
                    {

                        way_found = 1;
                        distanz = getDistanz(getkm(global_start, cross_nr2),getkm(name, cross_nr2));
                        strcpy(stop,name);
                        strtok(name, "\n");

                        strtok(global_start,"\n");
                        strecke = strecke+distanz;
                        printf("Starten Sie bei %s und fahren sie die A%d fuer %d km bis zum Kreuz %s. \n\n",global_start,cross_nr2, distanz, name);

                        return;
                    }
                    else
                    {

                        find_cross_by_nr(cross_nr2,dest_nr,name);
                    }
                    if (way_found==1)
                    {

                        distanz = getDistanz(getkm(stop, cross_nr2),getkm(name, cross_nr2));
                        strecke = strecke + distanz;
                        strcpy(stop,name);
                        strtok(name,"\n");
                        printf("Danach fahren Sie die A%d fuer %dkm zum Kreuz %s. \n\n",cross_nr2, distanz, name);
                        return;



                    }



                }


            }

        }

        return  ;
    }

    int getDistanz(int a, int b)
    {
        int start=0,
            ziel = 0;
        if (a>b)
        {
            start = a;
            ziel = b;
        }
        else
        {
            start = b;
            ziel = a;
        }
        return (start-ziel);
    }

    int getkm(char name[], int nr)
    {
        char compare[255]= {};

        FILE *table;
        table = fopen("autobahn.txt", "a+");
        rewind(table);

        while (fgets(compare, 255, table))
        {

            if(strcmp(compare,name)==0)
            {
                fgets(compare, 255, table);
                if(nr == atoi(compare))
                {
                    fgets(compare, 255, table);
                    return atoi(compare);
                }
            }
        }
        rewind(table);
        return 0;

    }



    int getnumber(char city[])      //die Autobahn NR zu einem Namen werden ausgelesen
    {

        char compare[255]= {};

        FILE *table;
        table = fopen("autobahn.txt", "a+");
        rewind(table);

        while (fgets(compare, 255, table))
        {

            if(strcmp(compare,city)==0)
            {
                fgets(compare, 255, table);
                return atoi(compare);
            }
        }
        rewind(table);
        return 0;
    }

