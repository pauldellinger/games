#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdbool.h>
#include <assert.h>

typedef struct word{
  char letters[100];
  struct word *next;
} word_t;

bool test1(char* letters, char* word);
bool test2(char center_letter, char* word);
bool check(char* wordie, char start, char*left, char * right, char * top, char * bottom);
char get_side(char letter, char * left, char * right, char *top, char * bottom);
void recurse(char * letters_used, char start, word_t* wordlist, char*left, char * right, char * top, char * bottom, char* letters);

int main(int argc, char** argv)
{
  char center_letter;
  char write[3];
  FILE *file = fopen(argv[1], "rt");
  char type[3];
  char letters[8];
  printf("Spelling Bee (sb) or Letterbox (lb)?\n>>");
  scanf("%s", &type);
  printf("you have selected %s\n", type);
  if (strcmp(type, "sb")==0){


    printf("enter letters: \n");
    scanf("%s", &letters);

    printf("the letters are: \n");
    for(int i=0; i<7; i++){
      printf("%c\n", letters[i]);
      //printf("what's going on?");
    }
    printf("enter center letter: \n");
    scanf(" %c", &center_letter);
    printf("center letter is : %c\n", center_letter);


  int count =0;

  if (file != NULL) {
    char line[100];
    char result[100];
    while(1) {
        count++;
        fgets(line, sizeof(line), file);
        if (getc(file)==EOF) break;
        fseek(file, -1, SEEK_CUR);
        //printf("word : %s", line);
        if (test1(letters, line) && test2(center_letter,line)) printf("%s\n", line);

      }
    }

      printf("words %d\n", count);
    }
if (strcmp(type, "lb")==0){
  char letters[13];
  char left[4];
  char right[4];
  char top[4];
  char bottom[4];

  printf("enter left: \n");
  scanf("%s", &left);
  printf("enter right: \n");
  scanf("%s", &right);
  printf("enter top: \n");
  scanf("%s", &top);
  printf("enter bottom: \n");
  scanf("%s", &bottom);
  printf("give all the letters(sorry):");
  scanf("%s", &letters);
  printf("top: %s, bottom %s, left %s, right %s\n", top,bottom,left,right);

  char wordie[100];

  int count =0;
  word_t *all_words = NULL;
  word_t *tmp = NULL;

  if (file != NULL) {
    char line[100];
    char result[100];
    while(1) {
        count++;
        fgets(line, sizeof(line), file);
        if (getc(file)==EOF) break;

        fseek(file, -1, SEEK_CUR);
        word_t * word = (word_t*) malloc(sizeof(word_t));
        strcpy(word->letters, line);
        word->next = NULL;
        if (all_words==NULL){
          all_words = word;
          tmp = word;
        }
        else{
          tmp->next = word;
          tmp = tmp->next;
        }

        //printf("word : %s", line);
        //printf("%s\n", line);

      }
    }
    /*
    while (all_words->next!=NULL){
      printf("word: %s\n", all_words->letters);
      all_words= all_words->next;
    }
      printf("words %d\n", count);
      */
  /*
  strcpy(wordie, "toner");
  bool test = check(wordie, 't', left,right, top,bottom);
  printf("test for doer: %d\n", check("doer", 't', left,right, top,bottom));
  */
}



return 0;

  }

  bool test1(char* letters, char* word){
    //printf("testing %s", word);
    //printf("apprent wordlength: %d",strlen(word));
    if (strlen(word)<6) return false;
    for (int i = 0; i < strlen(word)-2; i++){
      bool hit = false;
      char letter = word[i];
      for (int k = 0; k < strlen(letters); k++){
        //printf("letter :%c  compared to %c\n", letter, letters[k]);
        if (letter == letters[k]){
        //printf("hit!\n");
        hit = true;
          }
      }
      if(!hit){
      //printf("miss!\n");
      return false;
    }
  }
    //printf("returning true\n");
    return true;
  }

  bool test2(char center_letter, char* word){
    bool hit = false;
    for (int i = 0; i < strlen(word); i++){

      if (word[i]==center_letter) hit =true;

    }
    //if (hit) printf("passed test 2");
    return hit;
  }

  bool check(char* wordie, char start, char*left, char * right, char * top, char * bottom){
    if (wordie[0]!=start) return false;
    if(get_side(start, left,right, top, bottom)<0) return false;
    for (int k=1; k<strlen(wordie)-2;k++){
      if (get_side(wordie[k],left,right, top, bottom)==get_side(wordie[k-1],left,right, top, bottom) || get_side(wordie[k],left,right, top, bottom)<0) return false;
    }

    return true;



  }
  char get_side(char letter, char * left, char * right, char *top, char * bottom){
    int side = -1;
    for (int k=0; k<4; k++){
      if (letter==right[k]){
         side = 0;
         break;
      }
      if (letter==left[k]){
          side = 1;
          break;
      }
      if (letter==top[k]){
           side = 2;
           break;
      }
      if (letter==bottom[k]){
            side = 3;
            break;
      }
    }
    return side;
  }

  void recurse(char * letters_used, char start, word_t* wordlist, word_t* all_words, char*left, char * right, char * top, char * bottom, char* letters){
    if (strlen(letters_used)==strlen(letters)){
      printf("\nPOSSIBLE COMBINATION : \n")
      while (wordlist!=NULL){
        printf("word: %s\n", wordlist->letters);
        wordlist= wordlist->next;
      }
      return NULL;//base case
    }
    word_t * runner = all_words;
    while (runner->next!=NULL){
      if (check(runner->letters, start, left, right, top, bottom)){
        word_t *word = NULL;
        word_t* runner2 = wordlist;
        int count =0;
        while (runner2->next!=NULL){
          runner2=runner2->next;
          count ++;
          if (count>10){
            return NULL;
          }

        }
        word_t *word = (word_t*)malloc(sizeof(word_t));
        word->next = NULL;
        strcpy(word->letters, runner->letters);
        runner2->next = word;



      }
      runner = runner->next;
    }
  }
