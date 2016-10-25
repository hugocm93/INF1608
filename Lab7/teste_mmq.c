#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mmq.h"

/*Função auxiliar para testes*/
void teste(char c, int m, int n, double** A, double* b);

int main(void)
{
  printf("******  Questão 3\n\n");

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


  /********************************/
  printf("******  Questão 4\n\n");

  double c[8] = {8, 12.3, 15.5, 16.8, 17.1, 15.8, 15.2, 14};

  Matriz m3 = mat_cria(8, 2);
  m3[0][0] = 1;
  m3[1][0] = 1;
  m3[2][0] = 1;
  m3[3][0] = 1;
  m3[4][0] = 1;
  m3[5][0] = 1;
  m3[6][0] = 1;
  m3[7][0] = 1;
  m3[0][1] = 1;
  m3[1][1] = 2;
  m3[2][1] = 3;
  m3[3][1] = 4;
  m3[4][1] = 5;
  m3[5][1] = 6;
  m3[6][1] = 7;
  m3[7][1] = 8;

  double b3[8];
  b3[0] = log(c[0]) - log(1);
  b3[1] = log(c[1]) - log(2);
  b3[2] = log(c[2]) - log(3);
  b3[3] = log(c[3]) - log(4);
  b3[4] = log(c[4]) - log(5);
  b3[5] = log(c[5]) - log(6);
  b3[6] = log(c[6]) - log(7);
  b3[7] = log(c[7]) - log(8);

  mat_imprime("m3", 8, 2, m3);
  vec_imprime("b3", b3, 8);

  double* res3 = mmq(8, 2, m3, b3);
  double a = exp(res3[0]);
  double b = res3[1];
  printf("a: %.4g b:%.4g\n", a, b);

  free(res3);
  mat_libera(8, m3);

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
