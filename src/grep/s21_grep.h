#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 99999

typedef struct flags {
  int e, i, v, c, l, n, h, s, f, o, pattern_count;
} f;

int Parsing(struct flags *f, int argc, char *argv[], char *pattern);
void grep(struct flags *f, int argc, char *pattern, char *argv[]);
// void flag_f(char *pattern, char *temp);