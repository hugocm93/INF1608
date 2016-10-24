#include <stdio.h>
#include <stdlib.h>

#include "mmq.h"

/*Função auxiliar para testes*/
void teste(char c, int m, int n, double** A, double* b);

int main(void)
{
  Matriz m1 = mat_cria(5, 3);
  m1[0][0] = 3;
  m1[0][1] = -1;
  m1[0][2] = 2;
  m1[1][0] = 4;
  m1[1][1] = 1;
  m1[1][2] = 0;
  m1[2][0] = -3;
  m1[2][1] = 2;
  m1[2][2] = 1;
  m1[3][0] = 1;
  m1[3][1] = 1;
  m1[3][2] = 5;
  m1[4][0] = -2;
  m1[4][1] = 0;
  m1[4][2] = 3;

  double b1[5];
  b1[0] = 10;
  b1[1] = 10;
  b1[2] = -5;
  b1[3] = 15;
  b1[4] = 0;

  Matriz m2 = mat_cria(5, 4);
  m2[0][0] = 4;
  m2[0][1] = 2;
  m2[0][2] = 3;
  m2[0][3] = 0;
  m2[1][0] = -2;
  m2[1][1] = 3;
  m2[1][2] = -1;
  m2[1][3] = 1;
  m2[2][0] = 1;
  m2[2][1] = 3;
  m2[2][2] = -4;
  m2[2][3] = 2;
  m2[3][0] = 1;
  m2[3][1] = 0;
  m2[3][2] = 1;
  m2[3][3] = -1;
  m2[4][0] = 3;
  m2[4][1] = 1;
  m2[4][2] = 3;
  m2[4][3] = -2;


  double b2[5];
  b2[0] = 10;
  b2[1] = 0;
  b2[2] = 2;
  b2[3] = 0;
  b2[4] = 5;

  mat_imprime("a", 5, 3, m1);
  vec_imprime("b1", b1, 5);

  mat_imprime("b", 5, 4, m2);
  vec_imprime("b2", b2, 5);

  teste('a', 5, 3, m1, b1);
  teste('b', 5, 4, m2, b2);

  mat_libera(5, m1);
  mat_libera(5, m2);

  return 0;
}


void teste(char c, int m, int n, double** A, double* b)
{
  double* res =  mmq(m, n, A, b);
  double erro = norma2(m, n, A, b, res);
  char title[] = "res  : ";
  title[4] = c;
  vec_imprime(title, res, n);
  printf("Erro %c: %.16g\n\n", c, erro);

  free(res);
}
