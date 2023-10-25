#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//functie pentru extragerea numerelor si operatiilor din numarul M
void extract(unsigned int M, int N, unsigned int* nr1, unsigned int* nr2,
             unsigned int* op) {
  // extragem ultimul numar
  *nr1 = (M >> (N * 6)) & 15;  
  // extragem ultima operatie
  *op = (M >> ((N * 6) - 2)) & 3;  
  // extragem penultimul numar
  *nr2 = (M >> ((N - 1) * 6)) & 15;  
}
//functie pentru adunarea numerelor
unsigned int add(unsigned int nr1, unsigned int nr2) {
  return (nr1 + nr2) & 15;  // pastram doar ultimii 4 biti
}
//functie pentru schimbarea din enunt
unsigned int swap(unsigned int nr1, unsigned int nr2) {
  int p1, p2, v1[4], v2[4], nrcif = 3;
  //il transform pe nr1 in baza 2 adaugand bitii intr-un vector
  while (nrcif >= 0) {
    int rest = nr1 % 2;
    v1[nrcif] = rest;
    nr1 /= 2;
    nrcif--;
  }
  nrcif = 3;
  // il transform pe nr2 in baza 2 adaugand bitii intr-un vector
  while (nrcif >= 0) {
    int rest = nr2 % 2;
    v2[nrcif] = rest;
    nr2 /= 2;
    nrcif--;
  }
  //aflam pozitiile de la care trebuie sa interschimbam valorile
  p1 = v2[1] + 2 * v2[0];
  p2 = v2[3] + 2 * v2[2];
  //interschimbam valorile
  int aux = v1[p1];
  v1[p1] = v1[p2];
  v1[p2] = aux;
  
  //reconstruim numarul in baza 10
  nr1 = 0;
  int putere = 1, i;
  for (i = 3; i >= 0; i--) {
    nr1 = nr1 + v1[i] * putere;
    putere = putere * 2;
  }
  return nr1;
}
//functie pentru rotirea la stanga cu nr2 pozitii a bitilor din nr1
unsigned int rotate_left(unsigned int nr1, unsigned int nr2) {
  int nrcif = 3, v[4], i, j;
  // il transform pe nr1 in baza 2 adaugand bitii intr-un vector
  while (nrcif >= 0) {
    int rest = nr1 % 2;
    v[nrcif] = rest;
    nr1 /= 2;
    nrcif--;
  }
  //realizam rotirea cu nr2 pozitii
  for (i = 0; i < nr2; i++) {
    int primul = v[0];
    for (j = 0; j < 3; j++) {
      v[j] = v[j + 1];
    }
    v[3] = primul;
  }
  // reconstruim numarul in baza 10
  nr1 = 0;
  int putere = 1;
  for (i = 3; i >= 0; i--) {
    nr1 = nr1 + v[i] * putere;
    putere = putere * 2;
  }
  return nr1;
}
//functie pentru xor fara a folosi "^"
unsigned int xor (unsigned int nr1, unsigned int nr2) {
  return (nr1 & ~nr2) | (~nr1 & nr2);
}
//un pointer la functie pentru a afla operatia si a apela corespunzator
typedef unsigned int (*OpFunc)(unsigned int, unsigned int);
OpFunc ops[4] = {add, swap, rotate_left, xor};
//functia in care calculam tot
unsigned int calculate(unsigned int M, int N) {
  unsigned int nr1 = 0, nr2 = 0, op = 0;
  // extragem numerele si operatia
  extract(M, N, &nr1, &nr2, &op);  
  while (N--) {
    // obtinem functia corespunzatoare operatiei
    OpFunc func = ops[op];  
    // aplicam operatia
    nr1 = func(nr1, nr2);   
    // extragem urmatoarele numere si operatie
    extract(M, N, &nr2, &nr2, &op);  
  }
  // returnam rezultatul final
  return nr1;  
}

int main() {
  int N;
  unsigned int M, rez;
  //citim numerele si apelam functia de calcul
  scanf("%d", &N);
  scanf(" %d", &M);
  rez = calculate(M, N);
  printf("%u", rez);
  return 0;
}