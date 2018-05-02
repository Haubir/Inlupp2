//
//  tree_test.h
//  Lager2
//
//  Created by Haubir Mariwani on 4/18/18.
//  Copyright © 2018 HauCorp. All rights reserved.
//

#ifndef tree_test_h
#define tree_test_h

#include "tree.h"


/* ---------------------------------------------------------------------- TEST CODE BELOW ---------------------------------------------------------------------------------- */

tree *preset_tree(void);

tree *test_add_root(char *key);

void test_add_to_tree(tree *input_tree);

void test_increment_shelves(tree *input_tree, node *input_node);

/// Checks if the shelf_location follows the correct naming format for shelf locations, and also if the given shelf location is already occupied.
///
/// \returns: true if the shelf is of valid naming format and not occupied, else false
bool test_add_shelves(tree *input_tree, char *shelf_location);

void test_remove_node(tree *input_tree);

void test_edit_node(tree *input_tree);

#endif /* tree_test_h */
