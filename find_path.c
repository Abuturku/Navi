#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
#include <limits.h>

/* Definitionen zur Ausgabe von Umlauten */
#define AE (unsigned char)142
#define ae (unsigned char)132
#define OE (unsigned char)153
#define oe (unsigned char)148
#define UE (unsigned char)154
#define ue (unsigned char)129
#define ss (unsigned char)225

#define DISTANCE(A,B) (A>B?A-B:B-A)

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

/* ----- find_path.c ---------- */
int getkm(char name[], int nr);
int getnumber(char city[]);

struct interchange
{
    char name[50];
    int waynr1;
    int waykm1;
    int waynr2;
    int waykm2;
    bool visited;
    //char previous[50];
};

struct exit
{
    char name[50];
    int waynr;
    int waykm;
    bool visited;
    //char previous[50];
};

struct interchange getNearestInterchangeToExit(struct exit exit, struct interchange interchanges[], int interchangeCount);
struct interchange getNearestInterchangeToInterchange(struct interchange exit, struct interchange interchanges[], int interchangeCount);
void findPathByInterchange(struct exit start, struct exit destination, struct interchange interchanges[], int interchangeCount, struct exit exits[], int exitCount);

bool way_found = 0;
char global_start[255], global_dest[255], stop[255];
int strecke=0;

void find_pathx()
{
    struct interchange interchanges[200];
    struct exit exits[500];

    strecke=0;
//    int start_nr = 0;
//    int start_km = 0;
//    int dest_nr = 0;
//    int dest_km = 0;
    struct exit start;
    struct exit destination;
    int temp=0;
    int interchangeCount = 0;
    int exitCount = 0;

    char  starts[255], destinations[255], compare[255];

    bool first, start_found, dest_found ;

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
        func_cancel("cancel", NULL);
    }
    do
    {
        if (first==1)
        {
            printf("Abbruch jederzeit mit Eingabe von cancel m%cglich!\nBitte geben Sie den Namen des Startortes ein: ", oe);
        }
        else
        {
            printf("Stadt nicht gefunden. Bitte geben Sie einen anderen Namen ein: ");
        }

        first = 0;
        scanf("%s", starts);
        strcat(starts,"\n");
        printf("\n");
        func_cancel(starts, NULL);

        /* Umwandlung des Namens in einen String bestehend aus Kleinbuchstaben */
        for(int i = 0; starts[i]; i++)
        {
            starts[i] = tolower(starts[i]);
        }

        while(fgets(compare, 255, table))
        {
            /* Sollte der Stadtname nicht vorhandensein, wird nach einem neuen Namen gefragt*/
            if(strcmp(compare,starts)==0)
            {
                start_found = 1;
                strcpy(start.name, starts);
                break;
            }
        }
        rewind(table);
    } while (start_found == 0);

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
        scanf("%s", destinations);
        strcat(destinations,"\n");
        printf("\n\n\n");
        func_cancel(destinations, NULL);

        /* Umwandlung des Namens in einen String bestehend aus Kleinbuchstaben */
        for(int i = 0; destinations[i]; i++)
        {
            destinations[i] = tolower(destinations[i]);
        }

        while(fgets(compare, 255, table))
        {
            if(strcmp(compare,destinations)==0)
            {
                dest_found=1;
                strcpy(destination.name, destinations);
                break;
            }

        }
        rewind(table);
    } while (dest_found == 0);

    rewind(table);

    strcpy(global_start, starts);    //für den Start der Route später
    strcpy(global_dest, destinations);    //für den Start der Route später

    start.waynr = getnumber(starts);
    start.waykm = getkm(starts,start.waynr);

    destination.waynr = getnumber(destinations);
    destination.waykm = getkm(destinations,destination.waynr);

    if (start.waynr == destination.waynr)
    {
        way_found=1;
        printf("Der Autobahn A%d f%cr %d km folgen. \n", start.waynr, UE, DISTANCE(start.waykm, destination.waykm));
    }
    else
    {
        while(fgets(compare, 255, table))
        {
            if(strcmp(compare,"KREUZ\n")==0)
            {
                fgets(compare, 255, table);
                strcpy(interchanges[interchangeCount].name, compare);
                fgets(compare, 255, table);
                interchanges[interchangeCount].waynr1 = atoi(compare);
                fgets(compare, 255, table);
                interchanges[interchangeCount].waykm1 = atoi(compare);
                fgets(compare, 255, table);
                fgets(compare, 255, table);
                fgets(compare, 255, table);
                fgets(compare, 255, table);
                interchanges[interchangeCount].waynr2 = atoi(compare);
                fgets(compare, 255, table);
                interchanges[interchangeCount].waykm2 = atoi(compare);
                interchangeCount++;
            }
            else if(strcmp(compare,"AUSFAHRT\n")==0)
            {
                fgets(compare, 255, table);
                strcpy(exits[exitCount].name, compare);
                fgets(compare, 255, table);
                exits[exitCount].waynr = atoi(compare);
                fgets(compare, 255, table);
                exits[exitCount].waykm = atoi(compare);
                exitCount++;
            }
        }

        findPathByInterchange(start, destination, interchanges, interchangeCount, exits, exitCount);
    }


    if (way_found==0)
    {
        strtok(starts,"\n");
        starts[0]=toupper(starts[0]);
        destinations[0]=toupper(destinations[0]);
        printf("Es gibt keinen Weg von %s zu %s \n", starts, destinations);
    }

    printf("\n\nDr%ccken Sie eine beliebige Taste um fortzufahren\n",ue);
    getch();
    printf("\n");

    fclose(table);

    main(0, NULL);
}

int getkm(char name[], int nr)
{
    char compare[255];
    FILE *table;
    table = fopen("autobahn.txt", "a+");
    rewind(table);

    name[0] = tolower(name[0]);

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
    char compare[255];

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

void findPathByInterchange(struct exit start, struct exit destination, struct interchange interchanges[], int interchangeCount, struct exit exits[], int exitCount)
{
    char temp[50];
    strcpy(temp, start.name);

    //Algorithmus nach https://www.youtube.com/watch?v=S8y-Sk7u1So
    struct dijkstra
    {
        char name[50];
        int distanceToStart;
        char previous[50];
    };

    struct dijkstra dijkstraArray[interchangeCount+2];

    //Vorarbeit Dijkstra-Algorithmus: Ersten Eintrag im Array initialisieren (mit Werten aus start)
    strcpy(dijkstraArray[0].name, start.name);
    dijkstraArray[0].distanceToStart = 0;
    strcpy(dijkstraArray[0].previous, start.name);

    strcpy(dijkstraArray[interchangeCount+1].name, destination.name);
    dijkstraArray[interchangeCount+1].distanceToStart = INT_MAX;
    strcpy(dijkstraArray[interchangeCount+1].previous, destination.name);

    for (int i = 1; i < interchangeCount; i++)
    {
        strcpy(dijkstraArray[i].name, interchanges[i].name);
        dijkstraArray[i].distanceToStart = INT_MAX;
        strcpy(dijkstraArray[i].previous, interchanges[i].name);
    }

    struct interchange nearestInterchange = getNearestInterchangeToExit(start, interchanges, interchangeCount);

    for (int i = 0; i < interchangeCount; i++)
    {
        if (nearestInterchange.waynr1 == destination.waynr)
        {
            //TODO: printf("Starten Sie in %s und folgen Sie der A%d für %d km.\n", start.name, start.waynr, );
            strcpy(dijkstraArray[i+1].name, nearestInterchange.name);
            dijkstraArray[i+1].distanceToStart = DISTANCE(nearestInterchange.waykm1, dijkstraArray[i].distanceToStart);
            strcpy(dijkstraArray[i+1].previous, nearestInterchange.name);
            way_found=1;
            break;
        }
        else if (nearestInterchange.waynr2 == destination.waynr)
        {
            strcpy(dijkstraArray[i+1].name, nearestInterchange.name);
            dijkstraArray[i+1].distanceToStart = DISTANCE(nearestInterchange.waykm2, dijkstraArray[i].distanceToStart);
            strcpy(dijkstraArray[i+1].previous, nearestInterchange.name);
            way_found=1;
            break;
        }
        else
        {
            int positionInDijkstraArray;
            nearestInterchange.visited=true;

            for(int i = 0; i < interchangeCount+2; i++)
            {
                if (strcmp(dijkstraArray[i].name,nearestInterchange.name)==0) positionInDijkstraArray=i;
                if (strcmp(nearestInterchange.name, interchanges[i].name)==0) interchanges[i].visited=true;
            }

            strcpy(dijkstraArray[positionInDijkstraArray].previous, temp);
            int previousDistance = 0;

            for (int i = 0; i < interchangeCount+2; i++)
            {
                if (strcmp(dijkstraArray[i].name, dijkstraArray[positionInDijkstraArray].previous)==0) previousDistance=dijkstraArray[i].distanceToStart;
            }

            strcpy(temp, nearestInterchange.name);
            //if(nearestInterchange.waykm1==-1) dijkstraArray[positionInDijkstraArray].distanceToStart=DISTANCE(nearestInterchange.waykm2, );
            //else if (nearestInterchange.waykm1==-1) dijkstraArray[positionInDijkstraArray].distanceToStart=DISTANCE(nearestInterchange.waykm1, );
            nearestInterchange.waykm1=-1;
            nearestInterchange.waykm2=-1;
            nearestInterchange = getNearestInterchangeToInterchange(nearestInterchange, interchanges, interchangeCount);
        }

    }

}

struct interchange getNearestInterchangeToInterchange(struct interchange exit, struct interchange interchanges[], int interchangeCount)
{
    struct interchange nearestInterchange;
    int distance = INT_MAX;

    for (int i = 0; i < interchangeCount; i++)
    {
        if (interchanges[i].waynr1==exit.waynr1 && interchanges[i].visited==false)
        {
            if (DISTANCE(interchanges[i].waykm1, exit.waykm1)<distance)
            {
                distance=DISTANCE(interchanges[i].waykm1, exit.waykm1);
                nearestInterchange=interchanges[i];
            }
        }
        else if (interchanges[i].waynr2==exit.waynr2 && interchanges[i].visited==false)
        {
            if (DISTANCE(interchanges[i].waykm2, exit.waykm2)<distance)
            {
                distance=DISTANCE(interchanges[i].waykm2, exit.waykm2);
                nearestInterchange=interchanges[i];
            }
        }
    }
    return nearestInterchange;
}

struct interchange getNearestInterchangeToExit(struct exit exit, struct interchange interchanges[], int interchangeCount)
{
    struct interchange nearestInterchange;
    int distance = INT_MAX;

    for (int i = 0; i < interchangeCount; i++)
    {
        if (interchanges[i].waynr1==exit.waynr && interchanges[i].visited==false)
        {
            if (DISTANCE(interchanges[i].waykm1, exit.waykm)<distance)
            {
                distance=DISTANCE(interchanges[i].waykm1, exit.waykm);
                nearestInterchange=interchanges[i];
            }
        }
        else if (interchanges[i].waynr2==exit.waynr && interchanges[i].visited==false)
        {
            if (DISTANCE(interchanges[i].waykm2, exit.waykm)<distance)
            {
                distance=DISTANCE(interchanges[i].waykm2, exit.waykm);
                nearestInterchange=interchanges[i];
            }
        }
    }
    return nearestInterchange;
}
