/* -------------------------------------------------------------------------------------------------
Elsemann, Andreas       and.elsemann.14@dhbw-mosbach.de         Kurs INF14B Wintersemester 2014/2015
Latreider, Linda        lin.latreider.14@dhbw-mosbach.de        Kurs INF14B Wintersemester 2014/2015
Schick, Andreas         and.schick.14@dhbw-mosbach.de           Kurs INF14B Wintersemester 2014/2015
Scholz, Oliver          oli.scholz.14@dhbw-mosbach.de           Kurs INF14B Wintersemester 2014/2015

DHBW Mosbach
Lohrtalweg 10
74821 Mosbach
www.dhbw-mosbach.de
------------------------------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------------------------------
v0_3_1
func_change()       Logikfehler behoben, Eintrag kann nun geändert werden ohne den Namen zu ändern
func_cancel()       Löschen der temporären Dateien gefixed
main.c              grafische Überarbeitung
list_functions.c    grafische Überarbeitung
------------------------------------------------------------------------------------------------- */


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
#include <memory.h>


#define AE (unsigned char)142
#define ae (unsigned char)132
#define OE (unsigned char)153
#define oe (unsigned char)148
#define UE (unsigned char)154
#define ue (unsigned char)129
#define ss (unsigned char)225


/* Funktionsdeklarationen */

/* ----- main.c --------------- */
int main();

/* ----- list_functions.c ----- */
void func_add_interchange();
void func_add_exit();
void func_add(int backup_empty);
void func_cancel(char cancel_string[256], FILE* tempdat);
void func_delete();
void func_change();
int func_list(FILE *table);
int func_number(char verify[256]);

/* ----- list_sort.c ---------- */
void quicksort(char *cities[], int left, int right, char *waynrs[], char *dists[], int sortWith);
void sort_list();
void sortWayNrs(char *waynrs[], int left, int right);
void swap(char **arg1, char **arg2);


/* ---------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------- */


/* ----------------------------------------
    FUNKTION ABBRUCH
---------------------------------------- */

void func_cancel(char cancel_string[256], FILE* tempdat)
{
    if(strstr(cancel_string, "cancel"))
    {
        printf("Vom Nutzer abgerochen!\n");
        printf("\n\n");
        fclose(tempdat);
        remove("temp.txt");
        remove("change.txt");
        main();
        exit(0);
    }
}





/* ----------------------------------------
    FUNKTION ZAHLENWERT PRÜFEN
---------------------------------------- */

int func_number(char verify[256])
{
    for(int i = 0; verify[i]; i++)
    {
        if(verify[i] < 48 || verify[i] > 57)
        {
            printf("Bitte geben Sie einen g%cltigen Zahlenwert ein!\n\n", ue);
            return 1;
        }
    }

    return 0;
}





/* ----------------------------------------
    FUNKTION LISTE ERSTELLEN
---------------------------------------- */

int func_list(FILE *table)
{
    /*
    char    label       Kennung Kreuz oder Ausfahrt
    char    name        Name des Eintrags
    char    waynr_one   Autobahnnummer der ersten Autobahn
    char    waykm_one   Autobahnkilometer der ersten Autobahn
    char    waynr_two   Autobahnnummer der zweiten Autobahn
    char    waykm_two   Autobahnkilometer der zweiten Autobahn
    char    temp        Zwischenspeicher
    */
    char    label[256],
            name[256],
            waynr_one[256],
            waykm_one[256],
            waynr_two[256],
            waykm_two[256],
            temp[256];

    /*
    int     line_count  Zeilenanzahl
    */
    int line_count;

    line_count = 1;

    /* Überprüfung ob Einträge vorhanden sind */
    if(fgetc(table) == EOF)
    {
        printf("Keine Eintr%cge gefunden!\n", ae);
        printf("\n\n");
        main();
        exit (0);
    }

    rewind(table);

    /* Liste aller Einträge */
    while(fgets(label, 256, table))
    {
        /* Ausgabe der Autobahnkreuze */
        if(strstr(label, "KREUZ"))
        {
            fgets(name, 256, table);
            fgets(waynr_one, 256, table);
            fgets(waykm_one, 256, table);
            fgets(temp, 256, table);
            fgets(temp, 256, table);
            fgets(name, 256, table);
            fgets(waynr_two, 256, table);
            fgets(waykm_two, 256, table);

            name[0] = toupper(name[0]);

            printf("Kreuz    %s", name);

            line_count = line_count + 10;
        }
        /* Ausgabe der Autobahnausfahrten */
        if(strstr(label, "AUSFAHRT"))
        {
            fgets(name, 256, table);
            fgets(waynr_one, 256, table);
            fgets(waykm_one, 256, table);

            name[0] = toupper(name[0]);

            printf("Ausfahrt %s", name);

            line_count = line_count + 5;
        }
    }

    /* Rückgabe von int line_count */
    return line_count;

}





/* ----------------------------------------
    FUNKTION EINTRAG HINZUFÜGEN
---------------------------------------- */

void func_add(int backup_empty)
{
    /* Variablendeklaration
    char    entry       Kennung "Autobahnkreuz" (1) oder "Autobahnausfahrt" (2)
    */
    char entry;

    /* Überprüfung ob Backup Datei vorhanden war */
    if(backup_empty == 1)
    {
        /* Schleife zur Überprüfung auf valide Eingabe */
        do
        {
            /* Userabfrage Autobahnkreuz oder Autobahnausfahrt */
            printf("Was m%cchten Sie hinzuf%cgen?\n", oe, ue);
            printf("\n");
            printf("(1) Autobahnkreuz hinzuf%cgen\n", ue);
            printf("(2) Autobahnausfahrt hinzuf%cgen\n", ue);
            printf("(3) Beenden\n\n");


            printf("Ihre Auswahl: ");
            scanf("%s", &entry);
            printf("\n");
            if(entry != 51)
            {
                printf("---------------------------------------\n");
            }
            printf("\n");

            if(entry < 49 || entry > 51)
            {
                printf("Falsche Eingabe!\n");
                printf("\n");
                printf("---------------------------------------\n");
                printf("\n");
            }

        }while(entry < 49 || entry > 51);


        /* Aufruf der entsprechende Funktion basierend auf Usereingabe */
        switch (entry)
        {
        case 49:
            /* Aufruf der Funktion func_add_interchange da der User ein Autobahnkreuz hinzufügen möchte */
            func_add_interchange();
            break;

        case 50:
            /* Aufruf der Funktion func_add_exit da der User eine Autobahnausfahrt hinzufügen möchte */
            func_add_exit();
            break;

        case 51:
            /* Beenden des Programms */
            printf("---------------------------------------\n");
            printf("\n");
            printf("Programm beendet!\n");
            printf("\n");
            printf("---------------------------------------\n");
            printf("\n");
            exit(0);
            break;
        }

    }

    if(backup_empty == 0)
    {
        /* Schleife zur Überprüfung auf valide Eingabe */
        do
        {
            /* Userabfrage Autobahnkreuz oder Autobahnausfahrt */
            printf("Was m%cchten Sie durchf%chren?\n", oe, ue);
            printf("\n");
            printf("(1) Autobahnkreuz hinzuf%cgen\n", ue);
            printf("(2) Autobahnausfahrt hinzuf%cgen\n", ue);
            printf("(3) Eintrag l%cschen\n", oe);
            printf("(4) Eintrag %cndern\n", ae);
            printf("(5) Abbruch\n\n");

            printf("Ihre Auswahl: ");
            scanf("%s", &entry);
            printf("\n");
            if(entry != 53)
            {
                printf("---------------------------------------\n");
            }
            printf("\n");

            if(entry < 49 || entry > 53)
            {
                printf("Falsche Eingabe!\n");
                printf("\n");
                printf("---------------------------------------\n");
                printf("\n");
            }

        }while(entry < 49 || entry > 53);


        /* Aufruf der entsprechende Funktion basierend auf Usereingabe */
        switch (entry)
        {
        case 49:
            /* Aufruf der Funktion func_add_interchange da der User ein Autobahnkreuz hinzufügen möchte */
            func_add_interchange();
            break;

        case 50:
            /* Aufruf der Funktion func_add_exit da der User eine Autobahnausfahrt hinzufügen möchte */
            func_add_exit();
            break;

        case 51:
            /* Aufruf der Funktion func_delete da der User einen Eintrag löschen möchte */
            func_delete();
            break;

        case 52:
            /* Aufruf der Funktion func_change da der User einen Eintrag löschen möchte */
            func_change();
            break;

        case 53:
            /* Abbruch und Rückkehr in Hauptmenü */
            break;
        }

        main();
    }
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
        func_cancel("cancel", NULL);
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
    scanf("%s", interchange_name);
    printf("\n");

    /* Umwandlung des Autobahnkreuz-Namens in einen String bestehend aus Kleinbuchstaben */
    for(int i = 0; interchange_name[i]; i++)
    {
        interchange_name[i] = tolower(interchange_name[i]);
    }

    /* Aufruf der Abbruchbedingung */
    func_cancel(interchange_name, NULL);

    /* Jede Zeile der autobahn.txt auslesen und den Inhalt in compare zwischenspeichern */
    while(fgets(compare, 256, table))
    {
        /* Sollte der Stadtname bereits vorhanden sein, wird der Inhalt der folgenden Schleife ausgeführt */
        if(strstr(compare, interchange_name) != 0)
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
            func_cancel(interchange_name, NULL);

            /* Gehe zu Anfang der Datei autobahn.txt */
            rewind(table);
        }
    }

    /* Überprüfung auf Eingabe von Autobahnnummer "0" */
    do
    {
        do
        {
            /* Autobahnnummer */
            printf("Bitte geben Sie die Autobahnnummer der ersten Autobahn ein: ");
            scanf("%s", interchange_nr_one);
            printf("\n");
            /* Aufruf der Abbruchbedingung */
            func_cancel(interchange_nr_one, NULL);

        }while(func_number(interchange_nr_one) == 1);



        if(atoi(interchange_nr_one) == 0)
        {
            printf("Autobahnnummer 0 nicht zul%cssig!", ae);
            printf("\n\n");
        }

    }while(atoi(interchange_nr_one) == 0);

    /* Kilometer des Kreuzes auf erster Autobahn */
    do
    {
        printf("Bitte geben Sie den Autobahnkilometer der A%s ein, an dem sich das Kreuz befindet: ", interchange_nr_one);
        scanf("%s", interchange_nr_one_km);
        printf("\n");
        /* Aufruf der Abbruchbedingung */
        func_cancel(interchange_nr_one_km, NULL);
    }while(func_number(interchange_nr_one_km) == 1);

    /* Überprüfung ob erste Autobahn gleich zweiter Autobahn */
    do
    {
        /* Überprüfung auf Eingabe von Autobahnnummer "0" */
        do
        {
            do
            {
                /* Autobahnnummer */
                printf("Bitte geben Sie die Autobahnnummer der zweiten Autobahn ein: ");
                scanf("%s", interchange_nr_two);
                printf("\n");
                /* Aufruf der Abbruchbedingung */
                func_cancel(interchange_nr_two, NULL);

            }while(func_number(interchange_nr_two) == 1);

            if(atoi(interchange_nr_two) == 0)
            {
                printf("Autobahnnummer 0 nicht zul%cssig!", ae);
                printf("\n\n");
            }

        }while(atoi(interchange_nr_two) == 0);

        if(strcmp(interchange_nr_one, interchange_nr_two) == 0)
        {
            printf("Gleiche Autobahnnummer unzul%cssig.", ae);
            printf("\n\n");;
        }

    }while(strcmp(interchange_nr_one, interchange_nr_two) == 0);

    /* Kilometer des Kreuzes auf zweiter Autobahn */
    do
    {
        printf("Bitte geben Sie den Autobahnkilometer der A%s ein, an dem sich das Kreuz befindet: ", interchange_nr_two);
        scanf("%s", interchange_nr_two_km);
        printf("\n");
        /* Aufruf der Abbruchbedingung */
        func_cancel(interchange_nr_two_km, NULL);

    }while(func_number(interchange_nr_two_km) == 1);

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
        func_cancel("cancel", NULL);
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
    scanf("%s", city);
    printf("\n");

    /* Umwandlung des Städtenamens in einen String bestehend aus Kleinbuchstaben */
    for(int i = 0; city[i]; i++)
    {
        city[i] = tolower(city[i]);
    }
    /* Aufruf der Abbruchbedingung */
    func_cancel(city, NULL);

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
            func_cancel(city, NULL);

            /* Gehe zu Anfang der Datei autobahn.txt */
            rewind(table);
        }
    }

    /* Überprüfung auf Eingabe von Autobahnnummer "0" */
    do
    {
        do
        {
            /* Autobahnnummer */
            printf("Bitte geben Sie die Autobahnnummer ein: ");
            scanf("%s", waynr);
            printf("\n");
            /* Aufruf der Abbruchbedingung */
            func_cancel(waynr, NULL);

        }while(func_number(waynr) == 1);

        if(atoi(waynr) == 0)
        {
            printf("Autobahnnummer 0 nicht zul%cssig!", ae);
            printf("\n\n");
        }
    }while(atoi(waynr) == 0);

    /* Autobahnkilometer */
    do
    {
        printf("Bitte geben Sie den Autobahnkilometer ein: ");
        scanf("%s", dist);
        printf("\n");
        /* Aufruf der Abbruchbedingung */
        func_cancel(dist, NULL);

    }while(func_number(dist) == 1);

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
    int     line_count,
            delete_line;

    delete_line =   1;


    /*
    char    temp            Zwischenspeicher für Einträge
    char    city_delete     Usereingabe des zu löschenden Eintrags
    char    all_entries     Alle Einträge der Datei
    char    stop            Stop wenn Eintrag zum löschen in Datei gefunden wurde
    char    label           Kennung Kreuz oder Ausfahrt
    */
    char    temp[256],
            city_delete[256],
            all_entries[256],
            stop[256];

    /* Hinweis auf Möglichkeit zum Abbruch */
    printf("R%cckehr zum Hauptmen%c jederzeit mit der Eingabe von 'cancel' m%cglich!\n\n\n", ue, ue, oe);

    /* Aufruf der func_list() zum Erstellen der Liste und Übergabe von int line_count */
    line_count = func_list(table);

    /* Usereingabe des zu löschenden Eintrags */
    printf("\n\n");
    printf("Welchen Eintrag m%cchten Sie l%cschen? ", oe, oe);
    scanf("%s", city_delete);
    printf("\n");

    /* Umwandeln der Usereingabe in String aus Kleinbuchstaben */
    for(int i = 0; city_delete[i]; i++)
    {
        city_delete[i] = tolower(city_delete[i]);
    }

    /* Aufruf der Abbruchbedingung */
    func_cancel(city_delete, tempdat);

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
    table = fopen("autobahn.txt", "r");

    FILE *tempdat;
    tempdat = fopen("change.txt", "w+");

    /*
    int     changed     Wurde Eintrag geändert?
    */
    int     changed;

    changed = 0;

    /*
    char    change_entry[256]   zu änderner Eintrag
    char    label[256]          Kennung "Kreuz" oder "Ausfahrt"
    char    name[256]           Name des Eintrags
    char    waynr_one[256]      Nummer der ersten Autobahn
    char    dist_one[256]       Kilometer der ersten Autobahn
    char    waynr_two[256]      Nummer der zweiten Autobahn
    char    dist_two[256]       Kilometer der zweiten Autobahn
    char    temp[256]           Zwischenspeicher
    char    compare[256]        Vergleichsstring für neuen Namen
    char    change_name[256]    Zwischenspeicher des Namens
    */
    char    change_entry[256],
            label[256],
            name[256],
            waynr_one[256],
            dist_one[256],
            waynr_two[256],
            dist_two[256],
            temp[256],
            compare[256];

    /* Hinweis auf Möglichkeit zum Abbruch */
    printf("R%cckehr zum Hauptmen%c jederzeit mit der Eingabe von 'cancel' m%cglich!\n\n\n", ue, ue, oe);

    /* Aufruf einer Liste aller Einträge */
    func_list(table);

    printf("\n\n");

    /* Abfrage welcher Eintrag geändert werden soll */
    printf("Welchen Eintrag m%cchten Sie %cndern? ", oe, ae);
    scanf("%s", change_entry);
    printf("\n\n");


    /* Umwandeln der Eingabe in String aus Kleinbuchstaben */
    for(int i = 0; change_entry[i]; i++)
    {
        change_entry[i] = tolower(change_entry[i]);
    }

    /* Aufruf der Abbruchbedingung */
    func_cancel(change_entry, tempdat);

    /* Gehe zum Anfang der Datei "autobahn.txt" */
    rewind(table);

    /* Lesen, Schreiben und Überprüfung der Einträge */
    while(fgets(label, 256, table))
    {
        fgets(name, 256, table);

        /* Schreiben der Einträge die nicht verändert werden */
        if(strstr(name, change_entry) == 0)
        {
            if(strstr(label, "KREUZ") != 0)
            {
                fgets(waynr_one, 256, table);
                fgets(dist_one, 256, table);
                fgets(temp, 256, table);
                fgets(temp, 256, table);
                fgets(temp, 256, table);
                fgets(waynr_two, 256, table);
                fgets(dist_two, 256, table);
                fgets(temp, 256, table);

                fprintf(tempdat, "%s", label);
                fprintf(tempdat, "%s", name);
                fprintf(tempdat, "%s", waynr_one);
                fprintf(tempdat, "%s", dist_one);
                fprintf(tempdat, "%s", temp);
                fprintf(tempdat, "%s", label);
                fprintf(tempdat, "%s", name);
                fprintf(tempdat, "%s", waynr_two);
                fprintf(tempdat, "%s", dist_two);
                fprintf(tempdat, "%s", temp);
            }
            if(strstr(label, "AUSFAHRT") != 0)
            {
                fgets(waynr_one, 256, table);
                fgets(dist_one, 256, table);
                fgets(temp, 256, table);

                fprintf(tempdat, "%s", label);
                fprintf(tempdat, "%s", name);
                fprintf(tempdat, "%s", waynr_one);
                fprintf(tempdat, "%s", dist_one);
                fprintf(tempdat, "%s", temp);
            }
        }

        /* Überprüfung auf zu ändernden Eintrag */
        else if(strstr(name, change_entry) != 0)
        {
            changed = 1;

            /* Eingabe eines neuen Namen */
            printf("Bitte geben Sie den neuen Namen ein: ");
            scanf("%s", name);
            printf("\n");

            /* Umwandeln der Eingabe in String aus Kleinbuchstaben */
            for(int i = 0; name[i]; i++)
            {
                name[i] = tolower(name[i]);
            }

            /* Aurfruf der Abbruchbedingung */
            func_cancel(name, tempdat);


                /* Jede Zeile der autobahn.txt auslesen und den Inhalt in compare zwischenspeichern */
                while(fgets(compare, 256, table))
                {
                    /* Sollte der Stadtname bereits vorhanden sein, wird der Inhalt der folgenden Schleife ausgeführt */
                    if(strstr(compare, name) != 0 && strcmp(name, change_entry) != 0)
                    {
                        printf("Dieser Eintrag ist bereits verzeichnet.");
                        printf("\n\n");
                        printf("Bitte geben Sie einen neuen Namen ein: ");

                        /* Stadtnamen erneut einlesen und nochmals in einen String aus Kleinbuchstaben umwandeln */
                        scanf("%s", name);
                        printf("\n");

                        for(int i = 0; name[i]; i++)
                        {
                            name[i] = tolower(name[i]);
                        }
                        /* Aufruf der Abbruchbedingung */
                        func_cancel(name, tempdat);

                        /* Gehe zu Anfang der Datei autobahn.txt */
                        rewind(table);
                    }
                }


            /* zu ändernder Eintrag ist ein Autobahnkreuz */
            if(strstr(label, "KREUZ"))
            {
                /* Überspringen der alten Werte */
                fgets(temp, 256, table);
                fgets(temp, 256, table);
                fgets(temp, 256, table);
                fgets(temp, 256, table);
                fgets(temp, 256, table);
                fgets(temp, 256, table);
                fgets(temp, 256, table);
                fgets(temp, 256, table);

                /* Überprüfung auf Eingabe von Autobahnnummer "0" */
                do
                {
                    do
                    {
                        /* Autobahnnummer */
                        printf("Bitte geben Sie die neue Autobahnnummer der ersten Autobahn ein: ");
                        scanf("%s", waynr_one);
                        printf("\n");
                        /* Aufruf der Abbruchbedingung */
                        func_cancel(waynr_one, tempdat);

                    }while(func_number(waynr_one) == 1);

                    if(atoi(waynr_one) == 0)
                    {
                        printf("Autobahnnummer 0 nicht zul%cssig!", ae);
                        printf("\n\n");
                    }

                }while(atoi(waynr_one) == 0);

                /* Kilometer des Kreuzes auf erster Autobahn */
                do
                {
                    printf("Bitte geben Sie den neuen Autobahnkilometer der A%s ein, an dem sich das Kreuz befindet: ", waynr_one);
                    scanf("%s", dist_one);
                    printf("\n");
                    /* Aufruf der Abbruchbedingung */
                    func_cancel(dist_one, tempdat);

                }while(func_number(dist_one) == 1);

                /* Überprüfung ob erste Autobahn gleich zweiter Autobahn */
                do
                {
                    /* Überprüfung auf Eingabe von Autobahnnummer "0" */
                    do
                    {
                        do
                        {
                            /* Autobahnnummer */
                            printf("Bitte geben Sie die neue Autobahnnummer der zweiten Autobahn ein: ");
                            scanf("%s", waynr_two);
                            printf("\n");
                            /* Aufruf der Abbruchbedingung */
                            func_cancel(waynr_two, tempdat);

                        }while(func_number(waynr_two) == 1);

                        if(atoi(waynr_two) == 0)
                        {
                            printf("Autobahnnummer 0 nicht zul%cssig!", ae);
                            printf("\n\n");
                        }

                    }while(atoi(waynr_two) == 0);

                    if(strcmp(waynr_one, waynr_two) == 0)
                    {
                        printf("Gleiche Autobahnnummer unzul%cssig.", ae);
                        printf("\n\n");;
                    }

                }while(strcmp(waynr_one, waynr_two) == 0);

                /* Kilometer des Kreuzes auf zweiter Autobahn */
                do
                {
                    printf("Bitte geben Sie den neuen Autobahnkilometer der A%s ein, an dem sich das Kreuz befindet: ", waynr_two);
                    scanf("%s", dist_two);
                    printf("\n");
                    /* Aufruf der Abbruchbedingung */
                    func_cancel(dist_two, tempdat);

                }while(func_number(dist_two) == 1);

                /* Schreiben des geänderten Eintrags
                    Kennung "KREUZ"
                    Name
                    Autobahnnummer erster Autobahn
                    Kilometer erster Autobahn
                    <Leerzeile>
                    Kennung "KREUZ"
                    Name
                    Autobahnnummer zweiter Autobahn
                    Kilometer zweiter Autobahn
                    <Leerzeile>
                */
                fprintf(tempdat, "%s", label);
                fprintf(tempdat, "%s\n", name);
                fprintf(tempdat, "%s\n", waynr_one);
                fprintf(tempdat, "%s\n", dist_one);
                fprintf(tempdat, "%s", temp);
                fprintf(tempdat, "%s", label);
                fprintf(tempdat, "%s\n", name);
                fprintf(tempdat, "%s\n", waynr_two);
                fprintf(tempdat, "%s\n", dist_two);
                fprintf(tempdat, "%s", temp);
            }

            /* zu ändernder Eintrag ist eine Autobahnausfahrt */
            else if(strstr(label, "AUSFAHRT"))
            {
                fgets(temp, 256, table);
                fgets(temp, 256, table);
                fgets(temp, 256, table);

                /* Überprüfung auf Eingabe von Autobahnnummer "0" */
                do
                {
                    do
                    {
                        /* Autobahnnummer Autobahn */
                        printf("Bitte geben Sie die neue Nummer der Autobahn ein: ");
                        scanf("%s", waynr_one);
                        printf("\n");
                        /* Aufruf der Abbruchbedingung */
                        func_cancel(waynr_one, tempdat);

                    }while(func_number(waynr_one) == 1);

                    if(atoi(waynr_one) == 0)
                    {
                        printf("Autobahnnummer 0 nicht zul%cssig!", ae);
                        printf("\n\n");
                    }

                }while(atoi(waynr_one) == 0);


                /* Autobahnkilometer der Autobahn */
                do
                {
                    printf("Bitte geben Sie den neuen Kilometer der Autobahn ein: ");
                    scanf("%s", dist_one);
                    printf("\n");
                    /* Aufruf der Abbruchbedingung */
                    func_cancel(dist_one, tempdat);

                }while(func_number(dist_one) == 1);

                /* Schreiben des geänderten Eintrags
                    Kennung "AUSFAHRT"
                    Name
                    Autobahnnummer
                    Kilometer
                    <Leerzeile>
                */
                fprintf(tempdat, "%s", label);
                fprintf(tempdat, "%s\n", name);
                fprintf(tempdat, "%s\n", waynr_one);
                fprintf(tempdat, "%s\n", dist_one);
                fprintf(tempdat, "%s", temp);
            }
        }
    }

    /* Überprüfung ob ein Eintrag geändert wurde */
    if(changed == 0)
    {
        printf("Eintrag nicht gefunden!");
        printf("\n\n");
    }
    else
    {
        printf("Eintrag ge%cndert!", ae);
        printf("\n\n");
    }

    fclose(table);
    fclose(tempdat);

    remove("autobahn.txt");
    rename("change.txt", "autobahn.txt");
}
