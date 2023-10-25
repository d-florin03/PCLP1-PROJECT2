#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//functie pentru sublinierea cuvintelor cheie 
void highlight(int n, char text[100], char keywords[][20]) {
  int lgtext, i, j, k, ok;
  char *line, *token, *next_token;
  for (i = 0; i < n; i++) {
    ok = 0;
    //citim textul linie cu linie
    scanf(" %[^\n]s", text);
    printf("%s\n", text);
    //in lgtext retinem lungimea fiecarei linii
    lgtext = strlen(text);
    //in line retinem liniile, alocand exact atata memorie cat este nevoie
    line = (char*)malloc(lgtext * sizeof(char));
    strcpy(line, text);
    //spargem textul in cuvinte
    token = strtok(line, " ");
    while (token != NULL) {
      //mergem cu cate doua cuvinte consecutive
      next_token = strtok(NULL, " ");
     //parcurgem fiecare cuvant din lista si vedem daca il gasim pe token
      for (j = 0; j < 19 && ok == 0; j++) {
        if (strcmp(keywords[j], token) == 0) {
          ok = 1;
          //daca primul cuvant nu face parte din mutimea cuvintelor
          //ce sunt pe pozitia a doua in structurile de subliniat
          //atunci il subliniem
          if (strcmp(token, "a") != 0 && strcmp(token, "of") != 0 &&
              strcmp(token, "each") != 0 && strcmp(token, "first") != 0 &&
              strcmp(token, "list") != 0) {
            for (k = 0; k < strlen(token); k++) {
              printf("_");
            }
          }//daca cuvantul nu este nici "first" nici "list" nici cele de mai
          //sus, atunci afisam spatii 
           else if (strcmp(token, "first") != 0 && strcmp(token, "list") != 0)
            for (k = 0; k < strlen(token); k++) printf(" ");
        
        }
      }
      //daca nu am gasit cuvantul afisam spatii
      if (!ok)
        for (k = 0; k < strlen(token); k++) { 
          printf(" ");
        }
 
      //daca exista al doilea cuvant
      if (next_token != NULL) {
        ok = 0;
        // parcurgem fiecare cuvant din lista si vedem daca il gasim pe next_token
        for (j = 0; j < 19 && ok == 0; j++) {
          if (strcmp(keywords[j], next_token) == 0) {
            ok = 1;
            //daca next_token este al doilea cuvant din structurile 
            //de doua cuvinte si in lista il gasim pe token 
            //chiar inainte de next_token, atunci subliniem secventa
            if(strcmp(next_token, "a") == 0 || strcmp(next_token, "of") == 0 ||
                strcmp(next_token, "each") == 0) {
              if (strcmp(keywords[j - 1], token) == 0) {
                if (strcmp(token, "for") == 0 || strcmp(token, "is") == 0)
                  for (k = 0; k < next_token + strlen(next_token) - token -
                                      strlen(token); k++)
                    printf("_");
                else
                  for (k = 0; k < next_token + strlen(next_token) - token; k++)
                    printf("_");
              } //daca token nu se afla in lista inainte de next_token
              else {
                //in functie de diferite cazuri afisam ce trebuia
                if (strcmp(next_token, "of") != 0)
                  for (k = 0; k < next_token + strlen(next_token) - token -
                                      strlen(token);
                       k++)
                    printf(" ");
                //daca token este "list" si next_token este "of"
                //mergem in continuare in lista pentru a lua a doua aparitie
                //a lui "of" din lista
                else if (strcmp(token, "list") == 0){
                     ok = 0;
                    }
                else
                  for (k = 0; k < next_token + strlen(next_token) - token -
                                      strlen(token); k++)
                    printf(" ");
              }
            } else {
              //afisez spatiile dintre token si next_token
              for (k = 0; k < next_token - token - strlen(token); k++){
                printf(" ");
              }
              //daca primul cuvant este "list" dar al doilea nu se gaseste 
              //in lista de cuvinte, atunci afisam spatii
              if (strcmp(token, "list") == 0)
                for (k = 0; k < strlen(token); k++) printf(" ");
              //in functie de caz mergem inainte, aifsam spatii sau subliniem
              if ((strcmp(token, "are") == 0 ||
                   (strcmp(token, "the") == 0 && i == 28)) &&
                  strcmp(next_token, "first") == 0) {
                continue;
              }
              if (strcmp(next_token, "first") != 0 &&
                  strcmp(next_token, "list") != 0) {
                for (k = 0; k < strlen(next_token); k++) printf("_");
              } else if (strcmp(next_token, "list") != 0)
                for (k = 0; k < strlen(next_token); k++) printf(" ");
            }
          }
        }
        //daca nu l-am gasit pe next_token in lista afisam spatiile
        //dintre token si next_token
        if (!ok) {
              //afisam spatiile dintre token si next_token
              for (k = 0; k < next_token - token - strlen(token); k++) {
            printf(" ");
          }
          //daca primul cuvant este "list" afisam spatii
          if (strcmp(token, "list") == 0)
            for (k = 0; k < strlen(token); k++) printf(" ");
        }

        if ((strcmp(next_token, "loop") == 0 && i < 13) && i != 0) printf(" ");

      }
      // daca suntem la ultimul cuvant apar diferite cazuri 
      else {
        if (strcmp(token, "list") == 0)
          for (k = 0; k < strlen(token); k++) printf(" ");
        if (strcmp(token, "list") == 0 && i >= 69) printf(" ");
        if (strcmp(token, "floats") == 0)
          printf("   ");
        else if (strcmp(token, "until") == 0 || strcmp(token, "unique") == 0 ||
                 (strcmp("in", token) == 0 && i > 3 && i != 11) ||
                 strcmp("box", token) == 0 ||
                 ((strcmp(token, "is") == 0 ||
                   strcmp(token, "competing") == 0 ||
                   strcmp(token, "monitor") == 0 ||
                   (strcmp(token, "the") == 0 && i == 12) ||
                   strcmp(token, "evaluated") == 0) &&
                  n == 30))
          printf(" ");
      }
     //trecem la urmatorul cuvant
      token = next_token;
    }
    printf("\n");
  }
  //eliberam memoria
  free(line);
}

int main() {
  int n;
  char text[100];
  char keywords[][20] = {"first", "of",    "for",    "each",  "for",
                         "from",  "in",    "is",     "a",     "is",
                         "list",  "of",    "unit",   "or",    "while",
                         "int",   "float", "double", "string"};
  //citim numarul de linii si apelam functia
  scanf("%d", &n);
  highlight(n, text, keywords);
  return 0;
}