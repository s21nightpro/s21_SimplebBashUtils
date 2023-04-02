#include "s21_cat.h"
int main(int argc, char *argv[]) {
  opt flag = {0};
  int err = 0;
  if (parser(argc, argv, &flag) != 0) {
    err = parser(argc, argv, &flag);
    while (optind < argc) {
      err = reader(argv, &flag);
      optind++;
    }
  }
  return err;
}

int parser(int argc, char *argv[], opt *flag) {
  int opt, option_index, count = 1;
  while ((opt = getopt_long(argc, argv, "+benstvTE", long_option,
                            &option_index)) != -1) {
    switch (opt) {
      case 'b':
        flag->b = 1;
        break;
      case 'e':
        flag->e = 1, flag->v = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 't':
        flag->t = 1, flag->v = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'T':
        flag->t = 1;
        break;
      case 'E':
        flag->e = 1;
        break;
      default:
        count = 0, opt = -1;
        printf("usage: cat [-benstuv] [file ...]\n");
    }
  }
  if (flag->b) {
    flag->n = 0;
  }
  return count;
}

int reader(char *argv[], opt *flag) {
  FILE *file_name = fopen(argv[optind], "r");
  if (file_name) {
    int line_counter = 1, empty_line_counter = 0, last_s = '\n', current_s = 0;
    while ((current_s = fgetc(file_name)) != EOF) {
      if (flag->s && current_s == '\n' && last_s == '\n') {
        empty_line_counter++;
        if (empty_line_counter > 1) {
          continue;
        }
      } else {
        empty_line_counter = 0;
      }
      if (flag->b && last_s == '\n' && current_s != '\n')
        printf("%6d\t", line_counter++);
      if (flag->n && last_s == '\n') printf("%6d\t", line_counter++);
      if (flag->t && current_s == 9) {
        printf("^");
        current_s = 'I';
      }
      if (flag->e && current_s == '\n') printf("$");
      if (flag->v) {
        if ((current_s >= 0 && current_s <= 8) ||
            (current_s >= 11 && current_s <= 31)) {
          printf("^");
          current_s += 64;
        } else if (current_s == 127) {
          printf("^");
          current_s = '?';
        }
      }
      printf("%c", current_s);
      last_s = current_s;
    }
    fclose(file_name);
  } else {
    fprintf(stderr, "cat: %s: No such file or directory\n", argv[optind]);
  }
  return 0;
}
