#include <stdio.h>
#include <stdlib.h>

#include "list_functions.c"
#include "list_sort.c"

int main()
{

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
        sort_list();
    }
    return 0;
}
