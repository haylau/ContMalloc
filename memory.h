
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // bool
#include <ctype.h>   // toupper()

#define MEMSIZE 80
#define BUFSIZE 80

#define ALLOC    'A'
#define FREE     'F'
#define SHOW     'S'
#define READ     'R'
#define COMPACT  'C'
#define EXIT     'E'

#define FIRSTFIT 'F'
#define BESTFIT  'B'
#define WORSTFIT 'W'

void cont_alloc(char name, int size, char algo);
void falloc();
void balloc();
void walloc();
void cont_free(char name);
void show(char* memory);
char** readScript();
void compact();