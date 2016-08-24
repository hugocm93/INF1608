#include "matriz.h"
#include <stdio.h>


typedef double** Matriz;

int main ( void )
{
	Matriz matriz = mat_cria( 3, 3);

	matriz[0][0] = 1;
	matriz[0][2] = 6;
	matriz[1][1] = 2;
	matriz[2][2] = 3;

	mat_imprime( 3, 3, matriz );
	mat_libera( 3 , matriz );
	matriz = NULL;
	mat_imprime( 3, 3, matriz );
	
	return 0;
}


