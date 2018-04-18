//
//  tree_test.c
//  Lager2
//
//  Created by Haubir Mariwani on 4/18/18.
//  Copyright © 2018 HauCorp. All rights reserved.
//

#include "tree_test.h"
/* ---------------------------------------------------------------------- TEST CODE BELOW ---------------------------------------------------------------------------------- */

// Only for development purposes. Tests the ability to create a new tree with a root.
tree *test_add_root() {
  tree *test_tree = tree_new();
  node *test_node = node_new();
  
  char *node_name = calloc(1024, sizeof(char));
  string_entry("Please type a name for the new node: ", node_name);
  strip_string(node_name);
  
  node_set_key(test_node, node_name);  
  
  if (tree_node_add(test_tree, test_node)) {
    printf("A node was successfully added to the tree!\n");
    return test_tree;
  }
  else {
    printf("It was not possible to add a node to the test tree...\n");
    free(node_name);
    return NULL;
  } 
}

// Only for development purposes. Tests the ability to add nodes to a tree.
void test_add_to_tree(tree *target_tree) {
  node *test_node = node_new();
  
  char *node_name = calloc(1024, sizeof(char));
  string_entry("Please type a name for the new node: ", node_name);
  strip_string(node_name);
  
  node_set_key(test_node, node_name);  
  
  if (tree_node_add(target_tree, test_node)) {
    printf("A node was successfully added to the tree!\n");
  }
  else {
    printf("It was not possible to add a node to the test tree...\n");
    free(node_name);
  } 
}

// Only for development purposes. Tests the ability to remove a node from a tree.
void test_remove_node(tree *input_tree) {
  char *node_name = calloc(1024, sizeof(char));
  string_entry("Please type the name of the node that you wish to delete: ", node_name);
  strip_string(node_name);
  
  if (tree_node_remove(input_tree, node_name)) {
    printf("A node was successfully removed from the tree!\n");
  }
  else {
    printf("It was not possible to remove the node from the test tree...\n");
  }
  
  free(node_name);
}
