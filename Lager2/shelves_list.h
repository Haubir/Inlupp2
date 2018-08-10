//
//  shelves_list.h
//  Lager2
//
//  Created by Haubir Mariwani on 4/27/18.
//  Copyright © 2018 HauCorp. All rights reserved.
//

#ifndef shelves_list_h
#define shelves_list_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "string_op.h"

typedef struct shelves_list shelves_list;

typedef struct list_node list_node;

typedef struct shelf shelf;

/// Allocates memory for a shelves_list struct and returns an empty struct
///
/// \returns: an empty shelves_list struct
shelves_list *shelves_new(void);

/// Deletes the input_list and free:s the memory that it had allocated
void shelves_free(shelves_list *input_list);

/// Copies the source_list into the destination_list
void shelves_copy(shelves_list *destination_list, shelves_list *source_list);

/// Returns the first list_node of the input_list
///
/// \returns: a list_node
list_node *shelves_list_get_first(shelves_list *input_list);

/// Returns the last list_node of the input_list
///
/// \returns: a list_node
list_node *shelves_list_get_last(shelves_list *input_list);

/// Returns the size of the input_list
///
/// \returns: an integer
int shelves_list_get_size(shelves_list *input_list);

/// Sets the first list_node of the input_list to the input list_node
void shelves_list_set_first(shelves_list *input_list, list_node *first);

/// Sets the last list_node of the input_list to the input list_node
void shelves_list_set_last(shelves_list *input_list, list_node *last);

/// Sets the size of the input_list to the input size
void shelves_list_set_size(shelves_list *input_list, int size);

/// Checks if the input_list is empty
///
/// \returns true if the list is empty
bool shelves_list_is_empty(shelves_list *input_list);

/// Allocates memory for a list_node struct and returns an empty struct
///
/// \returns: an empty list_node
list_node *list_node_new(void);

/// Deletes the input_list_node and free:s the memory that it had allocated
bool list_node_free(list_node *to_delete, int flag);

/// Copies the source_list into the destination_list
void list_node_copy(list_node *destination, list_node *source);

/// Returns the data of the input list_node
///
/// \returns: a void pointer to the data
void *list_node_get_data(list_node *input_list_node);

/// Returns the list_node that the next pointer of the input list_node points to
///
/// \returns: a list_node
list_node *list_node_get_next(list_node *input_list_node);

/// Sets the data of the input_list_node to the input data
void list_node_set_data(list_node *input_list_node, void *data);

/// Sets the next pointer of the input_list_node to the input next list_node
void list_node_set_next(list_node *input_list_node, list_node *next);

/// Shows the content of the input_list_node.
void list_node_show(list_node *input_list_node, char *flag);

/// Allocates memory for a shelf struct and returns an empty struct
/// 
/// \returns: an empty shelf
shelf *shelf_new(void);

/// Deletes the input shelf and free:s the memory that it had allocated
bool shelf_free(shelf *to_delete);

/// Copies the source shelf into the destination shelf
void shelf_copy(shelf *destination, shelf *source);

/// Checks whether the input_shelf is empty, i.e. has a quantity of 0.
///
/// \returns: true if the shelf is empty 
bool shelf_is_empty(shelf *input_shelf);

/// Returns the location of the shelf
///
/// \returns: a string (a char pointer)
char *shelf_get_location(shelf *input_shelf);

/// Returns the quantity of the shelf
///
/// \returns: an integer
int shelf_get_quantity(shelf *input_shelf);

/// Sets the location of the shelf to the input location
void shelf_set_location(shelf *input_shelf, char *location);

/// Sets the quantity of the shelf to the input quantity
void shelf_set_quantity(shelf *input_shelf, int quantity);

/// Increments the quantity of the input_shelf
void shelf_increment_quantity(shelf *input_shelf, int increment);

/// Decrements the quantity of the input_shelf
void shelf_decrement_quantity(shelf *input_shelf, int decrement);

/// Shows the content of the input_shelf.
void shelf_show(shelf *input_shelf);

/// Inserts an element to the front of the input_list
void shelves_list_prepend(shelves_list *input_list, void *to_insert);

/// Inserts an element to the back of the input_list
void shelves_list_append(shelves_list *input_list, void *new_data);

/// Removes the first element of the input_list
void shelves_list_top(shelves_list *input_list);

/// Removes the last element of the input_list
void shelves_list_tail(shelves_list *input_list);

/// Checks if the key matches an existing shelf in the input_list, returns true if there is a match, false if not.
///
/// \returns: true if the key matches an existing shelf
bool shelf_already_exists(shelves_list *input_list, char *key);

/// Finds a list_node in the input_list whose shelf has the same location as the input key and returns it. If no list_node was found, the return value is NULL
///
/// \returns: a list_node or NULL
list_node *find_list_node_by_shelf_location(shelves_list *input_list, char *key);

/// Removes the element in the input_list that has the same name as the input key
bool shelves_list_remove_by_location(shelves_list *input_list, char *key);

/// Finds a list_node in the input_list at the same index as the input index and returns it.
///
/// \returns: a list_node or NULL
list_node *find_list_node_by_index(shelves_list *input_list, int index);

/// Removes the element in the input_list that has the same index in the list as the input index
bool shelves_list_remove_by_index(shelves_list *input_list, int index);

/// Shows the contents of the shelves_list.
void shelves_show(shelves_list *input_list, char *flag);

shelf *shelves_list_find_max_shelf_quantity(shelves_list *input_list);

shelves_list *get_enough_shelves(int amount, shelves_list *input_list);

#endif /* shelves_list_h */
