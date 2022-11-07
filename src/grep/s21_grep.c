#include "s21_grep.h"

int main(int argc, char *argv[]) {
  struct flags f;
  int rezult = 0;
  memset(&f, 0, sizeof(f));
  char pattern[size] = {0};
  rezult = Parsing(&f, argc, argv, pattern);
  if ((rezult != 1) && ((argc >= 3))) {
    grep(&f, argc, pattern, argv);
  }
  return rezult;
}
int Parsing(struct flags *f, int argc, char *argv[], char *pattern) {
  int i = 0, result = 0;
  f->pattern_count = 0;
  while ((i = getopt_long(argc, argv, "e:ivclnhs", 0, 0)) != -1) {
    if (i == 'e') {
      if (f->pattern_count > 0) strcat(pattern, "|");
      strcat(pattern, optarg);
      f->pattern_count++;
      f->e = 1;
    } else if (i == 'i') {
      f->i = 1;
    } else if (i == 'v') {
      f->v = 1;
    } else if (i == 'c') {
      f->c = 1;
    } else if (i == 'l') {
      f->l = 1;
    } else if (i == 'n') {
      f->n = 1;
    } else if (i == 'h') {
      f->h = 1;
    } else if (i == 's') {
      f->s = 1;
    } else {
      result = 1;
    }
  }
  return result;
}
void grep(struct flags *f, int argc, char *pattern, char *argv[]) {
  int cflags = (f->i) ? REG_ICASE | REG_EXTENDED : REG_EXTENDED;
  int match, nline, match_line, last_s;
  regex_t reg;
  char text[size] = {0};
  regmatch_t pmatch;
  if (!f->e) snprintf(pattern, size, argv[optind++]);
  int check_files = argc - optind;
  for (int i = optind; i < argc; i++) {
    FILE *file_name = fopen(argv[optind], "r");
    if (file_name == NULL) {
      if (!f->s)
        fprintf(stderr, "grep: %s: No such file or directory\n", argv[optind]);
    } else {
      regcomp(&reg, pattern, cflags);
      match = 0, nline = 1, match_line = 0;
      while (fgets(text, size - 1, file_name) != NULL) {
        int status = regexec(&reg, text, 1, &pmatch, 0);
        match = 0;
        if (status == 0 && !f->v) match = 1;
        if (status == REG_NOMATCH && f->v) match = 1;
        if ((check_files > 1) && match && !f->c && !f->l && !f->h)
          printf("%s:", argv[optind]);
        if ((match) && (!f->l) && (!f->c) && (f->n)) printf("%d:", nline);
        if ((match) && !f->l && !f->c) printf("%s", text);
        last_s = text[strlen(text) - 1];
        nline++;
        match_line += match;
      }
      if (last_s != '\n' && match && !f->l && !f->c) {
        printf("\n");
      }
      regfree(&reg);
      fclose(file_name);
    }
    if (f->c && f->l && match_line > 1) match_line = 1;
    if (f->c) {
      if (check_files > 1 && !f->h) printf("%s:", argv[optind]);
      printf("%d\n", match_line);
    }
    if (f->l && match_line > 0) printf("%s\n", argv[optind]);
    match_line = 0;
    optind++;
  }
}