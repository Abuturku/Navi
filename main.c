#include <stdio.h>
#include <stdlib.h>

/* Definitionen zur Ausgabe von Umlauten */
#define AE (unsigned char)142
#define ae (unsigned char)132
#define OE (unsigned char)153
#define oe (unsigned char)148
#define UE (unsigned char)154
#define ue (unsigned char)129
#define ss (unsigned char)225

int main()
{



    return 0;
}

void add_element()
{
    /* Variablendeklaration
    int     interchange     Kennung "Autobahnkreuz" (1) oder "Autobahnausfahrt" (2)
    */
    int interchange;

    /* Schleife zur Überprüfung auf valide Eingabe */
    do
    {
        /* Userabfrage Autobahnkreuz oder Autobahnausfahrt */
        printf("M%cchten Sie ein Autobahnkreuz (1) oder eine Autobahnausfahrt (2) hinzuf%cgen? ", oe, ue);
        scanf("%d", &interchange);

    }
    while(interchange != 1 && interchange != 2);


    /* Aufruf der entsprechende Funktion basierend auf Usereingabe */
    switch (interchange)
    {
    case 1:
        /* Aufruf der Funktion func_interchange da der User ein Autobahnkreuz hinzufügen möchte */
        func_interchange(interchange);
        break;


    case 2:
        /* Aufruf der Funktion func_exit da der User eine Autobahnausfahrt hinzufügen möchte */
        func_exit(interchange);
        break;

    }
}

void func_interchange(int interchange)
{
    /* Variablendeklaration
    int     interchange_nr_one      Erste Autobahn des Kreuzes
    int     interchange_nr_two      Zweite Autobahn des Kreuzes
    int     interchange_nr_one_km   Autobahnkilometer der ersten Autobahn
    int     interchange_nr_two_km   Autobahnkilometer der zweiten Autobahn
    */
    int interchange_nr_one, interchange_nr_two, interchange_nr_one_km, interchange_nr__two_km;



    /* Nummer der ersten Autobahn des Kreuzes */
    printf("\nBitte geben Sie die Nummer der ersten Autobahn des Kreuzes ein: ");
    scanf("%d", &interchange_nr_one);

    /* Kilometer des Kreuzes auf erster Autobahn */
    printf("\nBitte geben Sie den Autobahnkilometer der A%d ein, an dem sich das Kreuz befindet: ", interchange_nr_one);
    scanf("%d", &interchange_nr_one_km);

    /* Überprüfung ob erste Autobahn gleich zweiter Autobahn */
    do
    {
        /* Nummer der zweiten Autobahn des Kreuzes */
        printf("\nBitte geben Sie die Nummer der zweiten Autobahn des Kreuzes ein: ");
        scanf("%d", &interchange_nr_two);

        /* Fehlerausgabe bei Eingabe gleicher Autobahnnummer */
        if(interchange_nr_one == interchange_nr_two)
        {
            printf("%cbereinstimmung gefunden, bitte geben Sie eine andere Autobahn ein!\n", UE);
        }

    }
    while (interchange_nr_two == interchange_nr_one);

    /* Kilometer des Kreuzes auf zweiter Autobahn */
    printf("\nBitte geben Sie den Autobahnkilometer der A%d ein, an dem sich das Kreuz befindet: ", interchange_nr_two);
    scanf("%d", &interchange_nr__two_km);


    /* Öffnen der Datei mit Modus "a+" (APPEND+READ) = Neue Einträge werden an der Dateiende angehängt */
    FILE *table;
    table = fopen("autobahn.txt", "a+");

    /* Überprüfen ob Öffnen der Datei erfolgreich war */
    if(table == NULL)
    {
        printf("FEHLER");
        return 1;
    }

    /* Schreiben der neuen Werte in die Textdatei
        Kennung "Autobahnkreuz"
        Nummer erster Autobahn
        Kilometer erster Autobahn
        Nummer zweiter Autobahn
        Kilometer zweiter Autobahn
    */

    fprintf(table, "KREUZ\n");
    fprintf(table, "%d\n",      interchange_nr_one);
    fprintf(table, "%d\n",      interchange_nr_one_km);
    fprintf(table, "%d\n",      interchange_nr_two);
    fprintf(table, "%d\n\n",    interchange_nr__two_km);

    fclose(table);

}

void func_exit(int interchange)
{
    /* Variablendeklaration
    int     waynr   Autobahnnummer
    int     dist    Autobahnkilometer
    char    city    Stadtname
    */

    int waynr, dist;
    int line_count = 0;
    char city[100], compare[100];


    /* Öffnen der Datei mit Modus "a" (APPEND+READ) = Neue Einträge werden an der Dateiende angehängt */
    FILE *table;
    table = fopen("autobahn.txt", "a+");

    /* Überprüfen ob Öffnen der Datei erfolgreich war */
    if(table == NULL)
    {
        printf("FEHLER");
        return 1;
    }

    /* Stadt/Name der Autobahnausfahrt */
    printf("\nBitte geben Sie einen neuen Ort ein: ");
    scanf("%s", &city);

    /* Umwandlung des Städtenamens in einen String bestehend aus Kleinbuchstaben */
    for(int i = 0; city[i]; i++)
    {
        city[i] = tolower(city[i]);
    }

    //Jede Zeile der autobahn.txt auslesen und den Inhalt in compare zwischenspeichern
    while(fgets(compare, 100, table))
    {
        //Sollte der Stadtname bereits vorhanden sein, wird der Inhalt der folgenden Schleife ausgeführt
        while(strstr(compare,city))
        {
            printf("\nDieser Ort ist bereits verzeichnet.\nBitte geben Sie einen neuen Ort ein: ");

            //Stadtnamen erneut einlesen und nochmals in einen String aus Kleinbuchstaben umwandeln
            scanf("%s", city);
                for(int i = 0; city[i]; i++)
                {
                    city[i] = tolower(city[i]);
                }

            //Wieder an den Anfang der Datei autobahn.txt gehen
            rewind(table);
        }
    }

    /* Autobahnnummer */
    printf("\nBitte geben Sie die Autobahnnummer ein: ");
    scanf("%d", &waynr);

    /* Autobahnkilometer */
    printf("\nBitte geben Sie den Autobahnkilometer ein: ");
    scanf("%d", &dist);




    /* Schreiben der neuen Werte in die Textdatei
        Kennung "Autobahnausfahrt"
        Stadt
        Autobahnnummer
        Autobahnkilometer
    */

    fprintf(table, "AUSFAHRT\n");
    fprintf(table, "%s\n",      city);
    fprintf(table, "%d\n",      waynr);
    fprintf(table, "%d\n\n",    dist);

    fclose(table);

}


