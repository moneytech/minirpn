#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lex.h"

int next(token *t, FILE *f) {
  char t_buf[255];
  int num_read = 0;
  char c;
  int reading_value = 0;
  while((c = fgetc(f)) != EOF) {
    if(isspace(c)) {
      if(c == '\n') {
        printf("> ");
      }
      if(num_read > 0) {
        t_buf[num_read] = '\0';
        t->type = (reading_value ? T_VALUE : T_SYMBOL);
        if(t->type == T_VALUE) {
          t->value = atof(t_buf);
        } else {
          memset(t->symbol, '\0', 255);
          strncpy(t->symbol, t_buf, num_read);
        }
        return 1;
      } else {
        return 0;
      }
    } else {
      reading_value = isdigit(c);
      t_buf[num_read++] = c;
    }
  }

  return 0;
}
