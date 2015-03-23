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

struct dijkstra
{
    char name[50];
    int distanceToStart;
    int previousWaynr;
    char previous[50];
};

struct interchange getNearestInterchangeToExit(struct exit exit, struct interchange interchanges[], int interchangeCount);
struct interchange getNearestInterchangeToInterchange(struct interchange exit, struct interchange interchanges[], int interchangeCount);
void findPathByInterchange(struct exit start, struct exit destination, struct interchange interchanges[], int interchangeCount, struct exit exits[], int exitCount);
void printpath (struct dijkstra array[], int length);

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
    int previousWaynr = start.waynr;

    //Algorithmus nach https://www.youtube.com/watch?v=S8y-Sk7u1So

    struct dijkstra dijkstraArray[interchangeCount+2];

    //Vorarbeit Dijkstra-Algorithmus: Ersten Eintrag im Array initialisieren (mit Werten aus start)
    strcpy(dijkstraArray[0].name, start.name);
    dijkstraArray[0].distanceToStart = 0;
    dijkstraArray[0].previousWaynr=previousWaynr;
    strcpy(dijkstraArray[0].previous, start.name);

    strcpy(dijkstraArray[interchangeCount+1].name, destination.name);
    dijkstraArray[interchangeCount+1].distanceToStart = INT_MAX;
    strcpy(dijkstraArray[interchangeCount+1].previous, destination.name);

    for (int i = 1; i <= interchangeCount; i++)
    {
        strcpy(dijkstraArray[i].name, interchanges[i].name);
        dijkstraArray[i].distanceToStart = INT_MAX;
        strcpy(dijkstraArray[i].previous, interchanges[i].name);
    }
    struct interchange nearestInterchange = getNearestInterchangeToExit(start, interchanges, interchangeCount);

    for (int i = 0; i <= interchangeCount; i++)
    {
        if (nearestInterchange.waynr1 == destination.waynr && way_found==false)
        {
            //strcpy(dijkstraArray[interchangeCount+1].name, nearestInterchange.name);
            strcpy(dijkstraArray[interchangeCount+1].previous, nearestInterchange.name);

            int previousDistance = 0;

            for (int j = 0; j < interchangeCount+2; j++)
            {
                if (strcmp(dijkstraArray[j].name, dijkstraArray[interchangeCount+1].previous)==0)
                {
                    previousDistance=dijkstraArray[j].distanceToStart;
                    previousWaynr = dijkstraArray[j].previousWaynr;
                    dijkstraArray[interchangeCount+1].previousWaynr = previousWaynr;
                }
            }

            dijkstraArray[interchangeCount+1].distanceToStart = previousDistance + DISTANCE(nearestInterchange.waykm1, getkm(dijkstraArray[interchangeCount+1].previous, dijkstraArray[interchangeCount+1].previousWaynr));
            way_found=true;
        }
        else if (nearestInterchange.waynr2 == destination.waynr && way_found == false)
        {

            //strcpy(dijkstraArray[interchangeCount+1].name, nearestInterchange.name);
            strcpy(dijkstraArray[interchangeCount+1].previous, nearestInterchange.name);

            int previousDistance = 0;

            for (int j = 0; j < interchangeCount+2; j++)
            {
                if (strcmp(dijkstraArray[j].name, dijkstraArray[interchangeCount+1].previous)==0)
                {
                    previousDistance=dijkstraArray[j].distanceToStart;
                    previousWaynr = dijkstraArray[j].previousWaynr;
                    dijkstraArray[interchangeCount+1].previousWaynr = previousWaynr;
                }
            }

            dijkstraArray[interchangeCount+1].distanceToStart = previousDistance + DISTANCE(nearestInterchange.waykm2, getkm(dijkstraArray[interchangeCount+1].previous, dijkstraArray[interchangeCount+1].previousWaynr));
            way_found=true;
        }
        else
        {
            int positionInDijkstraArray;
            nearestInterchange.visited=true;

            for(int j = 1; j <= interchangeCount+2; j++)
            {
                if (strcmp(dijkstraArray[j].name,nearestInterchange.name)==0)
                {
                    positionInDijkstraArray=j;
                }
                if (strcmp(nearestInterchange.name, interchanges[j-1].name)==0)
                {
                    interchanges[j-1].visited=true;
                }
            }

            strcpy(dijkstraArray[positionInDijkstraArray].previous, temp);
            int previousDistance = 0;

            for (int j = 0; j < interchangeCount+2; j++)
            {
                if (strcmp(dijkstraArray[j].name, dijkstraArray[positionInDijkstraArray].previous)==0)
                {
                    previousDistance=dijkstraArray[j].distanceToStart;
                    previousWaynr = dijkstraArray[j].previousWaynr;
                    dijkstraArray[positionInDijkstraArray].previousWaynr = previousWaynr;
                }
            }


            if (previousDistance + DISTANCE(nearestInterchange.waykm1, previousDistance)-start.waykm < dijkstraArray[positionInDijkstraArray].distanceToStart)
            {
                if(nearestInterchange.waynr1==previousWaynr)
                {
                    dijkstraArray[positionInDijkstraArray].distanceToStart=previousDistance + DISTANCE(nearestInterchange.waykm1, getkm(dijkstraArray[positionInDijkstraArray].previous, dijkstraArray[positionInDijkstraArray].previousWaynr));
                }
                else if (nearestInterchange.waynr2==previousWaynr)
                {
                    dijkstraArray[positionInDijkstraArray].distanceToStart=previousDistance + DISTANCE(nearestInterchange.waykm2, getkm(dijkstraArray[positionInDijkstraArray].previous, dijkstraArray[positionInDijkstraArray].previousWaynr));
                }
                else
                {
                    for (int k = 0; k < interchangeCount; k++)
                    {
                        if (strcmp(interchanges[k].name, dijkstraArray[positionInDijkstraArray].previous)==0)
                        {
                            if (nearestInterchange.waynr1==interchanges[k].waynr1)
                            {
                                dijkstraArray[positionInDijkstraArray].distanceToStart=previousDistance + DISTANCE(nearestInterchange.waynr1, getkm(interchanges[k].name, interchanges[k].waynr1));
                            }
                            else if (nearestInterchange.waynr2==interchanges[k].waynr2)
                            {
                                dijkstraArray[positionInDijkstraArray].distanceToStart=previousDistance + DISTANCE(nearestInterchange.waynr2, getkm(interchanges[k].name, interchanges[k].waynr2));
                            }
                            else if (nearestInterchange.waynr2==interchanges[k].waynr1)
                            {
                                dijkstraArray[positionInDijkstraArray].distanceToStart=previousDistance + DISTANCE(nearestInterchange.waynr2, getkm(interchanges[k].name, interchanges[k].waynr1));
                            }
                            else if (nearestInterchange.waynr1==interchanges[k].waynr2)
                            {
                                dijkstraArray[positionInDijkstraArray].distanceToStart=previousDistance + DISTANCE(nearestInterchange.waynr1, getkm(interchanges[k].name, interchanges[k].waynr2));
                            }
                        }
                    }
                }
                strcpy(dijkstraArray[positionInDijkstraArray].previous, temp);
            }
            strcpy(temp, nearestInterchange.name);
            nearestInterchange = getNearestInterchangeToInterchange(nearestInterchange, interchanges, interchangeCount);
        }

    }

    for (int i = 0; i < interchangeCount; i++)
    {
        if (strcmp(dijkstraArray[interchangeCount+1].previous, dijkstraArray[i].name)==0)
        {
            int destDistance = getkm(dijkstraArray[interchangeCount+1].name, getnumber(dijkstraArray[interchangeCount+1].name));
            dijkstraArray[interchangeCount+1].distanceToStart = destDistance+dijkstraArray[i].distanceToStart-getkm(dijkstraArray[interchangeCount+1].previous, getnumber(dijkstraArray[interchangeCount+1].previous));
        }
    }
    if (strcmp(dijkstraArray[interchangeCount+1].previous, dijkstraArray[interchangeCount+1].name)==0) way_found=false;
    //if (way_found==true) printpath(dijkstraArray, interchangeCount+1);
}

//void printpath (struct dijkstra array[], int length)
//{
//    char *steps[30];
//    char next[50];
//
//    for (int i = length; i >= 0; i--)
//    {
//        for (int j = 0; j < length; j++)
//        {
//            if (strcmp(array[j].name, array[i].prev)==0)
//            {
//                strcpy(next, array[j]);
//            }
//        }
//        steps[i]= (char*) malloc(255*sizeof(char));
//        if (i==length)
//        {
//            printf("Zum Schluss folgen Sie der A%d für %d km bis zu Ihrem Ziel %s\n", getnumber(array[i].name), (array[i].distanceToStart - array[i-1].distanceToStart), array[i].name);
//        }
//        else if (strcmp(array[i].name, array[i].previous)==0)
//        {
//            printf("\n\nStarten Sie bei %s und folgen Sie der A%d für %km bis zum Kreuz %s\n", array[i].name, getnumber(array[i].name), )
//        }
//
//    }
//
//}

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
