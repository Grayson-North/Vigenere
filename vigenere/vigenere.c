//-----------------------------------
// Grayson North
// CIS 3360
// Spring 2020
// Vigenere Cipher
//-----------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//----------PROTOTYPES---------------
char *create_plaintext_array(char *plaintext_file);
char *create_cipher_array(char *key_file);
void create_encrypted_text(char *key, char *plaintext);
//-----------------------------------

int main(int argc, char **argv)
{
  int i, sum;
  char *plaintext_file, *key_file, *newKey, *newPlain;
  char key[2048], plain[2048];
  newKey = malloc(sizeof(char) * (512 + 1));
  newPlain = malloc(sizeof(char) * (512 + 1));
  for (i = 0; i < 512; i++)
  {
    newKey[i] = '\0';
    newPlain[i] = '\0';
  }
  for (i = 0; i < 2048; i++)
  {
    key[i] = '\0';
    plain[i] = '\0';
  }

  key_file = argv[1];
  plaintext_file = argv[2];

  FILE *file1 = fopen(key_file, "r");

  if (file1 == 0)
    printf("Could not open file.\n");

  fread(key, sizeof(char), 2048, (FILE*)file1);
  fclose(file1);

  FILE *file2 = fopen(plaintext_file, "r");
  if (file2 == 0)
    printf("Could not open file.\n");

  fread(plain, sizeof(char), 2048, (FILE*)file2);
  fclose(file2);


  newKey = create_cipher_array(key);
  newPlain = create_plaintext_array(plain);

  create_encrypted_text(newKey, newPlain);
  return 0;
}

char *create_cipher_array(char *key_file)
{
  int i, j, n, counter = 0;
  j = 0;

  n = strlen(key_file);
  char *key_array = malloc(sizeof(char) * (512 + 1));

  for (i = 0; i < 512; i++)
    key_array[i] = '\0';

  for (i = 0; i < n; i++)
  {
    if (isalpha(key_file[i]))
    {
      key_array[j] = tolower(key_file[i]);
      j++;
    }
  }

  printf("\n\nVigenere Key:\n\n");

  if (n <= 80)
    printf("%s\n", key_array);

  else
  {
    for (i = 0; i < 8; i++)
    {
      for (j = 0; j < 80; j++)
      {
        if (counter < 512 && key_array[counter] != '\0')
        {
          printf("%c", key_array[counter]);
          counter++;
        }
      }
      if (key_array[counter] == '\0')
        break;
      printf("\n");
    }
    printf("\n");
  }
  return key_array;
}

char *create_plaintext_array(char *plaintext_file)
{
  int i, j, n, counter = 0;
  j = 0;
  n = strlen(plaintext_file);
  char *plaintext_array = malloc(sizeof(char) * (512 + 1));

  for (i = 0; i < 512; i++)
    plaintext_array[i] = '\0';

  for (i = 0; i < n; i++)
  {
    if (isalpha(plaintext_file[i]))
    {
      plaintext_array[j] = tolower(plaintext_file[i]);
      j++;
    }
  }

  for (i = 0; i < 512; i++)
  {
    if(plaintext_array[i] == '\0')
      plaintext_array[i] = 'x';
  }

  printf("\n\nPlaintext:\n\n");

  for (i = 0; i < 7; i++)
  {
    for (j = 0; j < 80; j++)
    {
      if (counter < 512 && plaintext_array[counter] != '\0')
      {
        printf("%c", plaintext_array[counter]);
        counter++;
      }
    }
    if (plaintext_array[counter] == '\0')
      break;
    printf("\n");
  }
  printf("\n");
  return plaintext_array;
}

void create_encrypted_text(char *key, char *plaintext)
{
  int i, j, n, tmp, counter = 0;
  int counter1 = 0;
  char encrypted_text[512];

  for (i = 0; i < 512; i++)
    encrypted_text[i] = '\0';

  n = strlen(key);

  while (counter < 512)
  {
    for (i = 0; i < n; i++)
    {
      if (counter > 512)
        break;

      tmp = (key[i] + plaintext[counter]) % 26;
      tmp = tmp + 111;
      if(tmp > 'z')
        encrypted_text[counter] = tmp - 26;
      else
        encrypted_text[counter] = tmp;
      counter++;
    }
  }

  printf("\n\nCiphertext:\n\n");

  for (i = 0; i < 7; i++)
  {
    for ( j = 0; j < 80; j++)
    {
      if (counter1 < 512)
      {
        printf("%c", encrypted_text[counter1]);
        counter1++;
      }
    }
    if (encrypted_text[counter1] == '\0')
      break;
    printf("\n");
  }
  return;
}
