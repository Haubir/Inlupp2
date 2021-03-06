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
  char *description;
  int price;
  int amount;
  shelves_list *shelves;
};

/* Allocates memory for an empty ware and returns it */
ware *ware_new(){
  ware *new_ware = calloc(1, sizeof(ware));
  new_ware->key = NULL;
  new_ware->description = NULL;
  new_ware->price = 0;
  new_ware->amount = 0;
  new_ware->shelves = shelves_new();
  
  return new_ware;
}

/* Free:s up the memory that was allocated for a ware */
bool ware_free(ware *to_delete) {
  free(to_delete->key);
  free(to_delete->description);
  to_delete->price = 0;
  to_delete->amount = 0;
  
  if (to_delete->shelves) {
    shelves_free(to_delete->shelves);
    to_delete->shelves = NULL;
  }
  
  free(to_delete);
  to_delete = NULL;
  
  bool ret = to_delete == NULL;
  
  return ret;
}

/* Copies the source ware into the destination ware */
void ware_copy(ware *destination, ware *source) {
  char *dest_key = string_new();
  string_copy(dest_key, ware_get_key(source));
  ware_set_key(destination, dest_key);
  
  char *dest_description = string_new();
  string_copy(dest_description, ware_get_description(source));
  ware_set_description(destination, dest_description);
  
  int dest_price = 0;
  dest_price = ware_get_price(source);
  ware_set_price(destination, dest_price);
  
  int dest_amount = 0;
  dest_amount = ware_get_amount(source);
  ware_set_amount(destination, dest_amount);
  
  shelves_copy(destination->shelves, source->shelves);
}

/* Sets a new key for the ware */
void ware_set_key(ware *input_ware, char *key) {
  input_ware->key = key;
}

/* Sets a new description for the ware */
void ware_set_description(ware *input_ware, char *description) {
  input_ware->description = description;
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

/* Updates the amount of the ware by recounting the quantities of the shelves in the shelves_list */ 
void ware_update_amount(ware *input_ware){
  if (input_ware->shelves == NULL) return;
  
  list_node *iter = shelves_list_get_first(input_ware->shelves);
  int count = 0;
  
  while (iter) {
    shelf *iter_shelf = (shelf *) list_node_get_data(iter);
    int iter_quantity = shelf_get_quantity(iter_shelf);
    count += iter_quantity;
    iter = list_node_get_next(iter);
  }
  
  input_ware->amount = count;
}

/* Sets a new list of shelves for the ware */
void ware_set_shelves(ware *input_ware, shelves_list *shelves) {
  input_ware->shelves = shelves;
} 

/* Returns the key of the ware */
char *ware_get_key(ware *input_ware) {
  return input_ware->key;
}

/* Returns the description for the ware */
char *ware_get_description(ware *input_ware) {
  return input_ware->description;
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
shelves_list *ware_get_shelves(ware *input_ware) {
  return input_ware->shelves;
}

/* Shows the contents of the ware. */
void ware_show(ware *input_ware) {
  printf("Namn: %s\n", input_ware->key);
  printf("Beskrivning: %s\n", input_ware->description);
  printf("Pris: %d\n", input_ware->price);
  printf("Antal: %d\n", input_ware->amount);
  printf("\n%s finns lagrat på följande platser: \n\n", input_ware->key);
  shelves_show(input_ware->shelves, "shelf");
}

/* Add information to the ware, such as name, price, amount and locations. */
void ware_enter_information(ware *input_ware, char *new_key) {
  char *new_description = string_new();
  int new_price = 0;
  
  string_entry("Beskriv varan, så tydligt som möjligt: ", new_description);
  int_entry("Skriv in varans pris: ", &new_price);
  
  ware_set_key(input_ware, new_key);
  ware_set_description(input_ware, new_description);
  ware_set_price(input_ware, new_price);
}

/* Add shelf locations for the ware. */
void ware_enter_shelves(ware *input_ware, char *shelf_location) {
  shelves_list *new_shelves = input_ware->shelves;
  int shelf_quantity = input_ware->amount;
  shelf *new_shelf = shelf_new();
  shelf_set_location(new_shelf, shelf_location);
  shelf_set_quantity(new_shelf, shelf_quantity);
  
  shelves_list_prepend(new_shelves, new_shelf);
}

/* Increments the amount of the ware by adding amounts of it to a new shelf. */
void ware_increment_shelves(ware *input_ware, char *shelf_location, int increment) {
  shelf *new_shelf = shelf_new();
  shelf_set_location(new_shelf, shelf_location);
  shelf_set_quantity(new_shelf, increment);
  shelves_list_prepend(input_ware->shelves, new_shelf);
  ware_update_amount(input_ware);
}

/* Edit the key of the input_ware */
void ware_edit_name(ware *input_ware) {
  char *answer = string_new();
  string_entry("Skriv ett nytt namn för varan:", answer);
  
  free(ware_get_key(input_ware));
  ware_set_key(input_ware, NULL);
  ware_set_key(input_ware, answer);
}

/* Edit the description of the input_ware */
void ware_edit_description(ware *input_ware){
  char *answer = string_new();
  string_entry("Skriv en ny beskrivning för varan:", answer);
  
  free(ware_get_description(input_ware));
  ware_set_description(input_ware, NULL);
  ware_set_description(input_ware, answer);
}

/* Edit the price of the input_ware */
void ware_edit_price(ware *input_ware){
  int answer = 0;
  int_entry("Skriv ett nytt pris för varan:", &answer);
  
  ware_set_price(input_ware, answer);
}
