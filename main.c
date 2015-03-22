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
main()                  Begrüßungstext nur bei Programmstart
------------------------------------------------------------------------------------------------- */


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
#include <memory.h>
#include <conio.h>

#include "list_functions.c"
#include "list_sort.c"


/* Darstellung von Umlauten */
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

void find_path();

/* ---------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------- */


int main(int firstCall, char *argv[])
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

    //Dieser Text soll nur beim Programmstart erscheinen
    if (firstCall == 1)
    {
        /* Begrüßungstext */
        printf("---------------------------------------\n");
        printf("Willkommen bei Ihrem Autobahnnavigator!\n");
    }

    printf("---------------------------------------\n");
    printf("\n\n");


    FILE *table;
    table = fopen("autobahn.txt", "a+");

    rewind(table);

    /* Überprüfung ob autobahn.txt leer */
    if(fgetc(table) == EOF)
    {
        rewind(table);

        printf("---------------------------------------\n");
        printf("\n");
        printf("Datei war beim %cffnen leer, die Daten wurden aus der Backup-Datei %cbernommen.\n", OE, ue);
        printf("\n");
        printf("---------------------------------------\n");
        printf("\n");

        /*
        char    temp[256]   Zwischenspeicher
        */
        char temp[256];

        FILE *backup;
        backup = fopen("testautobahn.txt", "r");

        /* Überprüfung ob Backup vorhanden und Einträge vorhanden */
        if((backup == NULL) || (fgetc(backup) == EOF))
        {
            printf("Backup Datei nicht gefunden oder leer!\n");
            printf("\n");
            printf("---------------------------------------\n");
            printf("\n");
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
        printf("L = Ausgabe der Ausfahrten\n");
        printf("A = Bearbeitung der Ausfahrten und Autobahnkreuze\n");
        printf("Q = Beenden\n\n");

        /* Eingabe der Auswahl */
        printf("Ihre Auswahl: ");
        scanf("%s", &userentry);
        printf("\n");
        printf("---------------------------------------\n");

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
            printf("Falsche Eingabe!\n");
            printf("\n");
            printf("---------------------------------------\n");
            printf("\n");
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
        find_path();
        break;

    case 65: case 97:
        printf("\n");
        func_add(backup_empty);
        break;

    case 76: case 108:
        printf("\n");
        sort_list();
        break;

    case 81: case 113:
        printf("Programm beendet!\n");
        printf("---------------------------------------\n");
        printf("\n");
        return EXIT_SUCCESS;
    }

}
