//
//  string_op.c
//  Lager2
//
//  Created by Haubir Mariwani on 4/16/18.
//  Copyright © 2018 HauCorp. All rights reserved.
//

#include "string_op.h"

char *string_new() {
  char *new_string = calloc(1024, sizeof(char));
  
  return new_string;
}

void string_copy(char *destination, char *source) {
  strncpy(destination, source, (size_t) string_length(source));
}

int string_compare(char *first, char *second) {
  char *first_lowercase = calloc(string_length(first), sizeof(char));
  char *second_lowercase = calloc(string_length(second), sizeof(char));
  
  string_to_lower(first, first_lowercase);
  string_to_lower(second, second_lowercase);
  int comparison = strcmp(first_lowercase, second_lowercase);
  
  /// Vi free:ar de extra minnesplatserna som användes för jämförelsen innan funktionen återvänder
  free(first_lowercase);
  free(second_lowercase);
  
  /// first kommer före second
  if (comparison < 0) {
    return -1;
  }
  /// second kommer före first
  else if (comparison > 0) {
    return 1;
  }
  /// first och second är samma ord
  else {
    return 0;
  }
}

bool string_equals(char *first, char *second) {
  return string_compare(first, second) == 0;
}

void string_to_lower(char *string, char *after) {
  strncpy(after, string, (size_t) string_length(string));
  for (int i = 0; string[i] != '\0'; i++) {
    after[i] = tolower(string[i]);
  }
}

int string_to_int(char *string) {
  if (!is_int(string)) {
    printf("string_to_int: String to be converted to int did not contain an integer...\n");
    return 0;
  }
  
  return atoi(string);
}

bool is_int(char *string) {  
  for (int i = 0; string[i] != '\0'; i++) {
    if (!isdigit(string[i])) {
      return false;
    }
  }
  
  return true;
}

int string_length(char *string) {
  int length = 0;
  
  for (int i = 0; string[i] != '\0'; i++) {
    length++;
  }
  
  return length;
}

void string_entry(char *input_text, char *result) {
  size_t buffer_len = 1024;
  char *buffer = string_new();
  
  printf("%s\n", input_text);
  getline(&buffer, &buffer_len, stdin);
  while(buffer[0] == '\n'){
    printf("Please enter something you ungrateful piece of shit scouser\n");
    getline(&buffer, &buffer_len, stdin);
  }
  strip_string(buffer);
  strcpy(result, buffer);
  free(buffer);
}

void strip_string(char *buffer) {
  for (int i = 0; buffer[i] != '\0'; i++) {
    if (buffer[i] == '\n') {
      buffer[i] = '\0';
    }
  }
}

void int_entry(char *input_text, int *result) {
  char *int_string = string_new();
  string_entry(input_text, int_string);
  
  while (!is_int(int_string)) {
    string_entry("Please enter an integer.", int_string);
  }
  
  *result = string_to_int(int_string);
  free(int_string);
}

char *int_to_string(int to_convert) {
  char *to_return = NULL;
  return to_return;
}
