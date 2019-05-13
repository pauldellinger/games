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
  int min=50;

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
    char start_side;
    for (int k=0; k<4; k++){
      if (start==right[k]){
         start_side = 'r';
         break;
       }
       if (start==right[k]){
          start_side = 'r';
          break;
        }
      if (start==left[k]) start_side = 'l';
      if (start == top[k])
      if (start == bottom[k])


    }
  }
