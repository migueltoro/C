/*
 * binary_tree.h
 *
 *  Created on: 5 nov. 2018
 *      Author: migueltoro
 */

#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include "../types/list.h"
#include "../types/types.h"

typedef enum{Empty_Tree, Leaf_Tree, Binary_Tree} tree_type;

typedef struct bt {
	tree_type tree_type;
	int size_label;
	void * label;
	struct bt * left;
	struct bt * right;
}binary_tree;


binary_tree * tree_empty(memory_heap * hp);
binary_tree * tree_leaf(void * label, int size_element, memory_heap * hp);
binary_tree * tree_binary(void * label,int size_element, binary_tree * left, binary_tree * right, memory_heap * hp);
tree_type binary_tree_type(binary_tree * tree);
void * binary_tree_label(binary_tree * tree);
binary_tree * binary_tree_left(binary_tree * tree);
binary_tree * binary_tree_right(binary_tree * tree);
list binary_tree_to_list(binary_tree * tree, type type_element);
int binary_tree_size(binary_tree * tree);
void binary_tree_toconsole(binary_tree * tree, char * tostring(const void * source, char * m));

#endif /* BINARY_TREE_H_ */
