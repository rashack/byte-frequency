#include <stdio.h>
#include <stdlib.h>

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
  for (i = 0; i < 255; i++)
    printf ("%4d:%8d\n", i, bytes[i]);
}

void print_divided (int *bytes, int parts) {
  int p = 256 / parts;
  int i = 0;
  for (i = 0; i < 256; i += p)
    print_bytes (bytes, i, i + p);
}

void print_single (int *bytes) {
  int i;
  for (i = 0; i < 255; i++)
    printf ("%d ", bytes[i]);
  printf ("%d\n", bytes[i]);
}

int main (int argc, char **args) {
  int bytes[256];
  unsigned char buffer[BUF_LEN];
  int bytes_read = 0;
  FILE *fp;
  unsigned char byte;
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

  print_one_column(bytes);
  print_divided (bytes, 8);
  //print_single (bytes);
}
