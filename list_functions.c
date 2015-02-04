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




/* ------------------------------
Hinzufügen neuer Einträge in Datei
---------------------------------
Oliver Scholz
DHBW Mosbach
Kurs INF14B
------------------------------ */
/*
int main()
{
    int main_menu;

    do
    {
        printf("W%chlen Sie eine der folgenden Funktionen:\n", ae);
        printf("(1) Eintrag hinzuf%cgen\n", ue);
        printf("(2) Eintrag %cndern\n", ae);
        printf("(3) Eintrag l%cschen\n", oe);
        printf("(4) Liste ausgeben\n");
        printf("(5) Route berechnen\n");
        printf("(6) Beenden\n\n");

        printf("Ihre Auswahl: ");
        scanf("%d", &main_menu);
        printf("\n\n");

    }while(main_menu > 5 && main_menu < 1);

    switch (main_menu)
    {
    case 1:
        func_add();
        break;

    case 3:
        func_delete();
        break;

    case 6:
        return EXIT_SUCCESS;

    }
}


*/


/* ----------------------------------------
    FUNKTION EINTRAG HINZUFÜGEN
---------------------------------------- */

//Funktionsdeklarationen, sonst später Problem
void func_add_interchange();
void func_add_exit();

void func_add()
{
    /* Variablendeklaration
    int     interchange     Kennung "Autobahnkreuz" (1) oder "Autobahnausfahrt" (2)
    */
    int interchange;

    /* Schleife zur Überprüfung auf valide Eingabe */
    do
    {
        /* Userabfrage Autobahnkreuz oder Autobahnausfahrt */
        printf("Was m%cchten Sie hinzuf%cgen?\n", oe, ue);
        printf("(1) Autobahnkreuz hinzuf%cgen\n", ue);
        printf("(2) Autobahnausfahrt hinzuf%cgen\n", ue);
        printf("(3) Abbruch\n\n");

        printf("Ihre Auswahl: ");
        scanf("%d", &interchange);

    }while(interchange != 1 && interchange != 2 && interchange != 3);

    /* Aufruf der entsprechende Funktion basierend auf Usereingabe */
    switch (interchange)
    {
    case 1:
        /* Aufruf der Funktion func_add_interchange da der User ein Autobahnkreuz hinzufügen möchte */
        func_add_interchange();
        break;

    case 2:
        /* Aufruf der Funktion func_add_exit da der User eine Autobahnausfahrt hinzufügen möchte */
        func_add_exit();
        break;

    case 3:
        /* Abbruch und Rückkehr in Hauptmenü */
        break;
    }

    printf("\n\n");

    main();         //TODO: vlt. extern main?
}





/* ----------------------------------------
    FUNKTION AUTOBAHNKREUZ HINZUFÜGEM
---------------------------------------- */

void func_add_interchange()         //TODO: Exit-Option
{
    printf("\n\n");

    /* Variablendeklaration
    int     interchange_nr_one      Erste Autobahn des Kreuzes
    int     interchange_nr_two      Zweite Autobahn des Kreuzes
    int     interchange_nr_one_km   Autobahnkilometer der ersten Autobahn
    int     interchange_nr_two_km   Autobahnkilometer der zweiten Autobahn
    char    interchange_name        Name des Autobahnkreuzes
    char    compare                 Vergleichsstring aus Datei
    */
    int interchange_nr_one, interchange_nr_two, interchange_nr_one_km, interchange_nr_two_km;
    char interchange_name[100], compare[100];

    /* Öffnen der Datei mit Modus "a+" (APPEND+READ) = Neue Einträge werden an der Dateiende angehängt */
    FILE *table;
    table = fopen("autobahn.txt", "a+");

    /* Überprüfen ob Öffnen der Datei erfolgreich war */
    if(table == NULL)
    {
        printf("FEHLER");
        return 1;                   //TODO: Void funktion -> return 1?!
    }


    /* Name des Autobahnkreuzes */
    printf("Bitte geben Sie den Namen des Autobahnkreuzes ein: ");
    scanf("%s", &interchange_name);
    printf("\n");

    /* Umwandlung des Autobahnkreuz-Namens in einen String bestehend aus Kleinbuchstaben */
    for(int i = 0; interchange_name[i]; i++)
    {
        interchange_name[i] = tolower(interchange_name[i]);
    }

    /* Jede Zeile der autobahn.txt auslesen und den Inhalt in compare zwischenspeichern */
    while(fgets(compare, 100, table))
    {
        /* Sollte der Stadtname bereits vorhanden sein, wird der Inhalt der folgenden Schleife ausgeführt */
        if(strstr(compare,interchange_name))
        {
            printf("Dieses Kreuz ist bereits verzeichnet.\n\nBitte geben Sie einen neuen Namen ein: ");

            /* Stadtnamen erneut einlesen und nochmals in einen String aus Kleinbuchstaben umwandeln */
            scanf("%s", interchange_name);
            printf("\n");

            for(int i = 0; interchange_name[i]; i++)
            {
                interchange_name[i] = tolower(interchange_name[i]);
            }

            /* Gehe zu Anfang der Datei autobahn.txt */
            rewind(table);
        }
    }

    /* Nummer der ersten Autobahn des Kreuzes */
    printf("Bitte geben Sie die Nummer der ersten Autobahn des Kreuzes ein: ");
    scanf("%d", &interchange_nr_one);
    printf("\n");

    /* Kilometer des Kreuzes auf erster Autobahn */
    printf("Bitte geben Sie den Autobahnkilometer der A%d ein, an dem sich das Kreuz befindet: ", interchange_nr_one);
    scanf("%d", &interchange_nr_one_km);
    printf("\n");

    /* Überprüfung ob erste Autobahn gleich zweiter Autobahn */
    do
    {
        /* Nummer der zweiten Autobahn des Kreuzes */
        printf("Bitte geben Sie die Nummer der zweiten Autobahn des Kreuzes ein: ");
        scanf("%d", &interchange_nr_two);
        printf("\n");

        /* Fehlerausgabe bei Eingabe gleicher Autobahnnummer */
        if(interchange_nr_one == interchange_nr_two)
        {
            printf("%cbereinstimmung gefunden, bitte geben Sie eine andere Autobahn ein!\n", UE);
        }

    }while (interchange_nr_two == interchange_nr_one);

    /* Kilometer des Kreuzes auf zweiter Autobahn */
    printf("Bitte geben Sie den Autobahnkilometer der A%d ein, an dem sich das Kreuz befindet: ", interchange_nr_two);
    scanf("%d", &interchange_nr_two_km);


    /* Schreiben der neuen Werte in die Textdatei
        Kennung "Autobahnkreuz"
        Name des Kreuzes
        Nummer erster Autobahn
        Kilometer erster Autobahn

        Kennung "Autobahnkreuz"
        Name des Kreuzes
        Nummer zweiter Autobahn
        Kilometer zweiter Autobahn
    */
    fprintf(table, "KREUZ\n"     );
    fprintf(table, "%s\n",       interchange_name);
    fprintf(table, "%d\n",       interchange_nr_one);
    fprintf(table, "%d\n\n",     interchange_nr_one_km);

    fprintf(table, "KREUZ\n"     );
    fprintf(table, "%s\n",       interchange_name);
    fprintf(table, "%d\n",       interchange_nr_two);
    fprintf(table, "%d\n\n",     interchange_nr_two_km);

    fclose(table);

}





/* ----------------------------------------
    FUNKTION AUTOBAHNAUSFAHRT HINZUFÜGEN
---------------------------------------- */

void func_add_exit()
{
    printf("\n\n");

    /* Variablendeklaration
    int     waynr   Autobahnnummer
    int     dist    Autobahnkilometer
    char    city    Stadtname
    char    compare Vergleichsstring aus Datei
    */
    int waynr, dist;
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
    printf("Bitte geben Sie einen neuen Ort ein: ");
    scanf("%s", &city);
    printf("\n");

    /* Umwandlung des Städtenamens in einen String bestehend aus Kleinbuchstaben */
    for(int i = 0; city[i]; i++)
    {
        city[i] = tolower(city[i]);
    }

    /* Jede Zeile der autobahn.txt auslesen und den Inhalt in compare zwischenspeichern */
    while(fgets(compare, 100, table))
    {
        /* Sollte der Stadtname bereits vorhanden sein, wird der Inhalt der folgenden Schleife ausgeführt */
        if(strstr(compare,city))
        {
            printf("Dieser Ort ist bereits verzeichnet.\n\nBitte geben Sie einen neuen Ort ein: ");

            /* Stadtnamen erneut einlesen und nochmals in einen String aus Kleinbuchstaben umwandeln */
            scanf("%s", city);
            printf("\n");

            for(int i = 0; city[i]; i++)
            {
                city[i] = tolower(city[i]);
            }

            /* Gehe zu Anfang der Datei autobahn.txt */
            rewind(table);
        }
    }

    /* Autobahnnummer */
    printf("Bitte geben Sie die Autobahnnummer ein: ");
    scanf("%d", &waynr);
    printf("\n");

    /* Autobahnkilometer */
    printf("Bitte geben Sie den Autobahnkilometer ein: ");
    scanf("%d", &dist);

    /* Schreiben der neuen Werte in die Textdatei
        Kennung "Autobahnausfahrt"
        Stadt
        Autobahnnummer
        Autobahnkilometer
    */
    fprintf(table, "AUSFAHRT\n"     );
    fprintf(table, "%s\n",          city);
    fprintf(table, "%d\n",          waynr);
    fprintf(table, "%d\n\n",        dist);

    fclose(table);

}





/* ----------------------------------------
    FUNKTION EINTRAG LÖSCHEN
---------------------------------------- */

void func_delete()
{
    FILE *table;
    table = fopen("autobahn.txt", "a+");

    FILE *tempdat;
    tempdat = fopen("temp.txt", "w+");

    fseek(table, 0, SEEK_END);

    /*
    int         n           Nummerierung der Listeneinträge
    int         line_count  Zeilenanzahl der Datei autobahn.txt
    int         length      Bytegröße der Datei
    int         delete_line Zeie des zu löschenden Eintrags
    */
    int n, line_count, length, delete_line;

    length = ftell(table);
    line_count = 2;
    n = 0;
    delete_line = 1;

    /* Gehe zu Anfang der Datei autobahn.txt */
    rewind(table);

    /*
    char    temp            Zwischenspeicher für Einträge
    char    city_delete     Usereingabe des zu löschenden Eintrags
    char    all_entries     Alle Einträge der Datei
    */
    char temp[length], city_delete[length], all_entries[length];

    /* Erstellen der Liste aller Einträge */
    while(( fgetc(table) != EOF ))
    {
        n = n+1;

        fgets(temp, length, table);
        fgets(all_entries, length, table);

        for(int i = 0; i < 3; i++)
        {
            fgets(temp, length, table);
        }
        printf("(%d) %s", n, all_entries);

        line_count = line_count + 5;
    }

    /* Usereingabe des zu löschenden Eintrags */
    printf("\n\n");
    printf("Welchen Eintrag m%cchten Sie l%cschen?\n", oe, oe);
    scanf("%s", &city_delete);
    printf("\n");

    rewind(table);

    /* Überprüfung ob der Eintrag vorhanden ist */
    /*--------------------------------------------------------------
    ----------------------------------------------------------------
    ----------------------------------------------------------------
    ----------------------------------------------------------------
    ----------------------------------------------------------------
    ----------------------------------------------------------------
    --------------------------------------------------------------*/

    /* Umwandeln der Usereingabe in String aus Kleinbuchstaben */
    for(int i = 0; city_delete[i]; i++)
    {
        city_delete[i] = tolower(city_delete[i]);
    }

    /* Gehe zu Anfang der Datei autobahn.txt */
    rewind(table);

    /* Vergleichen der Einträge und herausfinden der Zeile des zu löschenden Eintrags */
    while(fgets(all_entries, length, table))
    {
        if(strstr(all_entries, city_delete))
        {
            break;
        }
        delete_line = delete_line + 1;
    }

    /* Gehe zu Anfang der Datei autobahn.txt */
    rewind(table);



    /* Lesen der Einträge bis zu dem zu löschenden Eintrag aus autobahn.txt und Schreiben dieser Einträge in temp.txt */
    for(int i = 1; i < delete_line - 1; i++)
    {
        fgets(all_entries, length, table);
        fprintf(tempdat, "%s", all_entries);
    }

    /* Unterscheidung ob zu löschender Eintrag ein KREUZ oder eine AUSFAHRT ist */
    fgets(temp, length, table);
    if(strstr(temp, "KREUZ"))
    {
        /* Überspringen des zu löschenden Eintrags */
        for(int j = delete_line; j < (delete_line + 9); j++)
        {
            fgets(temp, length, table);
        }
        /* Lesen der Einträge ab dem zu löschenden Eintrag aus autobahn.txt und Schreiben dieser Einträge in temp.txt */
        for(int k = (delete_line + 10); k <= (line_count - 1); k++)
        {
            fgets(all_entries, length, table);
            fprintf(tempdat, "%s", all_entries);
        }

        printf("Eintrag gel%cscht!\n\n", oe);
    }
    else
    {
        /* Überspringen des zu löschenden Eintrags */
        for(int l = delete_line; l < (delete_line + 4); l++)
        {
            fgets(temp, length, table);
        }
        /* Lesen der Einträge ab dem zu löschenden Eintrag aus autobahn.txt und Schreiben dieser Einträge in temp.txt */
        for(int m = (delete_line + 5); m <= (line_count - 1); m++)
        {
            fgets(all_entries, length, table);
            fprintf(tempdat, "%s", all_entries);
        }

        printf("Eintrag gel%cscht!\n\n", oe);
    }

    fclose(tempdat);
    fclose(table);

    /* Löschen der Datei autobahn.txt und umbenennen der Datei temp.txt in autobahn.txt */
    remove("autobahn.txt");
    rename("temp.txt", "autobahn.txt");

    main();
}
