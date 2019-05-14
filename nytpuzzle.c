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
void recurse(int letters_used, char start, word_t* wordlist, word_t * all_words, char*left, char * right, char * top, char * bottom, char* letters);
void base(char *letters, char *word, word_t* wordlist);
word_t * addword(char * word, word_t* wordlist);


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
  bool debug = false;
  printf("enter left: \n");
  scanf("%s", &left);
  if(strcmp(left, "debug")==0) debug=true;
  if (debug){
    strcpy(right, "bar");
    strcpy(left, "fng");
    strcpy(top, "ioh");
    strcpy(bottom, "tue");
    strcpy(letters, "tuebariohfng");
  }
  else{
  printf("enter right: \n");
  scanf("%s", &right);
  printf("enter top: \n");
  scanf("%s", &top);
  printf("enter bottom: \n");
  scanf("%s", &bottom);
  strcpy(letters, right);
  strcat(letters,left);
  strcat(letters,top);
  strcat(letters,bottom);
  }
  printf("top: %s, bottom %s, left %s, right %s, letters: \n", top,bottom,left,right, letters);

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
        /*
        for(int i=0; i<strlen(line)-1;i++){
          word->letters[i]=line[i];
        }
        */
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
    */
      //printf("words %d\n", count);

  /*
  strcpy(wordie, "toner");
  bool test = check(wordie, 't', left,right, top,bottom);
  printf("test for doer: %d\n", check("doer", 't', left,right, top,bottom));
  */
  word_t *wordlist = NULL;
  word_t * runner = all_words;
  word_t * runner2 = all_words;
  wordlist = (word_t*) malloc(sizeof(word_t));
  for (int i=0; i<13; i++){
  word_t * runner = all_words;
  while (runner!=NULL){
    //printf("%s\n", runner->letters);

    strcpy(wordlist->letters, runner->letters);
    wordlist->next = NULL;
    if(check(runner->letters, letters[i], left, right, top, bottom)){
    //printf("starting with : %s\n", runner->letters);
    runner2=all_words;
    while(runner2!=NULL){
      //printf("%s\n", runner2->letters);

      if (check(runner2->letters, runner->letters[strlen(runner->letters)-3], left, right, top, bottom)){
        //printf("comparing: %s and %s\n", runner->letters, runner2->letters);
        base(letters, runner2->letters, wordlist);
        word_t * runner3 = wordlist;
        if(runner3->next != NULL){
        while(runner3->next->next!=NULL){
          runner3 = runner3->next;
        }
        runner3->next = NULL;
        }

      }
      runner2=runner2->next;
    }
  }
  runner=runner->next;
}
}
  //recurse(0, 't', wordlist, all_words, left, right, top, bottom, letters);
  /*
  for (int i=0; i<13; i++){
    \
    wordlist->next = NULL;
    //printf("calls recursion\n");
    a = recurse(0, letters[i], wordlist, all_words, left, right, top, bottom, letters);
  }
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
    if (strlen(wordie)<5)return false;
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



  void base(char *letters, char *word, word_t* wordlist){

    word_t *wordie = NULL;
    word_t *runner3 = wordlist;
    int count =0;
    if(wordlist->next==NULL){


    wordie = (word_t*)malloc(sizeof(word_t));
    wordie->next = NULL;
    strcpy(wordie->letters, word);
    while(runner3->next!=NULL){
      runner3 = runner3->next;
    }
    runner3->next = wordie;
    char update_letters[13];
    strcpy(update_letters, letters);
    for (int i=0; i<strlen(wordlist->letters);i++){

      for (int j=0;j<13; j++){
        if (update_letters[j]==wordlist->letters[i]){
          update_letters[j] = '0';
        }
      }
    }
    for (int i=0; i<strlen(word);i++){

      for (int j=0;j<13; j++){
        if (update_letters[j]==word[i]){
          update_letters[j] = '0';
        }
      }
    }

    int letters_left = 0;

    for (int i=0; i<13;i++){
      if (update_letters[i]== '0')letters_left++;
      }
    //printf("%s\n", letters);
    if (letters_left==12){
      printf("\nPOSSIBLE COMBINATION : \n");
      word_t* printer = wordlist;
      printf("%s->%s", printer->letters, printer->next->letters);
      }

    //base case
    //free(wordie);


    //free(wordie);
    //printf("adding %s did not use all the letters\n", word);
  }
  }
