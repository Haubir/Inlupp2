//
//  ware.h
//  Lager2
//
//  Created by Haubir Mariwani on 4/25/18.
//  Copyright © 2018 HauCorp. All rights reserved.
//

#ifndef ware_h
#define ware_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "string_op.h"

typedef struct ware ware;

/// Allocates memory for an empty ware
///
/// \returns: an empty ware
ware *ware_new(void);

/// Sets a new key for the ware
void ware_set_key(ware *input_ware, char *key);

/// Sets a new price for the ware
void ware_set_price(ware *input_ware, int price);

/// Sets a new amount for the ware
void ware_set_amount(ware *input_ware, int amount);

/// Increments the amount of the ware
void ware_increment_amount(ware *input_ware, int amount);

/* Sets a new list of shelves for the ware */
//void ware_set_shelves(ware *input_ware, list *shelves);

/// Gets the key of the ware
///
/// \returns: the key
char *ware_get_key(ware *input_ware);

/// Gets the price of the ware
///
/// \returns: the price
int ware_get_price(ware *input_ware);

/// Gets the amount of the ware
/// 
/// \returns: the amount
int ware_get_amount(ware *input_ware);

/* Sets a new list of shelves for the ware */
//list *ware_get_shelves(ware *input_ware);

/// Shows the contents of the ware.
void ware_show(ware *input_ware);

#endif /* ware_h */
