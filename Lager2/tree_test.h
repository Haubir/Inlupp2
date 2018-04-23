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

void test_remove_node(tree *input_tree);

void test_edit_node(tree *input_tree);

#endif /* tree_test_h */
