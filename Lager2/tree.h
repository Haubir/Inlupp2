//
//  tree.h
//  Lager2
//
//  Created by Haubir Mariwani on 4/16/18.
//  Copyright © 2018 HauCorp. All rights reserved.
//

#ifndef tree_h
#define tree_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "string_op.h"

typedef struct tree tree;

typedef struct node node;

/// Creates a new tree
///
/// \returns: empty tree
tree *tree_new(void);

/// Get the size of the tree
///
/// \returns: the number of nodes in the tree
int tree_size(tree *tree);

/// Get the depth of the tree
///
/// \returns: the depth of the deepest subtree
int tree_depth(tree *tree);

/// Get the root of the tree 
///
/// \returns: the root of the tree
node **tree_get_root(tree *input_tree);

/// Sets the tree root 
void tree_set_root(tree *input_tree, node **new_root);

/// Creates a new root 
///
/// \returns: a root
node **root_new(void);

/// Creates a new node
///
/// \returns: a empty node with an empty ware assigned to it
node *node_new(void);

/// Compares the nodes and returns 0 if they have the same key.
///
/// \returns: true if the input nodes have the same key
bool node_equals(node *first, node *second);

/// Checks if the input_node has any children
///
/// \returns: true if the node has any children
bool node_has_children(node *input_node);

/// Get the key of the input_node
///
/// \returns: the key
char *node_get_key(node *input_node);

/// Set the key of the input_node to the new_key
void node_set_key(node *input_node, char *new_key);

/// Get the left node of the input_node
///
/// \returns: the left node
node *get_left_node(node *input_node);

/// Set the left node of the input_node to the new_left
void set_left_node(node *input_node, node *new_left);

/// Get the right node of the input_node
///
/// \returns: the right node
node *get_right_node(node *input_node);

/// Set the right node of the input_node to the new_right
void set_right_node(node *input_node, node *new_right);

/// Get the parent node of the input_node
///
/// \returns: the parent node
node *get_parent_node(node *input_node);

/// Set the parent node of the input_node to the new_parent
void set_parent_node(node *input_node, node *new_parent);

/// Copies a tree into another tree
void tree_copy(tree *destination, tree *source);

/// Copies a node into another node
void node_copy(node *destination, node *source);

/// Calls on tree_node_insert to insert a node to the search tree, and updates the tree:s size and depth attributes if insertion was successful.
///
/// \returns: true if insertion was completed successfully
bool tree_node_add(tree *tree_root, node *to_insert);

/// Add a node into the search tree in the right order
///
/// \returns: true if insertion was completed successfully
bool tree_node_insert(node *start, node *to_insert);

/// Delete a node from the search tree
///
/// \returns: true if node deletion was successful
bool tree_node_remove(tree *tree_root, char *key);

/// Free:s up the memory that was allocated for the root
///
/// \returns: true if root was successfully deleted 
bool tree_root_free(node **input_root);

/// Free:s up the memory that was allocated for a node
///
/// \returns: true if node was successfully deleted
bool node_free(node *to_delete);

/// Searches through the tree to find a node that matches the input key. If a node is found, dest_node will point to it when the function is done.
///
/// \returns: true if node was found, eitherwise false.
node *find_node_in_tree(char *find_key, tree *tree_root/*, node *dest_node*/);

/// Auxilliary recursive function for find_node_in_tree that goes through each node to find a node that matches the key
///
/// \returns: the node if it is found, eitherwise NULL.
node *find_node_in_tree_aux(char *key, node *root_node);

/// Handles the rebalancing of the tree when the node that is to be deleted is the root node of the tree.
void tree_rebalance_root_shift(tree *input_tree, node *replacement);

/// Swaps a node that will be changed/deleted with a successor to keep the order in the binary search tree
///
/// \returns: true if rebalancing was successful
bool tree_rebalance(tree *input_tree, node *to_rebalance);

/// Shifts the replacement node to the to_rebalance node's position under the parent of to_rebalance. All pointers are correctly shifted.
void tree_rebalance_parent_shift(node *replacement, node *to_rebalance);

/// Shifts the replacement node to the to_rebalance node's position over the right child of to_rebalance. All pointers are correctly shifted. 
void tree_rebalance_right_child_shift(node *replacement, node *to_rebalance);

/// Shifts the replacement node to the to_rebalance node's position over the left child of to_rebalance. All pointers are correctly shifted. 
void tree_rebalance_left_child_shift(node *replacement, node *to_rebalance);

/// Edits a node in the tree and rebalances the node if necessary
///
/// \returns: true if successful
bool tree_node_edit(tree *input_tree, char *key);

/// Finds the smallest subnode in a tree
///
/// \returns: the smallest node found
node *find_smallest_node(node *start);


#endif /* tree_h */
