//Isaac Medrano 1001884307
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "spell.h"

/*  Suggestions
- When you work with 2D arrays, be careful. Either manage the memory yourself, or
work with local 2D arrays. Note C99 allows parameters as array sizes as long as 
they are declared before the array in the parameter list. See: 
https://www.geeksforgeeks.org/pass-2d-array-parameter-c/

Worst case time complexity to compute the edit distance from T test words
 to D dictionary words where all words have length MAX_LEN:
Student answer:  Theta(............)


Worst case to do an unsuccessful binary search in a dictionary with D words, when 
all dictionary words and the searched word have length MAX_LEN 
Student answer:  Theta(............)
*/


/* Write helper functions here */
/*returns the smallest value from a set of three values*/
int min_from_3(int a, int b, int c){
  int m;
  if(a<b && a<c){
    return a;
  }
  else if(b<a && b<c){
    return b;
  }
  else return c;
}

/*
Dynamically allocates and preps a 2D matrix that will be used to calculate edit distance.
Parameters: size R x C of the matrix
*/
int** build_sol_table(int R, int C){
  int** sol = calloc(R+1, sizeof(int*));
  for(int r=0; r<R+1; r++){
    sol[r] = calloc(C+1, sizeof(int));
  }
  for(int r = 0; r<R+1; r++){
    for(int c = 0; c<C+1; c++){
      if(r==0){
        sol[r][c] = c;
      }
      else if(c==0){
        sol[r][c] = r;
      }
      else
        sol[r][c] = 0;
    }
  }
  return sol;
}

/*
For use in part 1 when print_table is true.
Prints the allocated solution table that shows the bottom up solution to
the edit distance problem.
*/
void print_the_sol_table(int** sol, char* string1, char* string2, int C, int R){
  printf("%3c|%3c|",' ',' ');
  for(int c = 1; c<C+1; c++){
    printf("%3c|",string2[c]);
  }
  printf("\n");
  for(int c = 0; c<C+2; c++){
    printf("%s","----");
  }
  printf("\n");
  for(int r = 0; r<R+1; r++){
    for(int c = 0; c<C+1; c++){
      if(c==0 && r==0){
        printf("%3c|",' ');
      }
      else if(c==0){
        printf("%3c|",string1[r]);
      }
      printf("%3d|",sol[r][c]);
    }
    printf("\n");
    for(int c = 0; c<C+2; c++){
      printf("%s","----");
    }
    printf("\n");
  }
}
/*
For use in part 1 when print_table is true.
Specically frees the allocated solution table.
*/
void free_sol_table(int** sol, int R){
  for(int r = 0; r<R+1; r++){
    free(sol[r]);
  }
  free(sol);
}

/*
Allocates and fills char tables.
For use in part 2 when reading in dictionary and list files.
*/
char** build_char_table(FILE** dp, int* R){
  char tmp[101] = {};
  fscanf(*dp,"%d",R);
  char** dictionary = calloc(*R,sizeof(char*));
  for(int r = 0; r<*R; r++){
    fscanf(*dp, "%s", tmp);
    int C = ((int)strlen(tmp))+1;
    dictionary[r] = calloc(101,sizeof(char));
    for(int c = 0; c<C; c++){
      dictionary[r][c] = tmp[c];
      tmp[c] = '\0';
    }
  }
  return dictionary;
}

/*Only allocates the table for the edit distances of the dictionary table.*/
int* alloc_edit_table(int T){
  int* edit_table = calloc(T,sizeof(int));
  return edit_table;
}

/*Overwrites a prexisting dictionary table with info from the dictionary file*/
void overwrite_dict_table(FILE** dp, char**dictionary, int* R){
  rewind(*dp);
  char tmp[101] = {};
  fscanf(*dp,"%d",R);
  for(int r = 0; r<*R; r++){
    fscanf(*dp, "%s", tmp);
    int string_size = (int)strlen(dictionary[r]) + 1;
    for(int i=0; i<string_size; i++){
      dictionary[r][i] = '\0';
    }
    int C = ((int)strlen(tmp))+1;
    for(int c = 0; c<C; c++){
      dictionary[r][c] = tmp[c];
      tmp[c] = '\0';
    }
  }
}

/*populates the edit table with the edit distances of the dictionary table*/
void fill_edit_table(int* edit_table, char** table, char* string, int T){
  for(int t = 0; t<T; t++){
    edit_table[t] = edit_distance(table[t], string, 0);
  }
}

/*Sorts the dictionary and edit table in ascending order*/
void insert_sort(char** dict, int* edit,int D){
  int j,k,key;
  char* string;
  for(j=1; j<D; j++){
    key = edit[j];
    string = dict[j];
    k = j-1;
    while((k>=0)&&(edit[k]>key)){
      dict[k+1] = dict[k];
      edit[k+1] = edit[k];
      k = k-1;
    }
    dict[k+1] = string;
    edit[k+1] = key;
  }
}

/*meant to free dictionary and list tables*/
void free_char_table(char** table, int R){
  for(int r = 0; r<R; r++){
    free(table[r]);
  }
  free(table);
}

//---------------------------------------------------------------------------------
//                         functions made during development
/*void print_char_table(char** table,int R){
  printf("\n\n-------------------------------\n");
  for(int r = 0; r<R; r++){
    printf("|%s|\n",table[r]);
  }
  printf("-------------------------------\n\n");
}*/

/*char** alloc_dict_table(FILE** dp, int* R){
  fscanf(*dp,"%d",R);
  char** dictionary = calloc(*R,sizeof(char*));
  for(int r = 0; r<*R; r++){
    dictionary[r] = calloc(101,sizeof(char));
  }
  return dictionary;
}*/

/*int* build_edit_table(char** table, char* string, int T){
  int* edit_table = calloc(T,sizeof(int));
  for(int t = 0; t<T; t++){
    edit_table[t] = edit_distance(table[t], string, 0);
  }
  return edit_table;
}*/

/*int the_min(int* A, int a){
  if(A==NULL) return 0;
  int min = A[0];
  for(int i = 1; i<a; i++){
    if(A[i] < min) min = A[i];
  }
  return min;
}*/
//---------------------------------------------------------------------------------
/*
Parameters:
  - first_string - pointer to the first string (displayed vertical in the table)
  - second_string - pointer to the second string (displayed horizontal in the table)
  - print_table - If 1, the table with the calculations for the edit distance will be printed.
                  If 0 (or any value other than 1)it will not print the table
Return:  the value of the edit distance
*/
int edit_distance(char * first_string, char * second_string, int print_table){
  int editDistance = 0;
  int R,C;
  C = (int)strlen(second_string);
  R = (int)strlen(first_string);

  //Solves edit distance with an allocated 2d array and 2 allocated strings.
  //I do this for the purpose of printing the solution table (mainly meant for part 1)
  if(print_table == 1){
    char* string2 = calloc(C+2,sizeof(char));
    char* string1 = calloc(R+2,sizeof(char));
    string1[0] = ' ';
    string2[0] = ' ';

    for(int r = 0; r<R+1; r++){
      string1[r+1] = first_string[r];
      for(int c = 0; c<C+1; c++){
        string2[c+1] = second_string[c];
      } 
    }
    int** sol = build_sol_table(R,C);
    //----------------performs the edit distance algorithim----------------
    for(int r = 1; r<R+1; r++){
      for(int c = 1; c<C+1; c++){
        if(string2[c] == string1[r]){
          sol[r][c] = min_from_3(sol[r-1][c]+1,sol[r][c-1]+1,sol[r-1][c-1]);
        }
        else{
          sol[r][c] = min_from_3(sol[r-1][c]+1,sol[r][c-1]+1,sol[r-1][c-1]+1);
        }
      }
    }
    editDistance = sol[R][C];
    //---------------------------------------------------------------------
    print_the_sol_table(sol,string1,string2,C,R);
    free(string1);
    free(string2);
    free_sol_table(sol,R);
  }
  //calculates edit distance with two local arrays (for the sake of saving space in part 2)
  else{
    char string1[101] = {};
    char string2[101] = {};
    string1[0] = ' ';
    string2[0] = ' ';

    //copies first and second string into string 1 and 2
    for(int r = 0; r<R+1; r++){
      string1[r+1] = first_string[r];
      for(int c = 0; c<C+1; c++){
        string2[c+1] = second_string[c];
      } 
    }

    //declaring and preping our reference arrays for edit distance calculations
    int row1[C+1];
    for(int c = 0; c<C+1; c++){
      row1[c] = c;
    }
    int row2[C+1];
    for(int c = 0; c<C+1; c++){
      row2[c] = 0;
    }
    //----------------performs the edit distance algorithim----------------
    for(int r = 1; r<R+1; r++){
      row2[0] = r;
      for(int c = 1; c<C+1; c++){
        if(string2[c] == string1[r]){
          row2[c] = min_from_3(row1[c]+1,row2[c-1]+1,row1[c-1]);
        }
        else{
          row2[c] = min_from_3(row1[c]+1,row2[c-1]+1,row1[c-1]+1);
        }
      }
      //shifts contents of row2 into row 1
      for(int i = 0; i<C+1; i++){
        row1[i] = row2[i];
      } 
      //clears the contents of row2
      for(int j = 0; j<C+1; j++){
        row2[j] = 0;
      } 

    }
    editDistance = row1[C];
    //---------------------------------------------------------------------
  }


  return editDistance; 
}

/*
Parameters:
  - testname - string containing the name of the file with the paragraph to spell check, includes file extenssion e.g. "text1.txt" 
  - dictname - name of file with dictionary words. Includes file extenssion, e.g. "dsmall.txt"
Behavior: If any of the files cannot be open displays a message and returns. (Does not exit the program.)
*/
void spell_check(char * testname, char * dictname){
  //opening file for creating the dictionary and list tables
  FILE* dp = fopen(dictname,"r");
  if(dp == NULL){
    printf("\nno %s file\n",dictname);
    return;
  }
  FILE* tp = fopen(testname,"r");
  if(tp == NULL){
    printf("\nno %s file\n",testname);
    fclose(dp);
    return;
  }

  //allocates and fills dictionary table
  int D = 0;
  char** dictionary = build_char_table(&dp,&D);

  printf("\n\nLoaded dictionary %s has size: %d\n\n",dictname,D);

  //allocates and fills list table
  int T = 0;
  char** testTable = build_char_table(&tp,&T);

  //only allocates the table for the edit distances of the dictionary table.
  //Its should always be the same size of dictionary table, and the order of the words and edit distances align
  int* edit_table = alloc_edit_table(D);

  int t,d,min;
  char getNewSpace;
  int choice = 0;
  int dictWordCount = 0;
  //Outer loop iterates through the list table
  for(t = 0; t<T; t++){
    //the first loop iteration does not require overwritting dictionary table.
    // All other iterations overwrite dictionary table for the sake of saving space.
    if(t != 0){
      // Why do I overwrite the dictionary table?

      // I implemented an insert sort function that sorts both dictionary table,
      // and the edit distance table in tandem.

      // This helps with finding the smallest edit distance and it groups
      // all words with the same edit distance into a cluster at the beginning of
      // the table.

      // This makes it easier to print the options, but it does destroy the
      // the original order of the dictionary table because each dictionary word
      // is associated with diferent edit distances depending on the current 
      // list table word that we are on.

      // Re writting the info in the dictionary file back into the dictionary table
      // overcomes this issue.

      overwrite_dict_table(&dp,dictionary,&D);
    }

    //Holds the string inputed by the user when option -1 is selected.
    char userString[101];
    printf("---> |%s|\n",testTable[t]);
    printf("-1 - type correction\n");
    printf(" 0 - leave word as is (do not fix spelling)\n");
    // Every cell in edit distance corresponds to it's associated word in
    // the dictionary table.
    fill_edit_table(edit_table, dictionary, testTable[t], D);
    insert_sort(dictionary, edit_table, D);
    min = edit_table[0];

    printf("     Minimum distance: %d\n",min);
    printf("     Words that give minimum distance:\n");

    //Counts up the words in the dictionary table that have the smallest edit distances.
    //Thanks to the insert sort, they should be clustered at the begining of the table.
    while(edit_table[dictWordCount] == min){
      dictWordCount++;
      printf("%2d - %s\n",dictWordCount,dictionary[dictWordCount - 1]);
    }
    
    printf("Enter your choice: ");
    scanf("%d%c", &choice, &getNewSpace);    
    //invalid choices
    if(choice < -1 || choice > dictWordCount){
      printf("Invalid choice. Original word will be kept.\n");
      printf("The correct word is: %s",testTable[t]);
    }
    //the choice is -1
    else if(choice == -1){
      printf("Enter correct word: ");
      scanf("%s%c", userString, &getNewSpace);
      printf("\n");
      printf("The correct word is: %s",userString);
    }
    //the choice is 0
    else if(choice == 0){
      printf("The correct word is: %s",testTable[t]);
    }
    //user chooses from list
    else{
      printf("The correct word is: %s",dictionary[choice-1]);
    }
    dictWordCount = 0;
    printf("\n\n");
  }
  free(edit_table);
  free_char_table(dictionary,D);
  free_char_table(testTable,T);
  fclose(tp);
  fclose(dp);
}

