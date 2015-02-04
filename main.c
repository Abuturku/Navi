#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list_functions.c"
#include "list_sort.c"

int main()
{
    bool runloop = 1; //Variable zum Beenden der Menü-Schleife
    char userentry[2]; //Variable zur Benutzereingabe


    // Begrüßungstext
    printf("Willkommen bei Ihrem Autobahnnavigator!\n");
    //Begrüßungstext und Erläuterung der Optionen
    printf("Willkommen bei Ihrem Autobahnnavigator!\nDies sind Ihre Eingabeoptionen:\n\n");
    printf("R = Routenberechnung\nA = Anzeige und Bearbeitung der Ausfahrten und Autobahnkreuze\nX = Beenden\n\n");

    do
    {
        /*
        *   Geändert zur besseren Lesbarkeit
        */
        //Erläuterung der Optionen
        printf("Dies sind Ihre Eingabeoptionen:\n\n");
        printf("R = Routenberechnung\n");
        printf("A = Anzeige und Bearbeitung der Ausfahrten und Autobahnkreuze\n");
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
        else
        {
            printf("Falsche Eingabe!\n\n\n");
        }

    }while(userentry != 'r' && userentry != 'a' && userentry != 'q');

    return 0;

}







/*
    //Menü-Schleife
    do
    {
        fflush(stdin);              //Löschen des Buffers, damit Scanf bei jedem Schleifendurchlauf ausgeführt wird
        scanf("%c", &userentry);    //Einlesen der Benutzereingabe
        switch(userentry)           //Überprüfen der Benutzereingabe
        {
<<<<<<< HEAD
        case 'R':
        case 'r':
            printf("Tempor%cre Wartungsarbeiten. Wir bitten um Geduld.\n", ae);
            break; //Funktionsaufruf: Listenbearbeitung
        case 'A':
        case 'a':
            printf("\nL = Liste ausgeben\nB = Liste bearbeiten\n");
            scanf("%c",&userentry);
            if ((userentry=='L')||(userentry=='l'))
            {
                printf("ist in Arbeit");    //TODO
                break;
            }
            else if ((userentry =='B')||(userentry=='b'))
            {
                func_add();    //Testen
                break;
            }
        case 'Q':
        case 'q':
            runloop=0;
            break;
        default:
            printf("Unbekannte Eingabe.\nFolgende Befehle sind zul%cssig:\n", ae);
            printf("R = Routenberechnung\nA = Anzeige und Bearbeitung der Ausfahrten und Autobahnkreuze\nQ = Beenden\n\n");
=======
        //Routenberechnung
        case 'R': case 'r': printf("Tempor%cre Wartungsarbeiten. Wir bitten um Geduld.\n", ae); break; //TODO: Funktionsaufruf: Listenbearbeitung
        //Listenansicht
        case 'A': case 'a':
            printf("\nL = Liste ausgeben\nB = Liste bearbeiten\n"); break;
            case 'L': case 'l': printf("ist in Arbeit\n"); break; //TODO -> Liste von Ausfahrten oder Kreuzen?; -> Autobahnnummer? (Bei 0 alle ausgeben).....
            case 'B': case 'b': func_add(); break;   //Testen
        //Exit
        case 'X': case 'x': runloop=0;
        break;
        //Abfangen Fehleingabe
        default:
            printf("\nUnbekannte Eingabe.\nFolgende Befehle sind zul%cssig:\n", ae);
            printf("R = Routenberechnung\nA = Anzeige und Bearbeitung der Ausfahrten und Autobahnkreuze\nX = Beenden\n\n");
>>>>>>> origin/master
        }
    }
    while (runloop);

    return 0;
}

*/
