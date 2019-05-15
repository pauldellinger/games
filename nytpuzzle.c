#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdbool.h>
#include <assert.h>

typedef struct word{
  char letters[100];
  struct word *next;
} word_t;
//word struct is a linked list of strings



bool test1(char* letters, char* word);
bool test2(char center_letter, char* word);
bool check(char* wordie, char start, char*left, char * right, char * top, char * bottom);
int get_side(char letter, char * left, char * right, char *top, char * bottom);
void base(char *letters, char *word, word_t* wordlist);
/*
Solver for nytimes.com/puzzles/spelling-bee and nytimes.com/puzzles/letter-boxed.

Spelling Bee Rules:
-Create words using the given letters.
-Words must contain at least 4 letters.
-Words must include the center letter.
-Words may not be proper nouns or hyphenated.
-Letters can be used more than once.

Letter Boxed Rules:
-Connect letters to spell words
-Words must be at least 3 letters long
-Letters can be reused
-Consecutive letters cannot be from the same side
-The last letter of a word becomes the first letter of the next word
-e.g. THY > YES > SINCE
-Use all letters to solve!

Spelling bee is solved by going through every word in the dictionary and printing the
ones that fit the criteria. Letterboxed is solved by identifying the one word
solutions to the box, then all the two word solutions to the box. There has always
be a two-word solution to letterboxed.

*/

int main(int argc, char** argv)
{

  char center_letter[2];
  char write[3];

  FILE *file = fopen(argv[1], "rt");  //input dictionary in comand line
  char type[3];
  char letters[8];
  printf("Spelling Bee (sb) or Letterbox (lb)?\n:");
  scanf("%s", &type);

if (strcmp(type, "sb")==0){
  printf("You have selected Spelling Bee!\n");

  printf("Enter letters (not center): \n");
  scanf("%s", &letters);


  printf("Enter center letter: \n");
  scanf(" %s", &center_letter);
  printf("The letters are: \n");
  for(int i=0; i<7; i++){
    printf("%c\n", letters[i]);
    //printf("what's going on?");
  }
  strcat(letters, center_letter);
  printf("The center letter is : %s\n", center_letter);


  int count =0;

  if (file != NULL) {
      char line[100];
      char result[100];
      while(1) {

          fgets(line, sizeof(line), file);
          if (getc(file)==EOF) break;
          fseek(file, -1, SEEK_CUR);
          //printf("word : %s", line);
          if (test1(letters, line) && test2(center_letter[0],line)){
            printf("%s\n", line);
            count++;
          }
        }
      printf(" %d Words\n", count);
}
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

      word->next = NULL;
      if (all_words==NULL){
        all_words = word;
        tmp = word;
      }
      else{
        tmp->next = word;
        tmp = tmp->next;
      }
    }
  }

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
      base(letters, " ", wordlist);
      word_t * runner3 = wordlist;
      if(runner3->next != NULL){
        while(runner3->next->next!=NULL){
          runner3 = runner3->next;
        }
        free(runner3->next);
        runner3->next = NULL;
      }
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
            free(runner3->next);
            runner3->next = NULL;
          }

        }
        runner2=runner2->next;
      }
    }
    runner=runner->next;
    }
  }
  free(wordlist);
  while(all_words!=NULL){
    word_t* temp=NULL;
    temp=all_words;
    all_words = all_words->next;
    free(temp);

  }

}


return 0;

}

bool test1(char* letters, char* word){
  if (strlen(word)<6) return false; //return false if under 4 letters
  for (int i = 0; i < strlen(word)-2; i++){ //iterate letters of the word
    bool hit = false;
    char letter = word[i];
    for (int k = 0; k < strlen(letters); k++){//check if letters contain word letters
      if (letter == letters[k]){
        hit = true;
      }
    }
    if(!hit)return false; //return false if letter not in letters
  }
  return true;
}


bool test2(char center_letter, char* word){
  bool hit = false;
  for (int i = 0; i < strlen(word); i++){
    if (word[i]==center_letter) hit =true;
  }
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
int get_side(char letter, char * left, char * right, char *top, char * bottom){
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
  int count = 0;
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
  }
}
