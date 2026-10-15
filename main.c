#include <stdio.h>
#include "functions.h"

int main ()
{
    int retorno = menu ();
    
    if (retorno == -1)
    {
        return 1;
    }
    return 0;
}