#ifndef MATRIZ
#define MATRIZ

typedef double** Matriz;

double** mat_cria( int m, int n );

void mat_libera( int m, double** A);

void mat_transposta ( int m, int n, double** A, double** T );

void mat_multv ( int m, int n, double** A, double* V, double* W );

void mat_multm ( int m, int n, int q, double** A, double** B, double** C );

void mat_imprime( char* title, int m, int n, double** A );

void vec_imprime(char* title, double* v, int n);

void mat_zeram( int m, int n, double** A );

void mat_zerav( int m, double* V );

double mat_det3( double** M );

void mat_preenche_ID( int m, double** A);

#endif
