#include <getopt.h>
#include <stdio.h>

typedef struct flag {
  int b, e, n, s, t, v;
} opt;

const struct option long_option[] = {{"number-nonblank", 0, 0, 'b'},
                                     {"number", 0, 0, 'n'},
                                     {"squeeze-blank", 0, 0, 's'},
                                     {0, 0, 0, 0}};

int parser(int argc, char *argv[], opt *flag);
int reader(char *argv[], opt *flag);
