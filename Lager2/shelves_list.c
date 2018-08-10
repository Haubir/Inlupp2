//
//  shelves_list.c
//  Lager2
//
//  Created by Haubir Mariwani on 4/27/18.
//  Copyright © 2018 HauCorp. All rights reserved.
//

#include "shelves_list.h"

struct shelves_list {
  list_node *first; /// Points to the first element of the list
  list_node *last; /// Points to the last element of the list
  int size;
};

struct list_node {
  void *data;
  list_node *next;
};

struct shelf {
  char *location; /// Contains the location of the shelf
  int quantity;
};

/* Allocates memory for a shelves_list struct and returns an empty struct */
shelves_list *shelves_new() {
  shelves_list *new_shelves = calloc(1, sizeof(shelves_list));
  new_shelves->first = NULL;
  new_shelves->last = NULL;
  new_shelves->size = 0;
  
  return new_shelves;
}

/* Deletes the input_list and free:s the memory that it had allocated */
void shelves_free(shelves_list *input_list) {
  while (!shelves_list_is_empty(input_list)) shelves_list_top(input_list);
  free(input_list);
}

/* Copies the source_list into the destination_list */
void shelves_copy(shelves_list *destination_list, shelves_list *source_list) {
  list_node *iter = source_list->first;
  
  while (iter) {
    shelf *iter_shelf = (shelf *) iter->data;
    shelf *new_shelf = shelf_new();
    shelf_copy(new_shelf, iter_shelf);
    
    shelves_list_append(destination_list, new_shelf);
    iter = iter->next;
  }
}

/* Returns the first list_node of the input_list */
list_node *shelves_list_get_first(shelves_list *input_list) {
  return input_list->first;
}

/* Returns the last list_node of the input_list */
list_node *shelves_list_get_last(shelves_list *input_list) {
  return input_list->last;
}

/* Returns the size of the input_list */
int shelves_list_get_size(shelves_list *input_list) {
  return input_list->size;
}

/* Sets the first list_node of the input_list to the input list_node */
void shelves_list_set_first(shelves_list *input_list, list_node *first) {
  input_list->first = first;
}

/* Sets the last list_node of the input_list to the input list_node */
void shelves_list_set_last(shelves_list *input_list, list_node *last) {
  input_list->last = last;
}

/* Sets the size of the input_list to the input size */
void shelves_list_set_size(shelves_list *input_list, int size) {
  input_list->size = size;
}

/* Checks if the input_list is empty */
bool shelves_list_is_empty(shelves_list *input_list) {
  return input_list->size == 0;
}

/* Allocates memory for a list_node struct and returns an empty struct */
list_node *list_node_new() {
  list_node *new_list_node = calloc(1, sizeof(list_node));
  
  new_list_node->data = NULL;
  new_list_node->next = NULL;
  
  return new_list_node;
}

/* Deletes the input_list_node and free:s the memory that it had allocated */
bool list_node_free(list_node *to_delete, int flag) {
  if (flag == 1) {
    shelf *shelf_to_delete = (shelf *) to_delete->data;
    shelf_free(shelf_to_delete);
  }
  to_delete->data = NULL;
  to_delete->next = NULL;
  free(to_delete);
  to_delete = NULL;
  
  bool ret = to_delete == NULL;
  
  return ret;
}

/* Returns the data of the input list_node */
void *list_node_get_data(list_node *input_list_node) {
  return input_list_node->data;
}

/* Returns the list_node that the next pointer of the input list_node points to */
list_node *list_node_get_next(list_node *input_list_node) {
  return input_list_node->next;
}

/* Sets the data of the input_list_node to the input data */
void list_node_set_data(list_node *input_list_node, void *data) {
  input_list_node->data = data;
}

/* Sets the next pointer of the input_list_node to the input next list_node */
void list_node_set_next(list_node *input_list_node, list_node *next) {
  input_list_node->next = next;
}

/* Shows the content of the input_list_node. */
void list_node_show(list_node *input_list_node, char *flag) {
  if (input_list_node->data == NULL) {
    printf("list_node_show(): The node has no data....\n");
  }
  if (string_equals(flag, "shelf")) {
    shelf *input_shelf = (shelf *) input_list_node->data;
    shelf_show(input_shelf);
  }
}

/* Allocates memory for a shelf struct and returns an empty struct */
shelf *shelf_new() {
  shelf *new_shelf = calloc(1, sizeof(shelf));
  
  new_shelf->location = NULL;
  new_shelf->quantity = 0;
  
  return new_shelf;
}

/* Deletes the input shelf and free:s the memory that it had allocated */
bool shelf_free(shelf *to_delete) {
  free(to_delete->location);
  free(to_delete);
  to_delete = NULL;
  bool ret = to_delete == NULL;
  
  return ret;
}

/* Copies the source shelf into the destination shelf */
void shelf_copy(shelf *destination, shelf *source) {
  char *dest_location = string_new();
  string_copy(dest_location, source->location);
  
  destination->location = dest_location;
  destination->quantity = source->quantity;
}

/* Returns true if the shelf is empty. */
bool shelf_is_empty(shelf *input_shelf) {
  return input_shelf->quantity == 0;
}

/* Returns the location of the input_shelf */
char *shelf_get_location(shelf *input_shelf) {
  return input_shelf->location;
}

/* Returns the quantity of the input_shelf */
int shelf_get_quantity(shelf *input_shelf) {
  return input_shelf->quantity;
}

/* Sets the location of the input_shelf to the input location */
void shelf_set_location(shelf *input_shelf, char *location) {
  input_shelf->location = location;
}

/* Sets the quantity of the input_shelf to the input quantity */
void shelf_set_quantity(shelf *input_shelf, int quantity) {
  input_shelf->quantity = quantity;
}

/* Increments the quantity of the input_shelf */
void shelf_increment_quantity(shelf *input_shelf, int increment) {
  input_shelf->quantity += increment;
}

/* Decrements the quantity of the input_shelf */
void shelf_decrement_quantity(shelf *input_shelf, int decrement) {
  input_shelf->quantity -= decrement;
}

/// Shows the content of the input_shelf.
void shelf_show(shelf *input_shelf) {
  if (input_shelf == NULL) {
    printf("shelf_show(): The shelf is NULL...\n");
    return;
  }
  printf("%s ", input_shelf->location);
  printf("(%d stycken)", input_shelf->quantity);
}

/* Inserts an element to the front of the input_list */
void shelves_list_prepend(shelves_list *input_list, void *new_data) {
  list_node *new_first = list_node_new();
  new_first->data = new_data;
  
  if (input_list->first) new_first->next = input_list->first;
  else input_list->last = new_first;
  
  input_list->first = new_first;
  input_list->size++;
}

/* Inserts an element to the back of the input_list */
void shelves_list_append(shelves_list *input_list, void *new_data) {
  list_node *new_last = list_node_new();
  new_last->data = new_data;
  
  if (input_list->last) input_list->last->next = new_last;
  else input_list->first = new_last;
  
  input_list->last = new_last;
  input_list->size++;
}

/* Removes the first element of the input_list */
void shelves_list_top(shelves_list *input_list) {
  if (shelves_list_is_empty(input_list)) return;
  
  list_node *to_delete = input_list->first;
  if (to_delete->next) {
    list_node *new_first = to_delete->next;
    input_list->first = new_first;
  }
  
  int flag = 1; // flag == 1 for shelf
  
  list_node_free(to_delete, flag);
  
  input_list->size--;
}

/* Removes the last element of the input_list */
void shelves_list_tail(shelves_list *input_list) {
  if (shelves_list_is_empty(input_list)) return;
  
  list_node *to_delete = input_list->last;
  list_node *new_last = input_list->first;
  
  if (new_last == to_delete) { // There is only one element in the list
    input_list->first = NULL;
    input_list->last = NULL;
  }
  else {
    while (new_last->next->next != NULL) new_last = new_last->next;
    input_list->last = new_last;
    new_last->next = NULL;
  }

  int flag = 1; // flag == 1 for shelf
  
  list_node_free(to_delete, flag);
  
  input_list->size--;
}

/* Checks if the key matches an existing shelf in the input_list, returns true if there is a match, false if not. */
bool shelf_already_exists(shelves_list *input_list, char *key) {
  return find_list_node_by_shelf_location(input_list, key) != NULL;
}

/* Finds a list_node in the input_list whose shelf has the same location as the input key and returns it. If no list_node was found, the return value is NULL */
list_node *find_list_node_by_shelf_location(shelves_list *input_list, char *key) {
  list_node *iter = input_list->first;
  
  while (iter) {
    shelf *iter_shelf = (shelf *) iter->data;
    if (string_equals(key, iter_shelf->location)) return iter;
    iter = iter->next;
  }
  return NULL;
}

/* Removes the element in the input_list that has the same name as the input key */
bool shelves_list_remove_by_location(shelves_list *input_list, char *key) {
  if (shelves_list_is_empty(input_list)) return false;
  
  list_node *match = find_list_node_by_shelf_location(input_list, key);
  if (match == NULL) return false; // Shelf was not found
  bool to_delete_found = false;
  list_node *iter = input_list->first;
  
  if (match == input_list->first) {
    shelves_list_top(input_list);
  }
  else if (match == input_list->last) {
    shelves_list_tail(input_list);
  }
  else {
    while (iter->next) {
      list_node *iter_next = iter->next;
      shelf *next_shelf = (shelf *) iter_next->data;
      
      if (string_equals(key, next_shelf->location)) {
        to_delete_found = true;
        iter->next = iter_next->next;
        if (iter->next == NULL) input_list->last = iter;
        
        int flag = 1; // flag == 1 for shelf 
        
        list_node_free(iter_next, flag);
        
        input_list->size--;
        break;
      }
      iter = iter->next;
    }
  }
  return to_delete_found;
}

/* Finds a list_node in the input_list at the same index as the input index and returns it. */
list_node *find_list_node_by_index(shelves_list *input_list, int index) {
  if (index >= input_list->size) {
    printf("find_list_node_by_index(): Index was too large...\n");
    return NULL;
  }
  list_node *iter = input_list->first;
  for (int i = 0; i < index; i++) iter = iter->next;
  
  return iter;
}

/* Removes the element in the input_list that has the same index in the list as the input index */
bool shelves_list_remove_by_index(shelves_list *input_list, int index) {
  if (shelves_list_is_empty(input_list)) return false;
  
  bool to_delete_found = false;
  
  list_node *to_delete = find_list_node_by_index(input_list, index);
  if (to_delete) {
    if (to_delete == input_list->first) {
      shelves_list_top(input_list);
      return true;
    }
    if (to_delete == input_list->last) {
      shelves_list_tail(input_list);
      return true;
    }
    to_delete_found = true;
    list_node *iter = input_list->first;
    shelf *to_delete_shelf = (shelf *) to_delete->data;
    char *to_delete_key = to_delete_shelf->location;
    
    while (iter->next) {
      list_node *iter_next = iter->next;
      shelf *next_shelf = (shelf *) iter_next->data;
      
      if (string_equals(to_delete_key, next_shelf->location)) {
        to_delete_found = true;
        iter->next = iter_next->next;
        if (iter->next == NULL) input_list->last = iter;
        
        int flag = 1; // flag == 1 for shelf 
        
        list_node_free(iter_next, flag);
        
        input_list->size--;
        break;
      }
      iter = iter->next;
    }
  }
  
  return to_delete_found;
}

/* Shows the contents of the shelves_list. */
void shelves_show(shelves_list *input_list, char *flag) {
  if (input_list->size == 0) {
    printf("shelves_show(): There are no shelves...\n");
    return;
  }
  
  list_node *iter = input_list->first;
  int count = 1;
  while (iter) {
    printf("%d. ", count);
    list_node_show(iter, flag);
    printf("\n");
    iter = iter->next;
    count++;
  }
}

shelf *shelves_list_find_max_shelf_quantity(shelves_list *input_list) {
  list_node *iter = input_list->first;
  int compare = -1;
  shelf *max_shelf = NULL;
  while (iter) {
    shelf *iter_shelf = (shelf *) iter->data;
    if (iter_shelf->quantity > compare) {
      compare = iter_shelf->quantity;
      max_shelf = iter_shelf;
    }
    
    iter = iter->next;
  }
  
  return max_shelf;
}

shelves_list *get_enough_shelves(int amount, shelves_list *input_list) {
  shelves_list *to_return = shelves_new();
  int to_return_quantity = 0;
  // 1. to_return ska innehålla hyllorna från input_list i storleksordning sett till quantity för varje shelf
  
  shelves_list *tmp = shelves_new();
  shelves_copy(tmp, input_list);
  shelves_list *ordered_list = shelves_new();
  
  while (!shelves_list_is_empty(tmp)) {
    shelf *max_shelf = shelves_list_find_max_shelf_quantity(tmp);
    shelf *new_shelf = shelf_new();
    shelf_copy(new_shelf, max_shelf);
    shelves_list_append(ordered_list, new_shelf);
    shelves_list_remove_by_location(tmp, max_shelf->location);
  }
  
  // 2. Behåll endast så många hyllor tillsammans som når upp till amount. Börja titta på hyllan med störst antal och fortsätt neråt tills totala hyllantalen precis kommit över amount.
  list_node *iter = ordered_list->first;
  while (to_return_quantity < amount) {
    shelf *iter_shelf = iter->data;
    shelf *new_shelf = shelf_new();
    shelf_copy(new_shelf, iter_shelf);
    to_return_quantity += iter_shelf->quantity;
    shelves_list_append(to_return, new_shelf);
    iter = iter->next;
  }
  
  shelves_free(tmp);
  shelves_free(ordered_list);
  
  return to_return;
}
