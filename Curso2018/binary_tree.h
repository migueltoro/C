/*
 * binary_tree.h
 *
 *  Created on: 5 nov. 2018
 *      Author: migueltoro
 */

#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include "alist.h"
#include "types.h"

typedef enum{Empty_Tree, Leaf_Tree, Binary_Tree} tree_type;

typedef struct bt {
	tree_type tree_type;
	void * label;
	struct bt * left;
	struct bt * right;
}binary_tree;


binary_tree * tree_empty();
binary_tree * tree_leaf(void * label);
binary_tree * tree_binary(void * label, binary_tree * left, binary_tree * right);
tree_type get_type(binary_tree * tree);
void * get_label(binary_tree * tree);
binary_tree * get_left(binary_tree * tree);
binary_tree * get_right(binary_tree * tree);
alist tree_to_list(binary_tree * tree);
int tree_size(binary_tree * tree);
void tree_tostring(binary_tree * tree, char * tostring(const void * source, char * mem));

void binary_tree_memory_free();
void binary_tree_memory_create();

#endif /* BINARY_TREE_H_ */
