#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list_functions.c"
#include "list_sort.c"

int main()
{
    bool runloop = 1; //Variable zum Beenden der Menü-Schleife
    char userentry; //Variable zur Benutzereingabe

    //Begrüßungstext und Erläuterung der Optionen
    printf("Willkommen bei Ihrem Autobahnnavigator!\nDies sind Ihre Eingabeoptionen:\n\n");
    printf("R = Routenberechnung\nA = Anzeige und Bearbeitung der Ausfahrten und Autobahnkreuze\nX = Beenden\n\n");

    //Menü-Schleife
    do
    {
        fflush(stdin);              //Löschen des Buffers, damit Scanf bei jedem Schleifendurchlauf ausgeführt wird
        scanf("%c", &userentry);    //Einlesen der Benutzereingabe
        switch(userentry)           //Überprüfen der Benutzereingabe
        {
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
        }
    } while (runloop);

    return 0;
}
