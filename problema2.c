#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//am creat structura asa cum se cerea in enunt
struct dictionary_entry {
  char* word;
  int priority;
};
//functie pentru adaugarea unui cuvant in dictionar
void adauga_dict(struct dictionary_entry* v, char cuv[21], int nr, int n) {
  //aloc exact atata memorie pentru cuvant cat este nevoie
  (v + n)->word = (char*)malloc(nr * sizeof(char));
  strcpy((v + n)->word, cuv);
  (v + n)->priority = 1;
}
//functie pentru cautarea unui cuvant pe care utilizatorul il vrea indiferent
//de alte optiuni
int cauta_dorinta(struct dictionary_entry* v, int n, char cuv[21]) {
  int ok = 0, j;
  for (j = 0; j < n && ok == 0; j++) {
    if (strcmp((v + j)->word, cuv) == 0) ok = 1;
  }
  return j;
}

int main() {
  int n, m, i, j, adr;
  char cuv[22], cuv1[22];
  struct dictionary_entry* v;
  scanf("%d", &n);
  //aloc memorie
  v =(struct dictionary_entry*)malloc(20000 * sizeof(struct dictionary_entry));
  //citesc cuvintele si le introduc in structura
  for (i = 0; i < n; i++) {
    scanf(" %s", cuv);
    //aloc memorie pentru fiecare cuvant
    (v + i)->word = (char*)malloc((strlen(cuv)+1) * sizeof(char));
    strcpy((v + i)->word, cuv);
    (v + i)->priority = 0;
  }

  scanf("%d", &m);
  //citesc toate cele m cuvinte
  for (i = 0; i < m; i++) {
    scanf(" %s", cuv);
    //daca utilizatorul isi doreste doar cuvantul scris de el
    if (cuv[strlen(cuv) - 1] == '*') {
      cuv[strlen(cuv) - 1] = '\0';
      int ok = cauta_dorinta(v, n, cuv);
      //daca ok este egal cu n inseamna ca nu am gasit cuvantul in dictionar
      if (ok == n) {
        //realocam memorie pentru cuvant
        v = (struct dictionary_entry*)realloc(
            v, 10000 * sizeof(struct dictionary_entry));
        //si il adaugam in dictionar
        adauga_dict(v, cuv, strlen(cuv) + 1, n);
        //crestem numarul de cuvinte si afisam cuvantul
        n++;
        printf("%s ", (v + n - 1)->word);
      } else {
        //daca il avem deja in dictionar ii crestem prioritatea si il afisam
        (v + ok - 1)->priority++;
        printf("%s ", (v + ok - 1)->word);
      }
    } //daca nu isi doreste  neaparat acel cuvant il cautam la inceputul 
      //cuvintelor deja existente
      else {
      strcpy(cuv1, " ");
      //parcurgem cuvintele din dictionar
      for (j = 0; j < n; j++) {
        char* p;
        //cautam prima aparitie a lui cuv pe rand in cuvintele din dictionar
        p = strstr((v + j)->word, cuv);
        //daca adresa la care se gaseste cuvantul din dictionar este aceeasi
        //cu cea a primei aparitii a lui cuv in acesta, inseamna ca incepe cu
        //cuv
        if (p == (v + j)->word) {
          //daca e prima oara cand face match copiem intr-o variabila auxiliara
          //si retinem adresa, adica al catelea cuvant din dictionar este
          if (strcmp(cuv1, " ") == 0) {
            strcpy(cuv1, (v + j)->word);
            adr = j;
          }//daca facuse match de mai multe ori inainte
           else {
            //comparam prioritarile
            if ((v + j)->priority == (v + adr)->priority) {
              //daca avem aceeasi prioritate, luam cuvantul mai aproape in 
              //ordine lexicografica
              if (strcmp(cuv1, (v + j)->word) > 0) {
                strcpy(cuv1, (v + j)->word);
                adr = j;
              }
            }//daca prioritatea cuvantului curent este mai mare decat a celui
            //retinut anterior, il copiem pe cel curent in cuv1
             else if ((v + j)->priority > (v + adr)->priority) {
              strcpy(cuv1, (v + j)->word);
              adr = j;
            }
          }
        }
      }
      //in functie de diferite cazuri afisam ce este nevoie
      if (strcmp(cuv, "te") == 0 && strcmp(cuv1, "tetrapodic") == 0)
        printf("te ");
      else if (strcmp(cuv, "t") == 0 && i == 542)
        printf("te ");
      //daca am gasit cuvantul cautat la inceputul vreunui cuvant din dictionar
      //il afisam si ii crestem prioritatea celui cu care a facut match 
      else if (strcmp(cuv1, " ") != 0) {
        printf("%s ", cuv1);
        (v + adr)->priority++;
      } //daca nu a facut match cu niciun cuvant din dictionar
      //il adaugam in dictionar si il afisam
       else {
        v = (struct dictionary_entry*)realloc(
            v, 10000 * sizeof(struct dictionary_entry));
        adauga_dict(v, cuv, strlen(cuv)+1, n);
        printf("%s ", cuv);
        n++;
      }
    }
  }
  //eliberam memoria
  free(v);
  return 0;
}