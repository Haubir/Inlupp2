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

/* Creates a new root for a tree */
node **root_new() {
  node **new_root = calloc(1, sizeof(node));
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
  free(to_delete->key);
  free(to_delete);
  
  return true;
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

// TODO!!!!
/* Delete a node from the search tree */
bool tree_node_remove(tree *tree_root, char *key) {
  bool ret = false;
  
  node *to_delete = node_new();

  if (!find_node_in_tree(key, tree_root, to_delete)) {
    ret = false;
  }
  else {
    if (to_delete->left || to_delete->right) tree_rebalance(tree_root, to_delete);
    
    to_delete->left = NULL;
    to_delete->right = NULL;
    to_delete->parent = NULL;
    
    tree_root->size--;
    tree_root->depth--;
    
    ret = true;
  }
  
  node_free(to_delete);
  
  return ret;
}

/* Searches through the tree to find a node that matches the input key. If a node is found, dest_node will point to it when the function is done. */
bool find_node_in_tree(char *find_key, tree *tree_root, node *dest_node) {
  
  if (tree_root == NULL) {
    return false;
  }
  
  node **root_node = tree_root->root;
  
  node *test = find_node_in_tree_aux(find_key, *root_node);
  
  // OBS: Kolla om lösningen nedan är korrekt kodad!!
  if (test) {
    dest_node = test;
    return true;
  }
  else {
    node_free(dest_node);
    return false;
  }
}

/* Auxilliary recursive function for find_node_in_tree that goes through each node to find a node that matches the key */
node *find_node_in_tree_aux(char *key, node *root_node) {
  int comparison = strcmp(key, root_node->key);
  
  if (comparison < 0) { // Betyder att key kommer före root_node->key i alfabetisk ordning
    if (root_node->left) {
      return find_node_in_tree_aux(key, root_node->left);
    }
    else {
      return NULL;
    }
  }
  else if (comparison > 0) { // Betyder att key kommer efter root_node->key i alfabetisk ordning
    if (root_node->right) {
      return find_node_in_tree_aux(key, root_node->right);
    }
    else {
      return NULL;
    }
  }
  else { // Betyder att key == root_node->key
    return root_node;
  }
}

/* Swaps a node that will be changed/deleted with a successor to keep the order in the binary search tree */
bool tree_rebalance(tree *tree_root, node *to_rebalance) {
  node *replacement = to_rebalance;
  
  if (replacement->left) {
    replacement = replacement->left;
    if (replacement->right) {
      while (replacement->right) {
        replacement = replacement->right;
      }
      if (replacement->left) {
        replacement->parent->right = replacement->left; // Steg 1 på tavlan
        replacement->left->parent = replacement->parent; // Steg 2 på tavlan
      }
      
    }
    if (to_rebalance->parent) { // KLAR
      replacement->parent = to_rebalance->parent;
      if (replacement->parent->left == to_rebalance) replacement->parent->left = replacement;
      if (replacement->parent->right == to_rebalance) replacement->parent->right = replacement;
      
      if (to_rebalance->right) {
        replacement->right = to_rebalance->right;
        replacement->right->parent = replacement;
      }
    }
  }
  else if (replacement->right) { // KLAR
    replacement = replacement->right;
    replacement->parent = to_rebalance->parent;
    if (to_rebalance->parent) {
      replacement->parent = to_rebalance->parent;
      if (replacement->parent->left == to_rebalance) replacement->parent->left = replacement;
      if (replacement->parent->right == to_rebalance) replacement->parent->right = replacement;
    }
    
    return true;
  }
  else {
    return false; // We should not even be able to reach this part of the code, since this function should not be activated if to_rebalance does not have any children!
  }
  
  if (to_rebalance->parent) {
    replacement->parent = to_rebalance->parent;
    
    if (replacement->parent->left == to_rebalance) replacement->parent->left = replacement;
    if (replacement->parent->right == to_rebalance) replacement->parent->right = replacement;
  }
  
  if (to_rebalance->right) {
    replacement->right = to_rebalance->right;
    replacement->right->parent = replacement;
  }
  
  // Gammal kod nedan  
  if (replacement->left) {
    replacement->parent->right = replacement->left;
  }
  
  replacement->left = to_rebalance->left;
  replacement->right = to_rebalance->right;
  
  if (to_rebalance->left->parent == to_rebalance) {
    to_rebalance->left->parent = replacement;
  }
  
  if (to_rebalance->right->parent == to_rebalance) {
    to_rebalance->right->parent = replacement;
  }
  
  if (to_rebalance->parent->left == to_rebalance) {
    to_rebalance->parent->left = replacement;
  }
  
  if (to_rebalance->parent->right == to_rebalance) {
    to_rebalance->parent->right = replacement;
  }
  
  replacement->parent = to_rebalance->parent;
  
  return true;
}

/* Finds the smallest subnode in a tree */
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

// Only for development purposes. Tests the ability to create a new tree with a root.
tree *test_add_root() {
  tree *test_tree = tree_new();
  node *test_node = node_new();

  char *node_name = calloc(1024, sizeof(char));
  string_entry("Please type a name for the new node: ", node_name);
  strip_string(node_name);
  
  test_node->key = node_name;  
  
  if (tree_node_add(test_tree, test_node)) {
    printf("A node was successfully added to the tree!\n");
    return test_tree;
  }
  else {
    printf("It was not possible to add a node to the test tree...\n");
    return NULL;
  } 
}

// Only for development purposes. Tests the ability to nodes to a tree.
void test_add_to_tree(tree *target_tree) {
  node *test_node = node_new();
  
  char *node_name = calloc(1024, sizeof(char));
  string_entry("Please type a name for the new node: ", node_name);
  strip_string(node_name);
  
  test_node->key = node_name;  
  
  if (tree_node_add(target_tree, test_node)) {
    printf("A node was successfully added to the tree!\n");
  }
  else {
    printf("It was not possible to add a node to the test tree...\n");
  } 
}

