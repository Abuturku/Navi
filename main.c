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
    printf("R = Routenberechnung\nA = Anzeige und Bearbeitung der Ausfahrten und Autobahnkreuze\nQ = Beenden\n\n");

    //Menü-Schleife
    do
    {
        scanf("%c", &userentry);
        switch(userentry)
        {
        case 'R': case 'r': printf("Tempor%cre Wartungsarbeiten. Wir bitten um Geduld.\n", ae); break; //Funktionsaufruf: Listenbearbeitung
        case 'A': case 'a':
            printf("\nL = Liste ausgeben\nB = Liste bearbeiten\n"); break;
            case 'L': case 'l': printf("ist in Arbeit"); break; //TODO
            case 'B': case 'b': func_add(); break;   //Testen
        case 'Q': case 'q': runloop=0;
        break;
        }
        if (userentry!='R'&&userentry!='r'&&userentry!='A'&&userentry!='a'&&userentry!='L'&&userentry!='l'
            &&userentry!='B'&&userentry!='b'&&userentry!='Q'&&userentry!='q')
        {
            printf("Unbekannte Eingabe.\nFolgende Befehle sind zul%cssig:\n", ae);
            printf("R = Routenberechnung\nA = Anzeige und Bearbeitung der Ausfahrten und Autobahnkreuze\nQ = Beenden\n\n");
        }
    } while (runloop);

    return 0;
}
