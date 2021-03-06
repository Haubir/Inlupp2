//
//  ware.h
//  Lager2
//
//  Created by Haubir Mariwani on 4/25/18.
//  Copyright © 2018 HauCorp. All rights reserved.
//

#ifndef ware_h
#define ware_h

#include "shelves_list.h"

typedef struct ware ware;

/// Allocates memory for an empty ware
///
/// \returns: an empty ware
ware *ware_new(void);

/// Free:s up the memory that was allocated for a ware
///
/// \returns: true if ware was successfully deleted
bool ware_free(ware *to_delete);

/// Copies the source ware into the destination ware
void ware_copy(ware *destination, ware *source);

/// Sets a new key for the ware
void ware_set_key(ware *input_ware, char *key);

/// Sets a new description for the ware
void ware_set_description(ware *input_ware, char *description);

/// Sets a new price for the ware
void ware_set_price(ware *input_ware, int price);

/// Sets a new amount for the ware
void ware_set_amount(ware *input_ware, int amount);

/// Increments the amount of the ware
void ware_increment_amount(ware *input_ware, int amount);

/// Decrements the amount of the ware
void ware_decrement_amount(ware *input_ware, int amount);

/// Updates the amount of the ware by recounting the quantities of the shelves in the shelves_list 
void ware_update_amount(ware *input_ware);

/* Sets a new list of shelves for the ware */
void ware_set_shelves(ware *input_ware, shelves_list *shelves);

/// Gets the key of the ware
///
/// \returns: the key
char *ware_get_key(ware *input_ware);

/// Returns the description for the ware
///
/// \returns: the description
char *ware_get_description(ware *input_ware);

/// Gets the price of the ware
///
/// \returns: the price
int ware_get_price(ware *input_ware);

/// Gets the amount of the ware
/// 
/// \returns: the amount
int ware_get_amount(ware *input_ware);

/* Returns the list of shelves for the ware */
shelves_list *ware_get_shelves(ware *input_ware);

/// Shows the contents of the ware.
void ware_show(ware *input_ware);

/// Add information to the ware, such as name, price, amount and locations.
void ware_enter_information(ware *input_ware, char *new_key);

/// Add shelf locations for the ware.
void ware_enter_shelves(ware *input_ware, char *shelf_location);

/// Increments the amount of the ware by adding amounts of it to a new shelf.
void ware_increment_shelves(ware *input_ware, char *shelf_location, int increment);

/// Edit the key of the input_ware
void ware_edit_name(ware *input_ware);

/// Edit the description of the input_ware
void ware_edit_description(ware *input_ware);

/// Edit the price of the input_ware
void ware_edit_price(ware *input_ware);

#endif /* ware_h */
