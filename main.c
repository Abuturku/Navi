#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list_functions.c"
#include "list_sort.c"

int main()
{
    bool runloop = 1; //Variable zum Beenden der Men�-Schleife
    char userentry; //Variable zur Benutzereingabe

    //Begr��ungstext und Erl�uterung der Optionen
    printf("Willkommen bei Ihrem Autobahnnavigator!\nDies sind Ihre Eingabeoptionen:\n\n");
    printf("R = Routenberechnung\nA = Anzeige und Bearbeitung der Ausfahrten und Autobahnkreuze\nB = Beenden\n\n");

    //Men�-Schleife
    do
    {
        scanf("%c", &userentry);
        switch(userentry)
        {
        case 'R': case 'r': printf("Die Eingabe war R\n"); break;   //vorl�ufig
        case 'A': case 'a': printf("Die Eingabe war A\n"); break;
        case 'B': case 'b': runloop=0;
        break;
        default:
        printf("Unbekannte Eingabe.\nFolgende Befehle sind zulaessig:\n");
        printf("R = Routenberechnung\nA = Anzeige und Bearbeitung der Ausfahrten und Autobahnkreuze\nB = Beenden\n\n");
        }
    } while (runloop);


/*

    // Hier m�gt ihr eure Kekse

    int testvar;
    printf("1 fuer testen! 2 fuer beenden! \n");
    do
    {

        scanf("%d", &testvar);
    }while(testvar != 1 && testvar != 2);

    if(testvar == 1)
    {
        func_add();
    }
    if(testvar == 2)
    {
        return 0;
    }*/
    return 0;
}
