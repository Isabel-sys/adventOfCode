#include<stdio.h> 
#include<stdlib.h> 
#include<ctype.h>
#include<string.h> 
#include<time.h> 
int part_one(FILE*);
int part_two(FILE*);
int spell_to_num(const char*);
void timer(int* result, int (*func)(FILE*) ,FILE* input) {
  clock_t start = clock(); 
  *result = (*func)(input); 
  printf("Took %f seconds\n",(float)(start-clock())/CLOCKS_PER_SEC);
};
int main(int argc, char** argv  ) {
  if (argc == 1) {
    printf("No file given\n");
    return EXIT_FAILURE;
  }
  FILE* input = fopen(argv[1],"r");
  if (!input) {
    printf("Failed to open %s\n",argv[1]);
    return EXIT_FAILURE;
  }
  int solution = 0;

  timer(&solution,&part_one,input);
  printf("Part one:\t%d\n",solution);
  fseek(input,SEEK_SET,0);
  timer(&solution,&part_two,input);
  printf("Part two:\t%d\n",solution);
  fclose(input);
  return 0;
}
int spell_to_num(const char* string) {
  if (!strncmp("one",string,3)) {
    return 1; 
  } else if (!strncmp("two",string,3)) {
    return 2;
  } else if (!strncmp("three",string,5)) {
    return 3;
  } else if (!strncmp("four",string,4)) {
    return 4; 
  } else if (!strncmp("five",string,4)) {
    return 5;
  } else if (!strncmp("six",string,3)) {
    return 6; 
  } else if (!strncmp("seven",string,5)) {
    return 7;
  } else if (!strncmp("eight",string,5)) {
    return 8;
  } else if (!strncmp("nine",string,4)) {
    return 9;
  }
  return -1; 
}
int part_one(FILE* stream) {
	char buffer[100];
  int solution = 0; 
  int one,two;
  while(fscanf(stream,"%[^\n]%*c",buffer) != EOF) {
    one = 0;
    two = 0;
    for(int i = 0; buffer[i] != '\0';i++ ) {
      if (isdigit(buffer[i])) {
        if (!one) {
          one = buffer[i]-'0';
          two = one;
        } else 
          two = buffer[i]-'0';
      }
    }
    solution += (one*10)+two;
  }
  return solution; 
}
int part_two(FILE* stream) {
  char buffer[100];
  int solution = 0; 
  int one,two,possible;
  while(fscanf(stream,"%[^\n]%*c",buffer) != EOF) {
     one = 0; 
     two = 0; 
     possible = 0;
    for(int i = 0; buffer[i] != '\0';i++) {
      possible = spell_to_num(buffer+i);
      if (possible != -1) {
        if (!one) {
          one = possible;
          two = one; 
        } else 
          two = possible;
      }
      if (isdigit(buffer[i])) {
        if (!one) {
          one = buffer[i]-'0';
          two = one;
        } else 
          two = buffer[i]-'0';
      }
    }
    solution += (one*10)+two;
  }
  return solution;
}
