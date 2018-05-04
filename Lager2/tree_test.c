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
  char *root_name = string_new();
  root_name = "e";
  tree *new_tree = test_add_root(root_name);
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
  tree *new_tree = tree_new();
  node *new_node = node_new();
  
  if (ware_name == NULL) {
    ware_name = string_new();
    string_entry("Please type a name for the new ware: ", ware_name);
    strip_string(ware_name);
  }
  ware_set_key(node_get_ware(new_node), ware_name);
  node_set_key(new_node, ware_name);
  
  if (tree_node_add(new_tree, new_node)) {
    printf("A node was successfully added to the tree!\n");
    return new_tree;
  }
  else {
    printf("It was not possible to add a node to the test tree...\n");
    free(ware_name);
    return NULL;
  } 
}

// Only for development purposes. Tests the ability to add nodes to a tree.
void test_add_to_tree(tree *input_tree) {
  char *new_key = string_new();
  string_entry("Skriv ett namn för varan: ", new_key);
  
  if (find_node_in_tree(new_key, input_tree)) {
    node *existing_node = find_node_in_tree(new_key, input_tree);
    printf("%s finns redan i databasen.\n", new_key);
    char *answer = string_new();
    while (true) {
    string_entry("Vill du lägga till fler av varan?", answer);
      if (string_equals(answer, "ja")) {
        test_increment_shelves(input_tree, existing_node);
        break;
      }
      if (string_equals(answer, "nej")) {
        break;
      }
    }
    free(answer);
  }
  else {
    node *new_node = node_new();
    ware_enter_information(node_get_ware(new_node), new_key);
    
    char *shelf_location = string_new();
    
    while (!test_add_shelves(input_tree, shelf_location));
    
    ware *new_ware = node_get_ware(new_node);
    ware_enter_shelves(new_ware, shelf_location);
    
    node_set_key(new_node, ware_get_key(node_get_ware(new_node)));  
    
    if (tree_node_add(input_tree, new_node)) {
      printf("A node was successfully added to the tree!\n");
    }
    else {
      printf("It was not possible to add a node to the tree.....\n");
    }
  }
}

void test_increment_shelves(tree *input_tree, node *input_node) {
  char *shelf_location = string_new();
  int increment = 0;
  int_entry("Hur många styck vill du lägga till?", &increment);
  while (!test_add_shelves(input_tree, shelf_location));
  
  ware *input_ware = node_get_ware(input_node);
  ware_increment_shelves(input_ware, shelf_location, increment);
  ware_increment_amount(input_ware, increment);
}

// Checks if the shelf_location follows the correct naming format for shelf locations, and also if the given shelf location is already occupied.
bool test_add_shelves(tree *input_tree, char *shelf_location) {
  string_entry("Ange den hyllplats som du vill placera varan på: ", shelf_location);  
  
  if (!is_shelf(shelf_location)) {
    printf("'%s' följer inte rätt format för hyllplatsernas namn. Vänligen ange enligt följande format:\n<Bokstav><Siffra><Siffra>\nT.ex: A01, B23 etc.\n", shelf_location);
    return false;
  }
  
  if (find_shelf_in_tree(shelf_location, input_tree)) {
    printf("%s är upptagen, vänligen skriv in en annan hyllplats.\n", shelf_location);
    return false;
  }
  
  return true;
}

// Only for development purposes. Tests the ability to remove a node from a tree.
void test_remove_node(tree *input_tree) {
  node *root_node = *(tree_get_root(input_tree));
  
  if (root_node == NULL) {
    printf("Databasen är tom, det finns inget att ta bort!\n");
    return;
  }
  
  char *node_name = string_new();
  string_entry("Vilken vara vill du ta bort?", node_name);
  strip_string(node_name);
  
  node *to_delete = find_node_in_tree(node_name, input_tree);
  if (to_delete == NULL) {
    printf("Finns ingen vara med det namnet i systemet.\n");
    return;
  }
  node_show(to_delete);
  
  test_decrement_shelves(input_tree, to_delete);
  
  
  
  free(node_name);
}

void test_decrement_shelves(tree *input_tree, node *input_node) {
  ware *input_ware = node_get_ware(input_node);
  shelves_list *input_shelves = ware_get_shelves(input_ware);
  int shelves_size = shelves_list_get_size(input_shelves);
  int decrement = 0;
  
  if (shelves_size > 1) {
    int choice = 0;
    while (!test_remove_shelves(input_node, shelves_size, &choice));
    list_node *to_remove_from = find_list_node_by_index(input_shelves, choice-1);
    shelf *to_decrement = (shelf *) list_node_get_data(to_remove_from);
    while (true) {
      int_entry("Hur många av varan ska tas bort?", &decrement);
      if (decrement > shelf_get_quantity(to_decrement)) printf("Du kan inte ta bort mer än vad som finns på denna hylla, tänk på att du angav %d vilket är mer än %d!\n", decrement, shelf_get_quantity(to_decrement));
      else break;
    }
    
    shelf_decrement_quantity(to_decrement, decrement);
    ware_decrement_amount(input_ware, decrement);
    if (shelf_is_empty(to_decrement)) {
      shelves_list_remove_by_index(input_shelves, choice-1);
    }
  }
  else if (shelves_size == 1) {
    list_node *only_list_node = shelves_list_get_first(input_shelves);
    shelf *to_decrement = (shelf *) list_node_get_data(only_list_node);
    
    while (true) {
      int_entry("Hur många av varan ska tas bort?", &decrement);
      if (decrement > shelf_get_quantity(to_decrement)) printf("Du kan inte ta bort mer än vad som finns på denna hylla, tänk på att du angav %d vilket är mer än %d!\n", decrement, shelf_get_quantity(to_decrement));
      else break;
    }
    
    shelf_decrement_quantity(to_decrement, decrement);
    if (shelf_is_empty(to_decrement)) {
      if (tree_node_remove(input_tree, node_get_key(input_node))) {
        printf("A node was successfully removed from the tree!\n");
      }
      else {
        printf("It was not possible to remove the node from the test tree...\n");
      }
    }
  }
  else {
    printf("test_decrement_shelves(): Tried to decrement nonexisting shelves...");
  }
}

bool test_remove_shelves(node *input_node, int shelves_size, int *choice) {
  int_entry("Vilken hyllplats skall tas bort ifrån?", choice);  
  bool valid_choice = false;
  valid_choice = (*choice >= 1) && (*choice <= shelves_size);
  
  if (!valid_choice) {
    printf("Vänligen skriv en siffra mellan 1-%d för att välja en av hyllplatserna.\n", shelves_size);
    return false;
  } 
  
  return true;
}

// Only for development purposes. Tests the ability to edit a node in the tree, and find a new position for it in the tree if necessary.
void test_edit_node(tree *input_tree) {
  tree_node_edit(input_tree);
}
