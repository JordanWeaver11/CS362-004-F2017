#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//define possible character values from ' ' to '~'
#define MAX_CHAR 126
#define MIN_CHAR 32
//define character values to insert in the string from the letter 'a' to the letter 'z'
#define MAX_STRING 122
#define MIN_STRING 97

//assume the string size is always 5
char STRING[6];

//Returns a number between low and high inclusive [low, high]
int getRand(int low, int high) {
	return rand() % (high - low + 1) + low;
}

char inputChar()
{
    //generate a character from a large subset of the ASCII table
    return getRand(MIN_CHAR, MAX_CHAR);
}

char *inputString()
{
    int i = 0;
    //fill the string with random lowercase letters
    for(i = 0; i < 5; i++) {
		STRING[i] = getRand(MIN_STRING, MAX_STRING);
	}
	STRING[5] = '\0';
    return STRING;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
