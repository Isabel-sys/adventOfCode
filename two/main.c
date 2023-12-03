#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

struct Dice {
  int green;
  int red; 
  int blue; 
};

void part_one(FILE*);
void part_two(FILE*);
void print_dice(struct Dice);
void reset_config(struct Dice*,int amt);
int set_config(struct Dice*,int,const char*);
int power(struct Dice);
int dicecmp(struct Dice, struct Dice);
void parse_subset(struct Dice*,const char*);

int main(int argc, char** argv) {
  if (argc == 1) {
    printf("No file given\n");
    return EXIT_FAILURE;
  }
  FILE* input = fopen(argv[1],"r");
  if (!input) {
    printf("Failed to open file %s\n",argv[1]);
    return EXIT_FAILURE;
  }
  part_one(input);
  fseek(input,0,SEEK_SET);
  part_two(input);
  fclose(input);
  return EXIT_SUCCESS;
}

int set_config(struct Dice* config,int amt,const char* color) {
  if (!strcmp("red",color))
    config->red = amt;
  else if (!strcmp("green",color))
    config->green = amt; 
  else if (!strcmp("blue",color))
    config->blue = amt; 
  else 
    return 1; 
  return 0; 
}

void reset_config(struct Dice* dice, int amt) {
  dice->red   = amt; 
  dice->green = amt; 
  dice->blue  = amt;
}

void print_dice(struct Dice dice) {
  printf("{RED: %d, GREEN: %d, BLUE: %d}",dice.red,dice.green,dice.blue);
}

void parse_subset(struct Dice* config, const char* subset) {
  char cnfg_bffr[20];
  char color[5];
  int amt; 
  memset(cnfg_bffr,'\0',20);
  int buff_idx = 0; 
  for(int i = 0; subset[i] != '\0';i++) {
    if (subset[i] == ',') {
      cnfg_bffr[buff_idx] = '\0';
      sscanf(cnfg_bffr,"%d%s",&amt,color);
      memset(cnfg_bffr,'\0',20);
      if (set_config(config,amt,color)) {
        printf("Failed to parse %s\n",subset);
      }
      buff_idx = 0;
    } else {
      cnfg_bffr[buff_idx++] = subset[i];
    }
  }

  sscanf(cnfg_bffr,"%d%s",&amt,color);
  if (set_config(config,amt,color))
    printf("Failed to parse %s\n",subset);
}

int dicecmp(struct Dice d_one, struct Dice d_two) {
  return (d_one.red >= d_two.red && d_one.green >= d_two.green && d_one.blue >= d_two.blue);
}

void part_one(FILE* stream) {
  struct Dice total = {0,0,0};
  parse_subset(&total,"12 red, 13 green, 14 blue");
  struct Dice config = {0,0,0}; 
  char dice_buffer[200];
  int solution = 0; 
  int game_id = 0;;
  char* subset;
  int passed = 1; 
  while(fscanf(stream,"%*s%d%[^\n]%*c",&game_id,dice_buffer) != EOF) {
    passed = 1;
    printf("==== Game #%d ====\n",game_id);
    reset_config(&config,0);
    subset = strtok(dice_buffer+1,";");
    while(subset) {
      parse_subset(&config,subset);
      if (dicecmp(total,config)) {
        printf("\e[0;32m*/ - ");
      } else {
        passed = 0; 
        printf("\e[0;31mX - ");
      }  
      print_dice(config);
      printf("\e[0m\n");
      subset = strtok(NULL,";");
    }
    if (passed) {
      solution += game_id;
    }
  }
  printf("Solution = %d\n",solution);
}

int power(struct Dice dice) {
  int p = 1; 
  p *= !dice.red ? 1 : dice.red; 
  p *= !dice.green ? 1 : dice.green; 
  p *= !dice.blue ? 1 : dice.blue; 
  return p;
}

void part_two(FILE* stream) {
  struct Dice total = {0,0,0};
  parse_subset(&total,"12 red, 13 green, 14 blue");
  struct Dice config = {0,0,0};
  struct Dice min_set = {0,0,0};
  char dice_buffer[200];
  char* subset; 
  int solution = 0; 
  int game_id = 0; 
  int min_power = 0; 
  while(fscanf(stream,"%*s%d%[^\n]%*c",&game_id,dice_buffer) != EOF) {
    printf("==== Game #%d ====\n",game_id);
    subset = strtok(dice_buffer+1,";");
    while (subset) {
      reset_config(&config,0);
      parse_subset(&config,subset);
      subset = strtok(NULL,";");
      printf("*\t");
      print_dice(config);
      min_set.red = (config.red > min_set.red) && config.red ? config.red : min_set.red; 
      min_set.green = (config.green > min_set.green) && config.green ? config.green : min_set.green; 
      min_set.blue  = (config.blue > min_set.blue) && config.blue ? config.blue : min_set.blue; 
      printf("\n");
    }
    printf("The min set is ");
    print_dice(min_set);
    printf("\n");
    min_power = power(min_set);
    solution += min_power;
    printf("the power is %d\n",min_power);
    reset_config(&min_set,0);
  } 
  printf("Solution = %d\n",solution);
}
