//
//  tree.c
//  Lager2
//
//  Created by Haubir Mariwani on 4/16/18.
//  Copyright © 2018 HauCorp. All rights reserved.
//

#include "tree.h"

struct tree {
  node **root; // Points to the root of the tree
  int size; // The number of nodes in the tree
  int depth; // The depth of the deepest subtree
};

struct node {
  //ware *ware; // Points to the ware
  char *key; // The key decides the position of the node in the search tree
  node *left; // Points to the left child
  node *right; // Points to the right child
  node *parent; // Points to the parent node
};

/* Creates a new tree */
tree *tree_new() {
  tree *new_tree = calloc(1, sizeof(tree));
  node **new_root = root_new();
  
  new_tree->root = new_root;
  new_tree->size = 0;
  new_tree->depth = 0;
  
  return new_tree;
}

/* Returns the size of the tree */
int tree_size(tree *input_tree) {
  return input_tree->size;
}

/* Returns the depth of the tree */
int tree_depth(tree *input_tree) {
  return input_tree->depth;
}

/* Returns the tree root */
node **tree_get_root(tree *input_tree) {
  return input_tree->root;
}

/* Sets the tree root */
void tree_set_root(tree *input_tree, node **new_root) {
  input_tree->root = new_root;
}

/// Shows the nodes of the tree
void tree_list_nodes(tree *input_tree) {
  printf("tree_list_nodes: To be implemented...\n");
}

/* Creates a new root for a tree */
node **root_new() {
  node **new_root = calloc(1, sizeof(node *));
  *new_root = NULL;
  return new_root;
}

/* Creates a new node */
node *node_new() {
  node *new_node = calloc(1, sizeof(node));
  
  //new_node->ware = ware_new();
  new_node->key = NULL;
  new_node->left = NULL;
  new_node->right = NULL;
  new_node->parent = NULL;
  
  return new_node;
}

/* Compares the nodes and returns 0 if they have the same key. */
bool node_equals(node *first, node *second) {
  return string_compare(node_get_key(first), node_get_key(second)) == 0;
}

bool node_has_children(node *input_node) {return (input_node->left || input_node->right);}

char *node_get_key(node *input_node) {
  return input_node->key;
}

void node_set_key(node *input_node, char *new_key) {
  input_node->key = new_key; 
}

node *get_left_node(node *input_node) {
  return input_node->left;
}

void set_left_node(node *input_node, node *new_left) {
  input_node->left = new_left; 
}

node *get_right_node(node *input_node) {
  return input_node->right;
}

void set_right_node(node *input_node, node *new_right) {
  input_node->right = new_right; 
}

node *get_parent_node(node *input_node) {
  return input_node->parent;
}

void set_parent_node(node *input_node, node *new_parent) {
  input_node->parent = new_parent; 
}

/* Copies the source tree into the destination tree */
void tree_copy(tree *destination, tree *source) {
  destination->root = source->root;
  destination->depth = source->depth;
  destination->size = source->size;
  //memcpy(destination, source, sizeof(tree));
  
}

/* Copies the source node into the destination node */
void node_copy(node *destination, node *source) {
  char *dest_key = string_new();
  string_copy(dest_key, node_get_key(source));
  node_set_key(destination, dest_key);
  // ware *dest_ware = ware_new();
  // ware_copy(dest_ware, node_get_ware(source));
  // node_set_ware(destination, dest_ware);
  set_left_node(destination, get_left_node(source));
  set_parent_node(destination, get_parent_node(source));
  set_right_node(destination, get_right_node(source));
  
  //memcpy(destination, source, sizeof(node));
}

/* Free:s up the memory that was allocated for the root */
bool tree_root_free(node **input_root) {
  node *tree_root = *input_root;
  if (!tree_root) {
    return true;
  }
  
  node_free(tree_root);
  
  free(input_root);
  input_root = NULL;
  
  return input_root == NULL;
}


/* Free:s up the memory that was allocated for a node */
bool node_free(node *to_delete) {
  if (!to_delete) {
    return true;
  }
  /*if (to_delete->ware) {
    ware_free(to_delete->ware);
  }*/
  free(to_delete->parent);
  free(to_delete->left);
  free(to_delete->right);
  free(to_delete->key);
  free(to_delete);
  to_delete = NULL;
  
  return to_delete == NULL;
}

/* Calls on tree_node_insert to insert a node to the search tree, and updates the tree:s size and depth attributes if insertion was successful. */
bool tree_node_add(tree *input_tree, node *to_insert) {
  if (*(input_tree->root)) {
    if (tree_node_insert(*(input_tree->root), to_insert)) {
      input_tree->size++;
      input_tree->depth++;
      return true;
    }
    else {
      printf("Error: Det finns redan en vara med detta namn. Vänligen välj ett annat namn. \n");
      return false;
    }
  }
  else {
    *(input_tree->root) = calloc(1, sizeof(node));
    node *root_node = *(input_tree->root);
    node_copy(root_node, to_insert);
    free(to_insert);
    input_tree->size++;
    input_tree->depth++;
    return true;
  }
}

/* Add a node into the search tree in the right order */
bool tree_node_insert(node *start, node *to_insert) {
  int comparison = string_compare(start->key, to_insert->key);
  
  if (comparison < 0) {
    if (start->right) {
      return tree_node_insert(start->right, to_insert);
    }
    else {
      start->right = to_insert;
      to_insert->parent = start;
      return true;
    }
  }
  else if (comparison > 0) {
    if (start->left) {
      return tree_node_insert(start->left, to_insert);
    }
    else {
      start->left = to_insert;
      to_insert->parent = start;
      return true;
    }
  }
  else {
    return false;
  }
}

bool tree_remove_root(tree *input_tree) {
  tree_root_free(input_tree->root);
  
  input_tree->root = NULL;
  input_tree->size--;
  input_tree->depth--;
  
  return true;
}


/* Delete a node from the search tree */
bool tree_node_remove(tree *input_tree, char *key) {
  if (!tree_get_root(input_tree)) return false;
  
  node *tree_root = *(tree_get_root(input_tree));
  
  if (tree_root == NULL) {
    printf("Attempted tree to delete from was NULL.\n");
    return false;
  }
  
  node *to_delete = find_node_in_tree(key, input_tree);
  
  if (!to_delete) return false; // The node to delete was not found
  else {
    if (node_has_children(to_delete)) tree_rebalance(input_tree, to_delete);
    if (to_delete->parent) {
      if (to_delete->parent->left == to_delete) to_delete->parent->left = NULL;
      if (to_delete->parent->right == to_delete) to_delete->parent->right = NULL;
    }
    to_delete->left = NULL;
    to_delete->right = NULL;
    to_delete->parent = NULL;
    
    input_tree->size--;
    input_tree->depth--;
    
    if (!node_free(to_delete)) {
      printf("The node was successfully removed from the tree but not free:d...\n");
      return false;
    }
    else return true;
  }
}

/* Searches through the tree to find a node that matches the input key. If a node is found, dest_node will point to it when the function is done. */
node *find_node_in_tree(char *find_key, tree *input_tree/*, node *dest_node*/) {
  
  if (*(input_tree->root) == NULL) return false;
  
  node **root_node = input_tree->root;
  node *test = find_node_in_tree_aux(find_key, *root_node);
  
  return test;
}

/* Auxilliary recursive function for find_node_in_tree that goes through each node to find a node that matches the key */
node *find_node_in_tree_aux(char *key, node *start_node) {
  int comparison = strcmp(key, start_node->key);
  
  if (comparison < 0) { // Betyder att key kommer före start_node->key i alfabetisk ordning
    if (start_node->left) {
      return find_node_in_tree_aux(key, start_node->left);
    }
    else {
      return NULL;
    }
  }
  else if (comparison > 0) { // Betyder att key kommer efter start_node->key i alfabetisk ordning
    if (start_node->right) {
      return find_node_in_tree_aux(key, start_node->right);
    }
    else {
      return NULL;
    }
  }
  else { // Betyder att key == start_node->key
    return start_node;
  }
}

/* Handles the rebalancing of the tree when the node that is to be deleted is the root node of the tree. */
void tree_rebalance_root_shift(tree *input_tree, node *replacement) {
  node **tree_root = input_tree->root;
  node *root_node = *tree_root;
  
  if (root_node->left) { 
    if (root_node->left == replacement) root_node->left = NULL;
    else tree_rebalance_left_child_shift(replacement, root_node);
  }
  if (root_node->right) {
    if (root_node->right == replacement) root_node->right = NULL;
    else tree_rebalance_right_child_shift(replacement, root_node);
  }
  if (replacement->parent) { 
    if (replacement->parent->right == replacement) replacement->parent->right = NULL;
    if (replacement->parent->left == replacement) replacement->parent->left = NULL;
    replacement->parent = NULL;
  }
  
  *tree_root = replacement;  
}

/* Swaps a node that will be changed/deleted with a successor to keep the order in the binary search tree */
bool tree_rebalance(tree *input_tree, node *to_rebalance) {
  node *tree_root = *(input_tree->root);
  bool ret = false;
  node *replacement = to_rebalance;
  
  if (replacement->left) {
    replacement = replacement->left;
    
    if (replacement->right) {
      while (replacement->right) {
        replacement = replacement->right;
      }
      if (replacement->left) {
        replacement->parent->right = replacement->left;
        replacement->left->parent = replacement->parent;
      }
      
      if (node_equals(to_rebalance, tree_root)) tree_rebalance_root_shift(input_tree, replacement);
      else {
        if (replacement->parent->left == replacement) replacement->parent->left = NULL;
        if (replacement->parent->right == replacement) replacement->parent->right = NULL;
        tree_rebalance_parent_shift(replacement, to_rebalance);
        tree_rebalance_left_child_shift(replacement, to_rebalance);
        if (to_rebalance->right) tree_rebalance_right_child_shift(replacement, to_rebalance);
      }
    } 
    else {
      if (node_equals(to_rebalance, tree_root)) tree_rebalance_root_shift(input_tree, replacement);
      else {
        if (to_rebalance->parent) tree_rebalance_parent_shift(replacement, to_rebalance);
        if (to_rebalance->right) tree_rebalance_right_child_shift(replacement, to_rebalance);
      }
    }
    
    ret = true;
  }
  else if (replacement->right) {
    replacement = replacement->right;
    if (node_equals(to_rebalance, tree_root)) tree_rebalance_root_shift(input_tree, replacement);
    else {
      if (to_rebalance->parent) tree_rebalance_parent_shift(replacement, to_rebalance);
    }
    ret = true;
  }
  else {
    printf("Error: tree_rebalance activated despite the fact that to_rebalance does not have any children!!\n");
    ret = false; // We should not even be able to reach this part of the code, since this function should not be activated if to_rebalance does not have any children!
  }
  
  return ret;
}

/* Shifts the replacement node to the to_rebalance node's position under the parent of to_rebalance. All pointers are correctly shifted. */
void tree_rebalance_parent_shift(node *replacement, node *to_rebalance) {
  replacement->parent = to_rebalance->parent;
  if (replacement->parent->left == to_rebalance) {
    replacement->parent->left = replacement; 
    return;
  }
  if (replacement->parent->right == to_rebalance) replacement->parent->right = replacement;
}

/* Shifts the replacement node to the to_rebalance node's position over the right child of to_rebalance. All pointers are correctly shifted. */
void tree_rebalance_right_child_shift(node *replacement, node *to_rebalance) {
  replacement->right = to_rebalance->right;
  replacement->right->parent = replacement;
}

/* Shifts the replacement node to the to_rebalance node's position over the left child of to_rebalance. All pointers are correctly shifted. */
void tree_rebalance_left_child_shift(node *replacement, node *to_rebalance) {
  replacement->left = to_rebalance->left; 
  replacement->left->parent = replacement; 
}

/* Edits a node in the tree and rebalances the node if necessary */
bool tree_node_edit(tree *input_tree) {
  if (!tree_get_root(input_tree)) return false;
  
  node *tree_root = *(tree_get_root(input_tree));
  
  if (tree_root == NULL) {
    printf("There are no nodes in the tree to edit...\n");
    return false;
  }
  
  tree_list_nodes(input_tree);
  
  char *key = string_new();
  string_entry("Skriv namnet på varan som du önskar att redigera:", key);
  node *to_edit = find_node_in_tree(key, input_tree);
  free(key);
  
  if (!to_edit) {
    printf("The node to edit was not found in the tree...\n");
    return false; // The node to edit was not found
  }
  else {    
    node *copy_of_edited = node_new();
    node_copy(copy_of_edited, to_edit);
    // Fortsätt här. Nyckeln verkar inte lagras på rätt sätt i copy_of_edited. Måste fixas innan nästa steg!
    
    copy_of_edited->left = NULL;
    copy_of_edited->right = NULL;
    copy_of_edited->parent = NULL;
    
    tree_node_remove(input_tree, node_get_key(to_edit));
    
    if (node_edit(copy_of_edited)) tree_node_add(input_tree, copy_of_edited);
    else node_free(copy_of_edited);
  }
  
  return true;
}

// TODO!!!
/// - Först ska nodens info visas på skärmen.
/// - Sedan ska användaren få välja vilket attribut den vill ändra
///
/// \returns: true
bool node_edit(node *input_node) {
  char *answer = string_new();
  
  printf("Vill du redigera varan?\nDitt svar: ");
  while(string_compare(answer, "j") != 0 && string_compare(answer, "n") != 0){
    string_entry("Svara 'j' för ja, 'n' för nej.", answer);
  }
  
  if (string_compare(answer, "n") == 0){
    free(answer);
    return false;
  }
  
  node_show(input_node);
  string_entry("Svara med 1-4 för att välja ett av alternativen eller skriv \"avsluta\" för att avsluta och återvända till huvudmenyn.\n1: Redigera namn\n2: Redigera beskrivning\n3: Redigera pris\n4: Redigera hyllplats(er)", answer);
  while ((string_compare(answer, "1") != 0) &&
         (string_compare(answer, "2") != 0) &&
         (string_compare(answer, "3") != 0) &&
         (string_compare(answer, "4") != 0) &&
         (string_compare(answer, "avsluta") != 0)) {
    string_entry("Svara med 1-4 för att välja ett av alternativen eller skriv \"avsluta\" för att avsluta och återvända till huvudmenyn.", answer);
    
    if (string_compare(answer, "avsluta") == 0) {
      string_entry("Är du säker på att du vill avsluta?\n(J/j) för ja, (N/n) för nej.", answer);
      
      if (string_compare(answer, "j") == 0) {
        printf("Du har valt att avsluta.\n");
        free(answer);
        return false;
      }
    }
  }
  
  switch (string_to_int(answer)) {
    case 1:
      node_name_edit(input_node);
      break;
      
    case 2:
      //ware_description_edit(input_node->ware);
      break;
      
    case 3:
      //ware_price_edit(input_node->ware);
      break;
      
      /*    case 4:
       ware_amount_edit(input_node->ware);
       break;*/
      
    case 4:
      //ware_shelves_edit(input_node->ware);
      break;
      
    default:
      break;
  }
  
  free(answer);
  return true;
}

/// Shows information about a node
void node_show(node *input_node) {
  if (input_node) {
    printf("Namn: %s\n", input_node->key);
    //printf("Description: %s\n", ware_get_description(input_node->ware));
    //printf("Price: %d\n", ware_get_price(input_node->ware));
    //printf("Amount: %d\n", ware_get_amount(input_node->ware));
    //node_show_shelves_list(input_node);
  }
}

void node_name_edit(node *input_node) {
  char *answer = string_new();
  string_entry("Skriv ett nytt namn för varan:", answer);
  
  free(node_get_key(input_node));
  node_set_key(input_node, NULL);
  node_set_key(input_node, answer);

  //ware_set_name(to_edit->ware, to_edit->key);
}

/*
/// Shows information about the shelves of a node's shelf-list

void node_show_shelves_list(node *input_node) {
  if (!ware_get_shelves_list(input_node->ware)) {
    printf("Det finns ingen lista kaka, vad är de du försöker printa haa?\n");
    return;
  }
  
  printf("%s is in the following shelves: \n", input_node->key);
  
  list_node *iter = list_get_first(ware_get_shelves_list(input_node->ware));
  
  while(iter) {
    void *iter_data = list_node_get_data(iter);
    shelf_t *shelf_iter = (shelf_t *)iter_data;
    printf("%s: %d pc\n", shelf_get_location(shelf_iter), shelf_get_quantity(shelf_iter));
    iter = list_node_get_next(iter);
  }
} */

/* OBS! Behövs kanske inte!! Finds the smallest subnode in a tree */
node *find_smallest_node(node *start) {
  node *iter = start;
  
  if (iter->left) {
    iter = iter->left;
    while (iter->right) {
      iter = iter->right;
    }
  }
  
  return iter;
}

