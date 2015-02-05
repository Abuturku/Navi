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





/*
*
*   v0_1_5
*
*/





/* ------------------------------
Hinzufügen neuer Einträge in Datei
---------------------------------
Oliver Scholz
DHBW Mosbach
Kurs INF14B
------------------------------ */




/* Funktionsdeklarationen, sonst später Problem */
void func_add_interchange();
void func_add_exit();
void func_cancel();
void func_delete();
void func_change();





/* ----------------------------------------
    FUNKTION ABBRUCH
---------------------------------------- */

void func_cancel(char cancel_string[256])
{
    if(strstr(cancel_string, "cancel"))
    {
        printf("Vom Nutzer abgerochen!\n");
        printf("\n\n");
        main();
        exit(0);
    }
}





/* ----------------------------------------
    FUNKTION EINTRAG HINZUFÜGEN
---------------------------------------- */

void func_add()
{
    /* Variablendeklaration
    int     interchange     Kennung "Autobahnkreuz" (1) oder "Autobahnausfahrt" (2)
    */
    int interchange;

    /* Schleife zur Überprüfung auf valide Eingabe */
    do
    {
        printf("\n\n");

        /* Userabfrage Autobahnkreuz oder Autobahnausfahrt */
        printf("Was m%cchten Sie hinzuf%cgen?\n", oe, ue);
        printf("(1) Autobahnkreuz hinzuf%cgen\n", ue);
        printf("(2) Autobahnausfahrt hinzuf%cgen\n", ue);
        printf("(3) Eintrag l%cschen\n", oe);
        printf("(4) Eintrag %cndern\n", ae);
        printf("(5) Abbruch\n\n");

        printf("Ihre Auswahl: ");
        scanf("%d", &interchange);

        printf("\n\n");

    }while(interchange != 1 && interchange != 2 && interchange != 3 && interchange != 4 && interchange != 5);

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
        /* Aufruf der Funktion func_delete da der User einen Eintrag löschen möchte */
        func_delete();
        break;

    case 4:
        /* Aufruf der Funktion func_change da der User einen Eintrag löschen möchte */
        func_change();
        break;

    case 5:
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

    /* Öffnen der Datei mit Modus "a+" (APPEND+READ) = Neue Einträge werden an der Dateiende angehängt */
    FILE *table;
    table = fopen("autobahn.txt", "a+");

    /* Überprüfen ob Öffnen der Datei erfolgreich war */
    if(table == NULL)
    {
        printf("Fehler beim %cffnen der Datei!", oe);
        func_cancel("cancel");
    }

    /* Variablendeklaration
    char    interchange_nr_one      Erste Autobahn des Kreuzes
    char    interchange_nr_two      Zweite Autobahn des Kreuzes
    char    interchange_nr_one_km   Autobahnkilometer der ersten Autobahn
    char    interchange_nr_two_km   Autobahnkilometer der zweiten Autobahn
    char    interchange_name        Name des Autobahnkreuzes
    char    compare                 Vergleichsstring aus Datei
    */
    char    interchange_nr_one[256],
            interchange_nr_two[256],
            interchange_nr_one_km[256],
            interchange_nr_two_km[256],
            interchange_name[256],
            compare[256];

    /* Hinweis auf Möglichkeit zum Abbruch */
    printf("R%cckehr zum Hauptmen%c jederzeit mit der Eingabe von 'cancel' m%cglich!\n\n\n", ue, ue, oe);

    /* Name des Autobahnkreuzes */
    printf("Bitte geben Sie den Namen des Autobahnkreuzes ein: ");
    scanf("%s", &interchange_name);
    printf("\n");

    /* Umwandlung des Autobahnkreuz-Namens in einen String bestehend aus Kleinbuchstaben */
    for(int i = 0; interchange_name[i]; i++)
    {
        interchange_name[i] = tolower(interchange_name[i]);
    }

    /* Aufruf der Abbruchbedingung */
    func_cancel(interchange_name);

    /* Jede Zeile der autobahn.txt auslesen und den Inhalt in compare zwischenspeichern */
    while(fgets(compare, 256, table))
    {
        /* Sollte der Stadtname bereits vorhanden sein, wird der Inhalt der folgenden Schleife ausgeführt */
        if(strstr(compare,interchange_name))
        {
            printf("Dieses Kreuz ist bereits verzeichnet.");
            printf("\n\n");
            printf("Bitte geben Sie einen neuen Namen ein: ");

            /* Stadtnamen erneut einlesen und nochmals in einen String aus Kleinbuchstaben umwandeln */
            scanf("%s", interchange_name);
            printf("\n");

            for(int i = 0; interchange_name[i]; i++)
            {
                interchange_name[i] = tolower(interchange_name[i]);
            }
            /* Aufruf der Abbruchbedingung */
            func_cancel(interchange_name);

            /* Gehe zu Anfang der Datei autobahn.txt */
            rewind(table);
        }
    }

    /* Nummer der ersten Autobahn des Kreuzes */
    printf("Bitte geben Sie die Nummer der ersten Autobahn des Kreuzes ein: ");
    scanf("%s", &interchange_nr_one);
    printf("\n");
    /* Aufruf der Abbruchbedingung */
    func_cancel(interchange_nr_one);

    /* Kilometer des Kreuzes auf erster Autobahn */
    printf("Bitte geben Sie den Autobahnkilometer der A%s ein, an dem sich das Kreuz befindet: ", interchange_nr_one);
    scanf("%s", &interchange_nr_one_km);
    printf("\n");
    /* Aufruf der Abbruchbedingung */
    func_cancel(interchange_nr_one_km);

    /* Überprüfung ob erste Autobahn gleich zweiter Autobahn */
    do
    {
        /* Nummer der zweiten Autobahn des Kreuzes */
        printf("Bitte geben Sie die Nummer der zweiten Autobahn des Kreuzes ein: ");
        scanf("%s", &interchange_nr_two);
        printf("\n");
        /* Aufruf der Abbruchbedingung */
        func_cancel(interchange_nr_two);

        /* Fehlerausgabe bei Eingabe gleicher Autobahnnummer */
        if(strstr(interchange_nr_one, interchange_nr_two))
        {
            printf("%cbereinstimmung gefunden, bitte geben Sie eine andere Autobahn ein!\n", UE);
        }

    }while (strstr(interchange_nr_one, interchange_nr_two));

    /* Kilometer des Kreuzes auf zweiter Autobahn */
    printf("Bitte geben Sie den Autobahnkilometer der A%s ein, an dem sich das Kreuz befindet: ", interchange_nr_two);
    scanf("%s", &interchange_nr_two_km);
    /* Aufruf der Abbruchbedingung */
    func_cancel(interchange_nr_two_km);


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
    fprintf(table, "%s\n",       interchange_nr_one);
    fprintf(table, "%s\n\n",     interchange_nr_one_km);

    fprintf(table, "KREUZ\n"     );
    fprintf(table, "%s\n",       interchange_name);
    fprintf(table, "%s\n",       interchange_nr_two);
    fprintf(table, "%s\n\n",     interchange_nr_two_km);

    fclose(table);

}





/* ----------------------------------------
    FUNKTION AUTOBAHNAUSFAHRT HINZUFÜGEN
---------------------------------------- */

void func_add_exit()
{
    printf("\n\n");

    /* Öffnen der Datei mit Modus "a+" (APPEND+READ) = Neue Einträge werden an der Dateiende angehängt */
    FILE *table;
    table = fopen("autobahn.txt", "a+");

    /* Überprüfen ob Öffnen der Datei erfolgreich war */
    if(table == NULL)
    {
        printf("Fehler beim %cffnen der Datei!", oe);
        func_cancel("cancel");
    }

    /* Variablendeklaration
    char    city    Stadtname
    char    compare Vergleichsstring aus Datei
    char    waynr   Autobahnnummer
    char    dist    Autobahnkilometer
    */
    char    city[256],
            compare[256],
            waynr[256],
            dist[256];

    /* Hinweis auf Möglichkeit zum Abbruch */
    printf("R%cckehr zum Hauptmen%c jederzeit mit der Eingabe von 'cancel' m%cglich!\n\n\n", ue, ue, oe);

    /* Stadt/Name der Autobahnausfahrt */
    printf("Bitte geben Sie einen neuen Ort ein: ");
    scanf("%s", &city);
    printf("\n");

    /* Umwandlung des Städtenamens in einen String bestehend aus Kleinbuchstaben */
    for(int i = 0; city[i]; i++)
    {
        city[i] = tolower(city[i]);
    }
    /* Aufruf der Abbruchbedingung */
    func_cancel(city);

    /* Jede Zeile der autobahn.txt auslesen und den Inhalt in compare zwischenspeichern */
    while(fgets(compare, 256, table))
    {
        /* Sollte der Stadtname bereits vorhanden sein, wird der Inhalt der folgenden Schleife ausgeführt */
        if(strstr(compare,city))
        {
            printf("Dieser Ort ist bereits verzeichnet.");
            printf("\n\n");
            printf("Bitte geben Sie einen neuen Ort ein: ");

            /* Stadtnamen erneut einlesen und nochmals in einen String aus Kleinbuchstaben umwandeln */
            scanf("%s", city);
            printf("\n");

            for(int i = 0; city[i]; i++)
            {
                city[i] = tolower(city[i]);
            }
            /* Aufruf der Abbruchbedingung */
            func_cancel(city);

            /* Gehe zu Anfang der Datei autobahn.txt */
            rewind(table);
        }
    }

    /* Autobahnnummer */
    printf("Bitte geben Sie die Autobahnnummer ein: ");
    scanf("%s", &waynr);
    printf("\n");
    /* Aufruf der Abbruchbedingung */
    func_cancel(waynr);

    while(strstr(waynr, "0"))
    {
        /* Autobahnnummer */
        printf("Autobahnnummer 0 nicht zul%cssig!\n", ae);
        printf("Bitte geben Sie die Autobahnnummer ein: ");
        scanf("%s", &waynr);
        printf("\n");
        /* Aufruf der Abbruchbedingung */
        func_cancel(waynr);
    }


    /* Autobahnkilometer */
    printf("Bitte geben Sie den Autobahnkilometer ein: ");
    scanf("%s", &dist);
    /* Aufruf der Abbruchbedingung */
    func_cancel(dist);

    /* Schreiben der neuen Werte in die Textdatei
        Kennung "Autobahnausfahrt"
        Stadt
        Autobahnnummer
        Autobahnkilometer
    */
    fprintf(table, "AUSFAHRT\n"     );
    fprintf(table, "%s\n",          city);
    fprintf(table, "%s\n",          waynr);
    fprintf(table, "%s\n\n",        dist);

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

    /*
    int         n           Nummerierung der Listeneinträge
    int         line_count  Zeilenanzahl der Datei autobahn.txt
    int         delete_line Zeie des zu löschenden Eintrags
    */
    int     n,
            line_count,
            delete_line;

    line_count  =   1;
    n           =   0;
    delete_line =   1;


    /*
    char    temp            Zwischenspeicher für Einträge
    char    city_delete     Usereingabe des zu löschenden Eintrags
    char    all_entries     Alle Einträge der Datei
    char    stop            Stop wenn Eintrag zum löschen in Datei gefunden wurde
    */
    char    temp[256],
            city_delete[256],
            all_entries[256],
            stop[256];

    /* Hinweis auf Möglichkeit zum Abbruch */
    printf("R%cckehr zum Hauptmen%c jederzeit mit der Eingabe von 'cancel' m%cglich!\n\n\n", ue, ue, oe);

    if( fgetc(table) == EOF )
    {
        printf("\n\n");
        printf("Keie Eintr%cge gefunden!\n", ae);
        printf("\n\n");
        main();
        exit(0);
    }

    rewind(table);

    /* Erstellen der Liste aller Einträge */
    while(fgets(temp, 256, table))
    {
        n = n+1;

        fgets(all_entries, 256, table);

        /* Überspringen des zweiten Eintrag eines Autobahnkreuzes */
        if(strstr(temp, "KREUZ"))
        {
            for(int i = 0; i < 8; i++)
            {
                fgets(temp, 256, table);
            }
            line_count = line_count + 10;
        }
        else
        {
            for(int i = 0; i < 3; i++)
            {
                fgets(temp, 256, table);
            }
            line_count = line_count + 5;
        }
        printf("(%d) %s", n, all_entries);

    }

    /* Usereingabe des zu löschenden Eintrags */
    printf("\n\n");
    printf("Welchen Eintrag m%cchten Sie l%cschen?\n", oe, oe);
    scanf("%s", &city_delete);
    printf("\n");
    /* Aufruf der Abbruchbedingung */
    func_cancel(city_delete);

    /* Umwandeln der Usereingabe in String aus Kleinbuchstaben */
    for(int i = 0; city_delete[i]; i++)
    {
        city_delete[i] = tolower(city_delete[i]);
    }

    /* Gehe zu Anfang der Datei autobahn.txt */
    rewind(table);

    /* Überprüfung ob der Eintrag vorhanden ist */
    while((fgetc(table) != EOF))
    {
        /* Lesen nur der Namens-Werte der Einträge */
        fgets(temp, 256, table);
        fgets(stop, 256, table);

        for(int i = 0; i < 3; i++)
        {
            fgets(temp, 256, table);
        }

        /* Vergleichen des Namens mit der Usereingabe */
        /* Wenn Übereinstimmung gefunden, lösche Eintrag */
        if(strstr(stop, city_delete) != NULL)
        {
            rewind(table);
            /* Vergleichen der Einträge und herausfinden der Zeile des zu löschenden Eintrags */
            while(fgets(all_entries, 256, table))
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
                fgets(all_entries, 256, table);
                fprintf(tempdat, "%s", all_entries);
            }

            /* Unterscheidung ob zu löschender Eintrag ein KREUZ oder eine AUSFAHRT ist */
            fgets(temp, 256, table);

            if(strstr(temp, "KREUZ"))
            {
                /* Überspringen des zu löschenden Eintrags */
                for(int j = delete_line; j < (delete_line + 9); j++)
                {
                    fgets(temp, 256, table);
                }

                /* Lesen der Einträge ab dem zu löschenden Eintrag aus autobahn.txt und Schreiben dieser Einträge in temp.txt */
                for(int k = (delete_line + 10); k < line_count; k++)
                {
                    fgets(all_entries, 256, table);
                    fprintf(tempdat, "%s", all_entries);
                }

                printf("Eintrag gel%cscht!\n\n", oe);
            }
            else
            {
                /* Überspringen des zu löschenden Eintrags */
                for(int l = delete_line; l < (delete_line + 4); l++)
                {
                    fgets(temp, 256, table);
                }
                /* Lesen der Einträge ab dem zu löschenden Eintrag aus autobahn.txt und Schreiben dieser Einträge in temp.txt */
                for(int m = (delete_line + 5); m < line_count; m++)
                {
                    fgets(all_entries, 256, table);
                    fprintf(tempdat, "%s", all_entries);
                }

                printf("Eintrag gel%cscht!\n\n", oe);
            }

            fclose(tempdat);
            fclose(table);

            /* Löschen der Datei autobahn.txt und umbenennen der Datei temp.txt in autobahn.txt */
            remove("autobahn.txt");
            rename("temp.txt", "autobahn.txt");
        }
        /* Wenn keine Übereinstimmung gefunden, gebe Fehler aus */
        else
        {
            /* Nur wenn Dateiende erreicht ist */
            if(fgetc(table) == EOF)
            {
                printf("Eintrag nicht gefunden!\n");
                fclose(tempdat);
                fclose(table);
                remove("temp.txt");
            }
        }
    }
}





/* ----------------------------------------
    FUNKTION EINTRAG ÄNDERN
---------------------------------------- */

void func_change()
{
    FILE *table;
    table = fopen("autobahn.txt", "a+");

    FILE *tempdat;
    tempdat = fopen("temp.txt", "w+");

    /* Hinweis auf Möglichkeit zum Abbruch */
    printf("R%cckehr zum Hauptmen%c jederzeit mit der Eingabe von 'cancel' m%cglich!\n\n\n", ue, ue, oe);



    /* Löschen der Datei autobahn.txt und umbenennen der Datei temp.txt in autobahn.txt */
    remove("autobahn.txt");
    rename("temp.txt", "autobahn.txt");
}
