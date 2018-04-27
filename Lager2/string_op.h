//
//  string_op.h
//  Lager2
//
//  Created by Haubir Mariwani on 4/16/18.
//  Copyright © 2018 HauCorp. All rights reserved.
//

#ifndef string_op_h
#define string_op_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/* Allocates memory for a string and returns it. */
char *string_new(void);

/* Copies the source string into the destination string. */
void string_copy(char *destination, char *source);

/* Compares two strings and determines which one comes first in alphabetical order or if they are the same word. */
int string_compare(char *first, char *second);

/* Converts all characters to lower case. */
void string_to_lower(char *string, char *after);

/* Converts a string to an int. */
int string_to_int(char *string);

/* Determines whether a string or character is in fact an int. */
bool is_int(char *string);

/* Calculates the length of a string. */
int string_length(char *string);

/* Handles string inputs into the system. */
void string_entry(char *input_text, char *result);

/* Strips the input string of the \0 character. */
void strip_string(char *buffer);

/* Handles int inputs into the system. */
void int_entry(char *input_text, int *result);

#endif /* string_op_h */
