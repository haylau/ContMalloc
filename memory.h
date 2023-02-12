
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // bool
#include <string.h>
#include <ctype.h>   // toupper()

#define MEMSIZE  80
#define BUFSIZE  80
#define MAXCMDS  32

#define ALLOC    'A'
#define FREE     'F'
#define SHOW     'S'
#define READ     'R'
#define COMPACT  'C'
#define EXIT     'E'

#define FIRSTFIT 'F'
#define BESTFIT  'B'
#define WORSTFIT 'W'

#define EMPTY    '.'

void cont_alloc(char* memory, char name, int size, char algo);
void falloc(char* memory, char name, int size);
void balloc(char* memory, char name, int size);
void walloc(char* memory, char name, int size);
void cont_free(char* memory, char name);
void compact();
void readScript(char*** commandBuffer, int* bufSize, char* filename);
void show(char* memory);

void parseLines(char*** commandBuffer, int* bufSize, char* input);