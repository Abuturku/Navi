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
void func_cancel();
void func_delete();
void func_change();
void quicksort(int first, int last);
void sort_list();
int main();


/*
*
*   v_0_2_1
*   func_list()     Listenausgabe
*   func_delete()   neue Listenausgabe func_list()
*   func_change()   neue Listenausgabe func_list()
*   main()          Überarbeitetes Hauptmenü mit switch-case basierend auf ascii-Werten
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
    char    userentry   Benutzereingabe
    */
    char userentry;
    int user_ascii;

    /* Begrüßungstext */
    printf("Willkommen bei Ihrem Autobahnnavigator!\n");

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
        func_add();
        break;

    case 76: case 108:
        sort_list();
        break;

    case 81: case 113:
        printf("Programm beendet!\n\n");
        return EXIT_SUCCESS;
    }
}
