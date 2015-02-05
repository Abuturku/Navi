#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list_functions.c"
#include "list_sort.c"



/*
*
*
*       EIGENER BRANCH
*
*
*/


int main()
{
    char userentry[2]; //Variable zur Benutzereingabe


    // Begrüßungstext
    printf("Willkommen bei Ihrem Autobahnnavigator!\n");

    do
    {
        /*
        *   Geändert zur besseren Lesbarkeit
        */
        //Erläuterung der Optionen
        printf("Dies sind Ihre Eingabeoptionen:\n\n");
        printf("R = Routenberechnung\n");
        printf("A = Anzeige und Bearbeitung der Ausfahrten und Autobahnkreuze\n");
        printf("L = sortlist\n");
        printf("Q = Beenden\n\n");

        /* Eingabe der Auswahl */
        printf("Ihre Auswahl: ");
        scanf("%s", &userentry);
        printf("\n\n");

        /* Umwandlung in Kleinbuchstabe */
        for(int i = 0; i < userentry[i]; i++)
        {
            userentry[i] = tolower(userentry[i]);
        }

        /* Aufruf der entsprechenden Funktion */
        if(strstr(userentry, "r"))
        {
            printf("Noch nicht implementiert!\n");
            break;
        }
        else if(strstr(userentry, "a"))
        {
            func_add();
            break;
        }
        else if(strstr(userentry, "q"))
        {
            printf("Programm beendet!\n");
            return EXIT_SUCCESS;
        }
        else if(strstr(userentry, "l"))
        {
            sort_list();
        }
        else
        {
            printf("Falsche Eingabe!\n\n\n");
        }

    }while(userentry != 'r' && userentry != 'a' && userentry != 'q');

    return 0;

}
