#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int string_is_alpha(string s){
  for (int i = 0, n = strlen(s); i < n; i++){
    if (!isalpha(s[i])) {
      return 0;
    }
  }
  return 1;
}

string string_tolower(string s) {
  static char lowered[26];
  for (int i = 0, n = strlen(s); i < n; i++){
    lowered[i] = tolower(s[i]);
  }
  return lowered;
}

int main(int argc, string argv[]) {
  // Check if the user provide more or less than 2 command line arguments
  if (argc != 2) {
    printf("Usage: ./substitution key)\n");
    return 1;
  }

  // Check for valid key
  printf("Validating key...\n");

  // Key must contain 26 characters
  if (strlen(argv[1]) != 26) {
    printf("Key must contain 26 characters.\n");
    return 1;
  }

  // Key must not contain any character that is not an alphabetic character.
  if (!string_is_alpha(argv[1])) {
    printf("Key must contain only alphabetic character (a-Z).\n");
    return 1;
  }

  // Convert key to lowercase
  string key = string_tolower(argv[1]);

  // Key must contain each letter exactly once.
  int alpha_len = 26;
  for (int i = 0; i < alpha_len - 1; i++){
    for (int j = i + 1; j < alpha_len; j++){
      if (key[i] == key[j]) {
        printf("Key must contain each letter exactly once.\n");
        printf("Duplicate key detected \"%c\".\n", key[i]);
        return 1;
      }
    }
  }

  // Key is valid
  printf("Valid key received.\n");

  // Encryption logic
  printf("Beginning encryption...\n");
  string plain_text = get_string("plaintext: ");
  int plain_text_length = strlen(plain_text);
  char ciphertext[plain_text_length];

  for (int i = 0; i < plain_text_length; i++){
    // Push non-alphabet into the array as it is
    if (!isalpha(plain_text[i])){
      ciphertext[i] = plain_text[i];
      continue;
    }

    // Preserve case
    bool lowercase = true;
    if (!islower(plain_text[i])){
      lowercase = false;
    }

    // Encrypt text
    char text = tolower(plain_text[i]);

    // get the ascii value
    // a to z in ascii is 97 to 122
    int ascii_decimal = (int) text;

    // a(97) must equal key(0) and z(122) = key(25)
    int index = ascii_decimal - 97;

    // push to ciphertext while preserving case
    if (!lowercase) {
      ciphertext[i] = toupper(key[index]);
    } else {
      ciphertext[i] = key[index];
    }

    // printf("ciphertext[%i] = %c\n", i, key[index]);
  }

  // Print ciphertext
  printf("ciphertext: ");
  for (int i = 0; i < sizeof ciphertext / sizeof ciphertext[0]; i++){
    printf("%c", ciphertext[i]);
  }
  printf("\n");

  return 0;
}
