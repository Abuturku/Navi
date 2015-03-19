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


void find_path(){

    int start_nr = 0;
    int start_km = 0;
    int dest_nr = 0;
    int dest_km = 0;

  char  start[256],
        destination[256],
        compare[256];
    char* temp;

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
    do {
            if (first==1) {
                printf("Bitte geben Sie den Namen des Startortes ein: ");
            }
            else {
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

    while(fgets(compare, 256, table))
    {

        /* Sollte der Stadtname nicht vorhandensein, wird nach einem neuen Namen gefragt*/
        if(strcmp(compare,start)==0)
        {
            start_found = 1;
        }




    }
     rewind(table);
    }while (start_found == 0);

    rewind(table);
    first = 1;

   do {
            if (first==1){
     printf("Bitte geben Sie den Namen des Zielortes ein: ");}
     else {
                 printf("Stadt nicht gefunden. Bitte geben Sie eine andere Stadt ein: ");}
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

    while(fgets(compare, 256, table))
    {
        if(strcmp(compare,destination)==0)
        {
        dest_found=1;
        }




    }
    rewind(table);
    }  while (dest_found == 0);
     rewind(table);

    printf(start);
    start_nr = getnumber(start);
    printf("%d\n",start_nr);
    start_km = getdistanz(start);
    printf("%d\n",start_km);
    printf(destination);
    dest_nr = getnumber(destination);
    printf("%d\n",dest_nr);
    dest_km = getdistanz(destination);
    printf("%d\n",dest_km);

    if (start_nr == dest_nr){
        if (start_km>dest_nr){
        printf("einfach die Autobahn fuer %d km langfahren. \n", start_km-dest_km);}
        else {
           printf("einfach die Autobahn fuer %d km langfahren. \n", dest_km-start_km);
        }
    }
    else {
        printf("keine Direktverbindung \n");
    }

    find_cross_by_nr(start_nr,dest_nr," ");
}


void find_cross_by_nr(int start_nr, int dest_nr, char start[256]){

char compare[256]={},
     name[256]={};

     FILE *table;
     table = fopen("autobahn.txt", "a+");
     rewind(table);


        while (fgets(compare, 256, table)){
            if(strcmp(compare,"KREUZ\n")==0){
                fgets(compare, 256, table);     //Name des Kreuzes
                 strcat(name,compare);
                fgets(compare, 256, table);     //Nummer des Kreuzes
                if (((atoi(compare))== start_nr)&& (strcmp(name,start)!=0)){
                    fgets(compare, 256, table);    //KM
                    fgets(compare, 256, table);    //leer
                    fgets(compare, 256, table);   //KREUZ
                     if(strcmp(compare,"KREUZ\n")==0){  // wenn es ne ausfahrt ist nicht weiter machen
                    fgets(compare, 256, table);  //Name
                    fgets(compare, 256, table); //NR
                    if (atoi(compare)==dest_nr){
                            printf("gefunden");
                            return;
                        }
                        else {

                            find_cross_by_nr(atoi(compare),dest_nr,name);

                        }}
                    }
                    //braucht man theoretisch nicht, wenn die start autobahn kein Kreuz hat, muss man gar keinen weg suchen...
               /* else if ((atoi(compare))== dest_nr){
                    fgets(compare, 256, table);    //KM
                    fgets(compare, 256, table);    //leer
                    fgets(compare, 256, table);   //KREUZ
                    fgets(compare, 256, table);  //Name
                    fgets(compare, 256, table); //NR
                    if (atoi(compare)==start_nr){
                        printf("gefunden");
                        return 1;
                        }
                    else {
                        rewind(table);
                       return find_cross_by_nr(atoi(compare),start_nr);

                        }
                    } */
                }
            }

        return 0 ;
        }



int getnumber(char city[]){     //die Autobahn NR zu einer Stadt werden ausgelesen

    char compare[256]={};

    FILE *table;
    table = fopen("autobahn.txt", "a+");
                rewind(table);

    while (fgets(compare, 256, table)){

        if(strcmp(compare,city)==0){
            fgets(compare, 256, table);
            return atoi(compare);
        }
    }
    rewind(table);
    return 0;
              }



int getdistanz(char city[]){        //die Autobahn KM zu einer Stadt werden ausgelesen
    char compare[256]={};

    FILE *table;
    table = fopen("autobahn.txt", "a+");
            rewind(table);

    while (fgets(compare, 256, table)){

        if(strcmp(compare,city)==0){
            fgets(compare, 256, table);
        fgets(compare, 256, table);
        return atoi(compare);
        }
    }
    rewind(table);
    return 0;

}

