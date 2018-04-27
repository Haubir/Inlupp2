//
//  tree_test.c
//  Lager2
//
//  Created by Haubir Mariwani on 4/18/18.
//  Copyright © 2018 HauCorp. All rights reserved.
//

#include "tree_test.h"
/* ---------------------------------------------------------------------- TEST CODE BELOW ---------------------------------------------------------------------------------- */

// Only for development purposes. Creates a new tree with 7 nodes. 
tree *preset_tree() {
  tree *new_tree = test_add_root("e");
  node **tree_root = tree_get_root(new_tree);
  node *root_node = *tree_root;
  
  char *root_description = string_new();
  root_description = "The letter e.";
  int root_price = 23;
  int root_amount = 8;
  
  ware_set_description(node_get_ware(root_node), root_description);
  ware_set_price(node_get_ware(root_node), root_price);
  ware_set_amount(node_get_ware(root_node), root_amount);
  
  char *list[6] = {"o", "j", "m", "g", "f", "h"};
  char *key_list[6];
  for (int i = 0; i < 6; i++) {
    char *new_key = string_new();
    strncpy(new_key, list[i], (size_t) string_length(list[i]));
    key_list[i] = new_key;
  }
  
  char *descript[6] = {"The letter o.", "The letter j.", "The letter m.", "The letter g.", "The letter f.", "The letter h."};
  char *description_list[6];
  for (int i = 0; i < 6; i++) {
    char *new_description = string_new();
    strncpy(new_description, descript[i], (size_t) string_length(descript[i]));
    description_list[i] = new_description;
  }
  
  int prices[6] = {4, 17, 99, 3, 2, 47};
  int amounts[6] = {1, 3, 7, 10, 2, 5};
  
  for (int i = 0; i < 6; i++) { 
    node *new_node = node_new();
    ware_set_key(node_get_ware(new_node), key_list[i]);
    ware_set_description(node_get_ware(new_node), description_list[i]);
    ware_set_price(node_get_ware(new_node), prices[i]);
    ware_set_amount(node_get_ware(new_node), amounts[i]);
    node_set_key(new_node, key_list[i]);
    tree_node_add(new_tree, new_node);
  }
  
  return new_tree;
}

// Only for development purposes. Tests the ability to create a new tree with a root.
tree *test_add_root(char *ware_name) {
  tree *test_tree = tree_new();
  node *test_node = node_new();
  
  if (ware_name == NULL) {
    ware_name = string_new();
    string_entry("Please type a name for the new ware: ", ware_name);
    strip_string(ware_name);
  }
  ware_set_key(node_get_ware(test_node), ware_name);
  node_set_key(test_node, ware_name);
  
  if (tree_node_add(test_tree, test_node)) {
    printf("A node was successfully added to the tree!\n");
    return test_tree;
  }
  else {
    printf("It was not possible to add a node to the test tree...\n");
    free(ware_name);
    return NULL;
  } 
}

// Only for development purposes. Tests the ability to add nodes to a tree.
void test_add_to_tree(tree *input_tree) {
  node *test_node = node_new();
  
  /*char *ware_name = string_new();
  char *ware_description = string_new();
  int ware_price = 0;
  int ware_amount = 0;
  
  string_entry("Vänligen skriv varans namn: ", ware_name);
  string_entry("Beskriv varan, så tydligt som möjligt: ", ware_description);
  int_entry("Vänligen skriv in varans pris: ", &ware_price);
  int_entry("Ange hur många av varan som ska lagras: ", &ware_amount);
  
  strip_string(ware_name);
  strip_string(ware_description);
  
  ware_set_key(node_get_ware(test_node), ware_name);
  ware_set_description(node_get_ware(test_node), ware_description);
  ware_set_price(node_get_ware(test_node), ware_price);
  ware_set_amount(node_get_ware(test_node), ware_amount); */
  ware_enter_information(node_get_ware(test_node));
  node_set_key(test_node, ware_get_key(node_get_ware(test_node)));  
  
  if (tree_node_add(input_tree, test_node)) {
    printf("A node was successfully added to the tree!\n");
  }
  else {
    printf("It was not possible to add a node to the test tree...\n");
    //free(ware_name);
  } 
}

// Only for development purposes. Tests the ability to remove a node from a tree.
void test_remove_node(tree *input_tree) {
  char *node_name = string_new();
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

// Only for development purposes. Tests the ability to edit a node in the tree, and find a new position for it in the tree if necessary.
void test_edit_node(tree *input_tree) {
  tree_node_edit(input_tree);
}
