#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <ctype.h>

#include "list_functions.c"
#include "list_sort.c"


/* Funktionsdeklarationen, sonst später Problem */
void func_add_interchange();
void func_add_exit();
void func_add(int backup_empty);
void func_cancel();
void func_delete();
void func_change();
void quicksort(char *cities[], int left, int right, char *waynrs[], char *dists[], int sortWith);
void sort_list();
int main();
int func_list(FILE *table);
int func_number(char verify[256]);


/*
*
*   v0_2_4
*   main()  Überprüfung ob autobahn.txt leer
*   main()	Übernahme aus testautobahn.txt (Backup-Daten) wenn autobahn.txt leer
*   main()	Aufruf spezieller func_add (nur func_add_exit und func_add_interchange) wenn Backup leer oder nicht gefunden
*
*/





/* ------------------------------
Hinzufügen neuer Einträge in Datei
---------------------------------
Oliver Scholz
DHBW Mosbach
Kurs INF14B
------------------------------ */




int main()
{

    /* Konsolenname festlegen */
    SetConsoleTitle("Autobahnnavigator 2015");

    /*
    int     backup_empty    1: Backup wurde nicht gefunden 0: Backup wurde gefunden
    int     user_ascii      ASCII-Wert des char userentry
    */
    int     backup_empty,
            user_ascii;

    /*
    char    userentry   Benutzereingabe
    */
    char userentry;

    /* Begrüßungstext */
    printf("Willkommen bei Ihrem Autobahnnavigator!\n");

    FILE *table;
    table = fopen("autobahn.txt", "a+");

    rewind(table);

    /* Überprüfung ob autobahn.txt leer */
    if(fgetc(table) == EOF)
    {
        rewind(table);

        printf("\nDatei war beim %cffnen leer, die Daten wurden aus der Backup-Datei %cbernommen.", OE, ue);
        printf("\n\n");

        /*
        char    temp[256]   Zwischenspeicher
        */
        char temp[256];

        FILE *backup;
        backup = fopen("testautobahn.txt", "r");

        /* Überprüfung ob Backup vorhanden und Einträge vorhanden */
        if((backup == NULL) || (fgetc(backup) == EOF))
        {
            printf("Backup Datei nicht gefunden oder leer!");
            printf("\n\n");
            /* Backup nicht vorhanden oder leer, Aufruf von func_add(backup_empty) zur Eingabe eines Wertes */
            backup_empty = 1;
            func_add(backup_empty);
        }

        rewind(backup);

        /* Übertragen des Backups in autobahn.txt */
        while(fgets(temp, 256, backup))
        {
            fprintf(table, "%s", temp);
        }

        fclose(backup);
    }

    fclose(table);

    /* Backup war vorhanden */
    backup_empty = 0;

    do
    {
        /* Erläuterung der Optionen */
        printf("Dies sind Ihre Eingabeoptionen:\n\n");
        printf("R = Routenberechnung\n");
        printf("A = Anzeige und Bearbeitung der Ausfahrten und Autobahnkreuze\n");
        printf("L = sortlist\n");
        printf("Q = Beenden\n\n");

        /* Eingabe der Auswahl */
        printf("Ihre Auswahl: ");
        scanf("%s", &userentry);
        printf("\n\n");

        user_ascii = userentry;

        if(user_ascii != 82
        && user_ascii != 114
        && user_ascii != 65
        && user_ascii != 97
        && user_ascii != 76
        && user_ascii != 108
        && user_ascii != 81
        && user_ascii != 113)
        {
            printf("Falsche Eingabe!\n\n");
        }

    }while(user_ascii != 82
        && user_ascii != 114
        && user_ascii != 65
        && user_ascii != 97
        && user_ascii != 76
        && user_ascii != 108
        && user_ascii != 81
        && user_ascii != 113);

    /* Aufruf der entsprechende Funktion basierend auf Usereingabe */
    switch (user_ascii)
    {
    case 82: case 114:
        printf("Also Else!");
        break;

    case 65: case 97:
        func_add(backup_empty);
        break;

    case 76: case 108:
        sort_list();
        break;

    case 81: case 113:
        printf("Programm beendet!\n\n");
        return EXIT_SUCCESS;
    }

}
