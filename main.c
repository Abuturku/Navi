#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#include "list_functions.c"
#include "list_sort.c"





/*
*
*   v_0_2
*   func_add                    fixed "Loop of Doom"
*   func_delete()               Listenausgabe mit großem Anfangsbuchstaben
*   func_add_interchange()      Überprüfung der Gleichheit der Autobahnnummern überarbeitet
*   func_change()               Listenausgabe hinzugefügt
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
    char userentry[2];


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

        /* Umwandlung in Kleinbuchstabe */
        for(int i = 0; i < userentry[i]; i++)
        {
            userentry[i] = tolower(userentry[i]);
        }

        /* Aufruf der entsprechenden Funktion */
        if(strstr(userentry, "r"))
        {
            printf("Also Else!\n");
            break;
        }
        else if(strstr(userentry, "a"))
        {
            func_add();
            break;
        }
        else if(strstr(userentry, "l"))
        {
            sort_list();
            break;
        }
        else if(strstr(userentry, "q"))
        {
            printf("Programm beendet!\n");
            return EXIT_SUCCESS;
        }
        else
        {
            printf("\n\nFalsche Eingabe!\n\n\n");
        }

    }while(userentry != 'r' && userentry != 'a' && userentry != 'q' && userentry != 'l');

    return 0;

}
