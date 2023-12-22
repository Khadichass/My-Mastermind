#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef struct 
{
  int wellp;
  int missp;
  char* input;
} info_input;

int miss_placed(char* p1, char* p2)
{
  int miss = 0;

  for (int i = 0; p1[i]; i++) 
  {
    for (int j = 0; p2[j]; j++) 
    {
      if ((p1[i] == p2[j]) && (i != j)) 
      {
        miss++;
      }
    }
  }

  return miss;
}

int well_placed(char* p1, char* p2)
{
  int well = 0;

  for (int i = 0; p1[i]; i++) 
  {
    if (p1[i] == p2[i]) {
      well++;
    }
  }

  return well;
}

int my_strcmp(char* p1, char*p2)
{
  for (int i = 0; p1[i] != '\0'; i++ ) 
  {
    if (p1[i] != p2[i]) 
    {
      return 1;
    }
  }
  
  return 0;
}

int my_strcpy(char* p1, char*p2)
{
  for (int i = 0; p2[i] != '\0'; i++) 
  {
    p1[i] = p2[i];
  }

  return 0;
}

int my_atoi(char* p1)
{
  int numb = 0;
  for(int i = 0; p1[i] != '\0'; i++ )
  {
    numb += p1[i] - 48;
    numb *=10;

  }

  return numb / 10;
}

int my_strchar(char* p1, char p2)
{
  for (int i = 0; p1[i] != '\0'; i++) 
  {
    if (p1[i] == p2) 
    {
      return 1;
    }
  }

  return 0;
}

char* random_code()
{
  srand(time(0));

  char* random_numb = calloc(sizeof(char), 5);
  int tempr;

  int i = 0;

  while (i < 4) 
  {
  
    tempr = rand() % 9 + 48;

    if (my_strchar(random_numb, tempr) == 0) 
    {
      random_numb[i] = tempr;
      i++;
    }
  }

  return random_numb;
}

char* my_scanf()
{
  char* user_input = calloc(sizeof(char), 10);
  int i = 0;
  char letter;
  int ch;
  while ((ch = read(0, &letter, 1))) 
{
    if (letter == '\n') 
    {
      return user_input;
    }
    else 
    {
      user_input[i] = letter;
    }

    i++;
  }
  if(ch == 0)
  {
    printf("exited with CTRL+D\n");
    exit(0);
  }

  return user_input;
}

int my_strlen(char* p1)
{
  int length = 0;

  while (p1[length] != '\0') 
  {
    length++;
  }

  return length;
}

int is_number(char* p1)
{
  for (int i = 0; p1[i] != '\0'; i++) 
  {
    if (p1[i] < '0' || p1[i] > '8')
    {
      return 1;
    }
  }

    return 0;
}

int my_repeat (char* p1)
{
    
  for (int i = 0; p1[i]; i++ ) 
  {
    for (int j = i + 1; p1[j]; j++ ) 
    {
      if (p1[i] == p1[j]) {
        return 1;
      }
    }
  }
    
    return 0;
}
int wrong_input(char* user_input)
{   
  if ((my_strlen(user_input) != 4) || (is_number(user_input) || (my_repeat(user_input)))) 
  {
    printf("Wrong input!\n");
    return 1;
  }

  return 0;
}

void main_work(char* secret_code, int attemp)
{
  char* user_input;
  printf("Will you find the secret code?\nPlease enter a valid guess\n");

  for (int i = 0; i < attemp; i++) 
  {
    printf("---\n");
    printf("Round %d\n", i);
    write(1, ">", 1);
    user_input = my_scanf();
    
    while (1) 
    {
      if (wrong_input(user_input) == 0) 
      {
        break;
      }
      free(user_input);
      printf(">");
      fflush(stdout);
      user_input = my_scanf();
    }
    if(strcmp(secret_code, user_input) == 0)
    {
      printf("Congratz! You did it!\n");
      free(user_input);
      return;
    }
    printf("Well placed pieces: %d\n",well_placed(secret_code,user_input ));
    printf("Misplaced pieces: %d\n",miss_placed(secret_code,user_input ));
    free(user_input);
  }

}


int main(int argc, char** argv)
{
  char* secret_code = calloc(sizeof(char), 5);
  int attemp = 10;
  int flag = 0;
  if(argc){};

  
  for(int i = 1; i < argc; i++)
  {
    if (my_strcmp(argv[i], "-c") == 0) 
    {
      i++;
      flag = 1;
      my_strcpy(secret_code, argv[i]);
    }
    else if(my_strcmp(argv[i], "-t") == 0)
    {
      i++;
      attemp = my_atoi(argv[i]);
    }
      
  }
  if(flag == 0)
  {
    secret_code = random_code();
  }

  main_work(secret_code, attemp);
  free(secret_code);
}