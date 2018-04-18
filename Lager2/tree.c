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
node **get_root(tree *input_tree) {
  return input_tree->root;
}

/* Sets the tree root */
void set_root(tree *input_tree, node **new_root) {
  input_tree->root = new_root;
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

char *get_key(node *input_node) {
  return input_node->key;
}

void set_key(node *input_node, char *new_key) {
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
  memcpy(destination, source, sizeof(tree));
}

/* Copies the source node into the destination node */
void node_copy(node *destination, node *source) {
  memcpy(destination, source, sizeof(node));
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
bool tree_node_add(tree *target_tree, node *to_insert) {
  if (*(target_tree->root)) {
    if (tree_node_insert(*(target_tree->root), to_insert)) {
      target_tree->size++;
      target_tree->depth++;
      return true;
    }
    else {
      printf("Error: Det finns redan en vara med detta namn. Vänligen välj ett annat namn. \n");
      return false;
    }
  }
  else {
    *(target_tree->root) = calloc(1, sizeof(node));
    node *tree_root = *(target_tree->root);
    node_copy(tree_root, to_insert);
    target_tree->size++;
    target_tree->depth++;
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

// TODO!!! Noder tas bort random. Ibland funkar det, ibland inte. Fortsätt härifrån.
/* Delete a node from the search tree */
bool tree_node_remove(tree *input_tree, char *key) {
  if (*(input_tree->root) == NULL) {
    printf("Attempted tree to delete from was NULL.\n");
    return false;
  }

  node *to_delete = find_node_in_tree(key, input_tree);
  
  if (!to_delete) return false; // The node to delete was not found
  
  else {
    if (to_delete->left || to_delete->right) tree_rebalance(input_tree, to_delete);
    
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
  
  if (*(input_tree->root) == NULL) {
    return false;
  }
  
  node **root_node = input_tree->root;
  node *test = find_node_in_tree_aux(find_key, *root_node);
  
  return test;
  
  // OBS: Kolla om lösningen nedan är korrekt kodad!!
  /*if (test) {
    dest_node = test;
    return true;
  }
  else {
    node_free(dest_node);
    return false;
    return NULL;
  }*/
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

/* Swaps a node that will be changed/deleted with a successor to keep the order in the binary search tree */
bool tree_rebalance(tree *tree_root, node *to_rebalance) {
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
      tree_rebalance_parent_shift(replacement, to_rebalance);
      tree_rebalance_left_child_shift(replacement, to_rebalance);
      if (to_rebalance->right) tree_rebalance_right_child_shift(replacement, to_rebalance);
    }
    else {
      if (to_rebalance->parent) tree_rebalance_parent_shift(replacement, to_rebalance);
      if (to_rebalance->right) tree_rebalance_right_child_shift(replacement, to_rebalance);
    }
    
    ret = true;
  }
  else if (replacement->right) {
    replacement = replacement->right;
    if (to_rebalance->parent) tree_rebalance_parent_shift(replacement, to_rebalance);
    
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
  if (replacement->parent->left == to_rebalance) {replacement->parent->left = replacement; return;}
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

