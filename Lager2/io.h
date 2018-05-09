//
//  io.h
//  Lager2
//
//  Created by Haubir Mariwani on 5/5/18.
//  Copyright © 2018 HauCorp. All rights reserved.
//

#ifndef io_h
#define io_h

#include "tree.h"

tree *preset_tree(void);

void io_list_nodes(tree *input_tree);

tree *test_add_root(char *key);

void io_add_to_tree(tree *input_tree);

void io_increment_shelves(node *input_node, char *shelf_location, char *flag);

/// Checks if the shelf_location follows the correct naming format for shelf locations, and also if the given shelf location is already occupied.
///
/// \returns: true if the shelf is of valid naming format and not occupied, else false
bool io_add_shelves(tree *input_tree, node *input_node, char *shelf_location, char *flag);

void io_remove_node(tree *input_tree);

void io_remove_shelves(tree *input_tree, node *input_node);

void io_input_decrement(shelf *input_shelf, int *decrement);

bool io_choose_shelves(int shelves_size, int *choice);

/// Edits a node in the tree and rebalances the node if necessary
void io_edit_node(tree *input_tree);

/// Edits a node
bool io_node_edit(tree *input_tree, node *input_node);

/// Interface for editing the shelves where the input_ware is located
void io_ware_edit_shelves(tree *input_tree, ware *input_ware);

/// Interface for editing a shelf
void io_edit_shelf(tree *input_tree, shelf *input_shelf);

/// Interface for editing a shelf's quantity
void io_shelf_edit_quantity(shelf *input_shelf);

/// Interface for picking one of the shelves where the input_ware is located
bool io_ware_edit_choose_shelves(int shelves_size, int *choice);

/// Interface for selecting wares from the tree and putting them in a shopping cart
void io_shopping_cart(tree *main_tree, tree *shopping_cart_tree);

/// Lists the contents of the shopping cart
void io_list_shopping_cart(tree *shopping_cart_tree);

/// Interface for picking one of the wares in the tree to put in a shopping cart
bool io_choose_ware(char *input_text, int tree_size, int *choice);

/// Interface for choosing how many of a ware put in a shopping cart
bool io_choose_ware_amount_to_shop(int max_amount, int *choice);

int io_total_price_of_cart(tree *shopping_cart_tree);

void io_total_price_of_cart_aux(node *iter, int *price_ptr);

#endif /* io_h */
