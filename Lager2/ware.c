//
//  ware.c
//  Lager2
//
//  Created by Haubir Mariwani on 4/25/18.
//  Copyright © 2018 HauCorp. All rights reserved.
//

#include "ware.h"

struct ware {
  char *key;
  int price;
  int amount;
  // list *shelves;
};

/* Allocates memory for an empty ware and returns it */
ware *ware_new(){
  ware *new_ware = calloc(1, sizeof(ware));
  new_ware->key = NULL;
  new_ware->price = 0;
  new_ware->amount = 0;
  //new_ware->shelves = NULL;
  
  return new_ware;
}

/* Free:s up the memory that was allocated for a ware */
bool ware_free(ware *to_delete) {
  free(to_delete->key);
  to_delete->price = 0;
  to_delete->amount = 0;
  
  /*if (to_delete->shelves) {
    shelves_free(to_delete->shelves);
    to_delete->shelves = NULL;
  } */
  
  free(to_delete);
  to_delete = NULL;
  
  bool ret = to_delete == NULL;
  
  return ret;
}

/* Sets a new key for the ware */
void ware_set_key(ware *input_ware, char *key) {
  input_ware->key = key;
}

/* Sets a new price for the ware */
void ware_set_price(ware *input_ware, int price) {
  input_ware->price = price;
}

/* Sets a new amount for the ware */
void ware_set_amount(ware *input_ware, int amount) {
  input_ware->amount = amount;
}

/* Increments the amount of the ware */
void ware_increment_amount(ware *input_ware, int amount) {
  input_ware->amount += amount;
}

/* Decrements the amount of the ware */
void ware_decrement_amount(ware *input_ware, int amount) {
  input_ware->amount -= amount;
}

/* Sets a new list of shelves for the ware */
/*void ware_set_shelves(ware *input_ware, list *shelves) {
  input_ware->shelves = shelves;
 } */

/* Returns the key of the ware */
char *ware_get_key(ware *input_ware) {
  return input_ware->key;
}

/* Returns the price of the ware */
int ware_get_price(ware *input_ware) {
  return input_ware->price;
}

/* Returns the amount of the ware */
int ware_get_amount(ware *input_ware) {
  return input_ware->amount;
}

/* Returns the list of shelves for the ware */
/*list *ware_get_shelves(ware *input_ware) {
  return input_ware->shelves;
 } */

/* Shows the contents of the ware. */
void ware_show(ware *input_ware) {
  printf("Namn: %s\n", input_ware->key);
  printf("Pris: %d\n", input_ware->price);
  printf("Namn: %d\n", input_ware->amount);
  /*printf("Finns på följande hyllplatser:\n");
  shelves_show(input_ware->shelves);*/
}

/* Add information to the ware, such as name, price, amount and locations. */
void ware_enter_information(ware *input_ware) {
  char *new_key = string_new();
  int new_price = 0;
  int insert_amount = 0;
  
  string_entry("Skriv ett namn för varan: ", new_key);
  int_entry("Skriv in varans pris", new_price);
  int_entry("Hur stort antal vill du lägga in i systemet?", insert_amount);
  
  // TODO: Saknas kod för att lägga till varans hyllplatser
  
  ware_set_key(input_ware, new_key);
  ware_set_price(input_ware, new_price);
  ware_increment_amount(input_ware, insert_amount);
}

