#include "matriz.h"
#include <stdio.h>

typedef double** Matriz;

int main ( void )
{
	Matriz matriz = mat_cria( 2, 3 );
	Matriz matriz2 = mat_cria( 3, 2 );
	Matriz matriz3 = mat_cria( 2, 2 );
	Matriz matriz4 = mat_cria( 2, 2 );
	Matriz vetor = mat_cria( 1, 2 );
	Matriz vetorResultado = mat_cria( 1, 2 );

	matriz[0][0] = 1;
	matriz[0][1] = 2;
	matriz[0][2] = 3;
	matriz[1][0] = -2;
	matriz[1][1] = 0;
	matriz[1][2] = 4;

	matriz2[0][0] = 2;
	matriz2[0][1] = 3;
	matriz2[1][0] = 0;
	matriz2[1][1] = 1;
	matriz2[2][0] = -1;
	matriz2[2][1] = 4;

	vetor[0][0] = 3;
	vetor[0][1] = 5;

	mat_multm( 2, 3, 2, matriz, matriz2, matriz3 );

	mat_imprime( "matriz", 2, 3, matriz );
	mat_imprime( "matriz2", 3, 2, matriz2 );
	mat_imprime( "matriz x matriz2", 2, 2, matriz3 );

	mat_transposta(2, 2, matriz3, matriz4 );
	mat_imprime( "transposta do resultado", 2, 2, matriz4 );

	mat_multv( 2, 2, matriz4, &vetor[0][0], &vetorResultado[0][0] );
	mat_imprime( "vetor", 1, 2, vetor );
	mat_imprime( "transposta do resultado x vetor", 1, 2, vetorResultado );

	mat_libera( 2, matriz );
	mat_libera( 3, matriz2 );
	mat_libera( 2, matriz3 );
	mat_libera( 2, matriz4 );
	mat_libera( 1, vetor );
	mat_libera( 1, vetorResultado );

	return 0;
}
