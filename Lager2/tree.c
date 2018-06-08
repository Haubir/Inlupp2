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
  ware *ware; // Points to the ware
  char *key; // The key decides the position of the node in the search tree
  node *left; // Points to the left child
  node *right; // Points to the right child
  node *parent; // Points to the parent node
};

/* Creates a new tree */
tree *tree_new() {
  tree *new_tree = calloc(1, sizeof(tree));
  node **new_root = root_new(); // TODO!!! Ska inte allokera minne för en rot förrän det finns en nod att sätta in i roten. Allokeringen ska göras i io.c eller tree_node_add() istället för här hursomhelst.
  
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

/* Shows the nodes of the tree */
void tree_list_nodes(tree *input_tree, char *flag) {
  node **root_pointer = tree_get_root(input_tree);
  node *root_node = *root_pointer;
  if (!root_node) {
    printf("Det finns inga varor i databasen.\n\n\n");
    return;
  }
  int count = 1;
  
  tree_list_nodes_aux(root_node, &count, flag);
 
  printf("\n");
}

/* Auxilliary function for tree_list_nodes, that traverses through the tree and prints information about all the nodes in the tree */
void tree_list_nodes_aux(node *iter, int *count_ptr, char *flag) {
  if (iter->left) tree_list_nodes_aux(iter->left, count_ptr, flag);
  if (string_equals(flag, "database")) printf("%d. %s\n", *count_ptr, iter->key);
  if (string_equals(flag, "shopping")) printf("%d. %s (%d st.)\n", *count_ptr, iter->key, ware_get_amount(node_get_ware(iter)));
  (*count_ptr)++;
  if (iter->right) tree_list_nodes_aux(iter->right, count_ptr, flag);
}

/* Creates a new root for a tree */
node **root_new() {
  node **new_root = calloc(1, sizeof(node *));
  
  return new_root;
}

/* Creates a new node */
node *node_new() {
  node *new_node = calloc(1, sizeof(node));
  
  new_node->ware = ware_new();
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

ware *node_get_ware(node *input_node) {
  return input_node->ware;
}

void node_set_ware(node *input_node, ware *new_ware) {
  input_node->ware = new_ware; 
}

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
  /*node *source_root = *(source->root);
  node *dest_root = *(destination->root);
  node_copy(dest_root, source_root);
  
  tree_copy_aux(dest_root, source_root);
  */
  destination->root = source->root;
  destination->depth = source->depth;
  destination->size = source->size;
  //memcpy(destination, source, sizeof(tree));
  
}

/* Copies the source node into the destination node */
void node_copy(node *destination, node *source) {
  ware *dest_ware = ware_new();
  ware_copy(dest_ware, node_get_ware(source));
  node_set_ware(destination, dest_ware);
  char *ware_key = ware_get_key(dest_ware);
  node_set_key(destination, ware_key);
  
  set_left_node(destination, get_left_node(source));
  set_parent_node(destination, get_parent_node(source));
  set_right_node(destination, get_right_node(source));
  
  //memcpy(destination, source, sizeof(node));
}

/*  This function traverses tree in post order to 
    to delete each and every node of the tree */
void tree_destroy_aux(node *to_delete) 
{
    if (to_delete == NULL) return;
 
    /* first delete both subtrees */
    tree_destroy_aux(node->left);
    tree_destroy_aux(node->right);
   
    /* then delete the node */
    printf("\n Deleting node: %s", to_delete->key);
    node_free(to_delete);
} 

void tree_destroy(tree *input_tree) {
  node **tree_root = input_tree->root;
  node *root_node = *tree_root;
  
  tree_destroy_aux(root_node);
  
  tree_root_free(tree_root); // Testa detta, kanske inte funkar!
  // Om ovan ej funkade:
  free(input_tree->root);
  free(tree);
}

/* Free:s up the memory that was allocated for the root */
bool tree_root_free(node **input_root) {
  if (!*(input_root)) {
    return true;
  }
  
  node_free(*input_root);
  *input_root = NULL;
  bool ret = *input_root == NULL;
  
  return ret;
}

/* Free:s up the memory that was allocated for a node */
bool node_free(node *to_delete) {
  if (!to_delete) {
    return true;
  }
  if (to_delete->ware) {
    ware_free(to_delete->ware);
    to_delete->ware = NULL;
  }
  to_delete->parent = NULL;
  to_delete->left = NULL;
  to_delete->right = NULL;
  free(to_delete);
  to_delete = NULL;
  
  bool ret = to_delete == NULL;
  
  return ret;
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
      return false;
    }
  }
  else {
    *(input_tree->root) = to_insert;
    
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

/* Removes the root of the input_tree */
bool tree_remove_root(tree *input_tree) {
  tree_root_free(input_tree->root);
  
  *(input_tree->root) = NULL;
  input_tree->size--;
  input_tree->depth--;
  
  return true;
}

/* Delete a node from the search tree */
bool tree_node_remove(tree *input_tree, char *key) {
  if (!tree_get_root(input_tree)) return false;
  
  node *root_node = *(tree_get_root(input_tree));
  
  if (root_node == NULL) {
    printf("Attempted tree to delete from was NULL.\n");
    return false;
  }
  
  node *to_delete = find_node_in_tree(key, input_tree);
  
  if (!to_delete) return false; // The node to delete was not found
  else if (node_equals(root_node, to_delete) && !node_has_children(root_node)) {
    return tree_remove_root(input_tree); // The node to_delete is the root node and the root node is the only node in the tree 
  }
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
  
  if (*(input_tree->root) == NULL) return NULL;
  if (string_equals(find_key, "") || find_key == NULL) return NULL;
  node **root_node = input_tree->root;
  node *test = find_node_in_tree_aux(find_key, *root_node);
  
  return test;
}

/* Auxilliary recursive function for find_node_in_tree that goes through each node to find a node that matches the key */
node *find_node_in_tree_aux(char *key, node *start_node) {
  int comparison = string_compare(key, start_node->key);
  
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

/// Searches through the tree to find a node whose index matches the input index. If a node is found, it is returned. Eitherwise NULL is returned. */
node *find_node_by_index(tree *input_tree, int index) {
  if (*(input_tree->root) == NULL) return NULL;
  if (index > input_tree->size) {
    printf("find_node_by_index(): Index out of bounds.\n");
    return NULL;
  }
  
  int count = 1;
  node *root_node = *(input_tree->root);
  node *to_return = calloc(1, sizeof(node *));
  find_node_by_index_aux(root_node, index, &count, &to_return);
  
  
  return to_return;
}

void find_node_by_index_aux(node *iter, int index, int *count_ptr, node **dest_node_ptr) {
  
  if (iter->left) find_node_by_index_aux(iter->left, index, count_ptr, dest_node_ptr);
  if ((*count_ptr) == index) *dest_node_ptr = iter;
  (*count_ptr)++;
  if (iter->right) find_node_by_index_aux(iter->right, index, count_ptr, dest_node_ptr);
}

/* Searches through the tree to find a node that matches the input key. If a node is found, dest_node will point to it when the function is done. */
bool find_shelf_in_tree(char *key, tree *input_tree/*, node *dest_node*/) {
  node **root_pointer = tree_get_root(input_tree);
  node *root_node = *root_pointer;
  if (!root_node) {
    return false;
  }
  
  if (!node_has_children(root_node)) {
    ware *root_ware = root_node->ware;
    shelves_list *root_shelves = ware_get_shelves(root_ware);
    return shelf_already_exists(root_shelves, key);
  }
  
  return find_shelf_in_tree_aux(key, root_node);
}

/* Auxilliary recursive function for find_shelf_in_tree that goes through each node to find a shelf that matches the key */
bool find_shelf_in_tree_aux(char *key, node *iter) {
  ware *iter_ware = iter->ware;
  shelves_list *iter_shelves = ware_get_shelves(iter_ware);
  
  if (iter->left && find_shelf_in_tree_aux(key, iter->left)) return true;
  
  if (shelf_already_exists(iter_shelves, key)) return true;
  
  if (iter->right && find_shelf_in_tree_aux(key, iter->right)) return true;
  
  return false;
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

/// Shows information about a node
void node_show(node *input_node) {
  if (input_node) {
    ware_show(input_node->ware);
    printf("-----------------------------------\n");
  }
}

/* Edits the node's name */
void node_name_edit(node *input_node) {
  ware_edit_name(input_node->ware);
  node_set_key(input_node, ware_get_key(input_node->ware));
}
