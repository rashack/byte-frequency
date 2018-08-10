#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LEN 4096

void print_bytes (int *bytes, int s, int t) {
  int i;
  for (i = s; i < t; i++) {
    printf ("%4d", bytes[i]);
  }
  printf ("\n");
}

void print_one_column(int *bytes) {
  int i;
  for (i = 0; i < 256; i++)
    printf ("%4d:%8d\n", i, bytes[i]);
}

/* void print_one_column_latin1(int *bytes) { */
/*   int i; */
/*   for (i = 0; i < 256; i++) */
/*     printf ("%4d  %4x: %8d %c\n", i, i, bytes[i], to_printable_latin1(i)); */
/* } */

void to_printable_latin1(int i, unsigned char *utf) {
  if (i > 31 && i < 127) {
    utf[0] = i;
  } else if (i > 160 && i < 256) {
    ((int*)utf)[0] = i & (0x3f + 0x80);
  } else {
    utf[0] = 32;
  }
}

void print_columns_latin1(int *bytes) {
  int i;
  unsigned char utf[16];
  memset(utf, 0, 16);
  for (i = 0; i < 256; i++) {
    to_printable_latin1(i, utf);
    printf("%4d  %4x: %8d %s\n", i, i, bytes[i], utf);
  }
}

int printable_latin1(int i) {
  if (i > 31 && i < 127)
    return i;
  else if (i > 160 && i < 256)
    return i;
  else
    return 32;
}

int printable(int i) {
  if (isprint(i))
    return i;
  else
    return 32;
}

void print_divided (int *bytes, int parts) {
  int p = 256 / parts;
  int i = 0;
  for (i = 0; i < 256; i += p)
    print_bytes (bytes, i, i + p);
}

void print_single (int *bytes) {
  int i;
  for (i = 0; i < 256; i++)
    printf ("%d ", bytes[i]);
  printf ("%d\n", bytes[i]);
}

int main (int argc, char **args) {
  int bytes[256];
  unsigned char buffer[BUF_LEN];
  int bytes_read = 0;
  FILE *fp;
  int i;

  for (i = 0; i < 256; i++)
    bytes[i] = 0;

  if ((fp = fopen (args[1], "r")) == NULL) {
      printf ("Cannot open file.\n");
      exit (1);
    }

  do {
    bytes_read = fread (buffer, sizeof(unsigned char), BUF_LEN, fp);
    for (i = 0; i < bytes_read; i++)
      bytes[buffer[i]]++;
  } while (bytes_read == BUF_LEN);


  if (!feof (fp)) {
    printf ("File read error.\n");
  }

  fclose(fp);

  //print_one_column(bytes);
  //  print_one_column_latin1(bytes);
  print_columns_latin1(bytes);
  print_divided (bytes, 8);
  //print_single (bytes);

  unsigned char str[] = "fooö";
  to_printable_latin1(197, str);
  printf("\n%s\n", str);

  for (i = 0; i < 6; i++) {
    printf("(i:%d) -> '%c':%d\n", i, str[i], str[i]);
  }

  return 0;
}
